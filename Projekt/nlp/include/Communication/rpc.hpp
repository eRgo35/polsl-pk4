#ifndef RPC_HPP

#define RPC_HPP

#include <deque>
#include <list>
#include <map>
#include <set>

#include "mdp.h"
#include "zmsg.hpp"

// Begin broker definitions
static constexpr uint32_t n_heartbeat_liveness = 3;
static constexpr uint32_t n_heartbeat_interval = 2500;  //  msecs
static constexpr uint32_t n_heartbeat_expiry =
    n_heartbeat_interval * n_heartbeat_liveness;  //  msecs

struct service;
struct worker {
  std::string m_identity;  //  Address of worker
  service *m_service;      //  Owning service, if known
  int64_t m_expiry;        //  Expires at unless heartbeat

  worker(std::string identity, service *service = nullptr, int64_t expiry = 0)
      : m_identity(identity), m_service(service), m_expiry(expiry) {}
};

//  This defines a single service
struct service {
  ~service() {
    for (size_t i = 0; i < m_requests.size(); i++) {
      delete m_requests[i];
    }
  }

  const std::string m_name;       //  Service name
  std::deque<zmsg *> m_requests;  //  List of client requests
  std::list<worker *> m_waiting;  //  List of waiting workers
  size_t m_workers;               //  How many workers we have

  service(std::string name) : m_name(name) {}
};

//  This defines a single broker
class broker {
 public:
  //  ---------------------------------------------------------------------
  //  Constructor for broker object

  broker(int verbose) : m_verbose(verbose) {
    //  Initialize broker state
    m_context = new zmq::context_t(1);
    m_socket = new zmq::socket_t(*m_context, ZMQ_ROUTER);
  }

  //  ---------------------------------------------------------------------
  //  Destructor for broker object

  virtual ~broker() {
    while (!m_services.empty()) {
      delete m_services.begin()->second;
      m_services.erase(m_services.begin());
    }
    while (!m_workers.empty()) {
      delete m_workers.begin()->second;
      m_workers.erase(m_workers.begin());
    }
  }

  //  ---------------------------------------------------------------------
  //  Bind broker to endpoint, can call this multiple times
  //  We use a single socket for both clients and workers.

  void bind(std::string endpoint) {
    m_endpoint = endpoint;
    m_socket->bind(m_endpoint.c_str());
    console->log("I: MDP broker/0.1.1 is active at ", endpoint.c_str());
  }

 private:
  AsyncLogger *console = AsyncLogger::GetInstance();

  //  ---------------------------------------------------------------------
  //  Delete any idle workers that haven't pinged us in a while.

  void purge_workers() {
    std::deque<worker *> toCull;
    int64_t now = s_clock();
    for (auto wrk = m_waiting.begin(); wrk != m_waiting.end(); ++wrk) {
      if ((*wrk)->m_expiry <= now) toCull.push_back(*wrk);
    }
    for (auto wrk = toCull.begin(); wrk != toCull.end(); ++wrk) {
      if (m_verbose) {
        console->log("I: deleting expired worker: ",
                     (*wrk)->m_identity.c_str());
      }
      worker_delete(*wrk, 0);
    }
  }

  //  ---------------------------------------------------------------------
  //  Locate or create new service entry

  service *service_require(std::string name) {
    assert(!name.empty());
    if (m_services.count(name)) {
      return m_services.at(name);
    }
    service *srv = new service(name);
    m_services.insert(std::pair{name, srv});
    if (m_verbose) {
      console->log("I: received message:");
    }
    return srv;
  }

  //  ---------------------------------------------------------------------
  //  Dispatch requests to waiting workers as possible

  void service_dispatch(service *srv, zmsg *msg) {
    assert(srv);
    if (msg) {  //  Queue message if any
      srv->m_requests.push_back(msg);
    }

    purge_workers();
    while (!srv->m_waiting.empty() && !srv->m_requests.empty()) {
      // Choose the most recently seen idle worker; others might be about to
      // expire
      auto wrk = srv->m_waiting.begin();
      auto next = wrk;
      for (++next; next != srv->m_waiting.end(); ++next) {
        if ((*next)->m_expiry > (*wrk)->m_expiry) wrk = next;
      }

      zmsg *msg = srv->m_requests.front();
      srv->m_requests.pop_front();
      worker_send(*wrk, k_mdpw_request.data(), "", msg);
      m_waiting.erase(*wrk);
      srv->m_waiting.erase(wrk);
      delete msg;
    }
  }

  //  ---------------------------------------------------------------------
  //  Handle internal service according to 8/MMI specification

  void service_internal(std::string service_name, zmsg *msg) {
    if (service_name.compare("mmi.service") == 0) {
      service *srv = m_services[msg->body()];
      if (srv && srv->m_workers) {
        msg->body_set("200");
      } else {
        msg->body_set("404");
      }
    } else {
      msg->body_set("501");
    }

    //  Remove & save client return envelope and insert the
    //  protocol header and service name, then rewrap envelope.
    std::string client = msg->unwrap();
    msg->wrap(k_mdp_client.data(), service_name.c_str());
    msg->wrap(client.c_str(), "");
    msg->send(*m_socket);
    delete msg;
  }

  //  ---------------------------------------------------------------------
  //  Creates worker if necessary

  worker *worker_require(std::string identity) {
    assert(!identity.empty());

    //  self->workers is keyed off worker identity
    if (m_workers.count(identity)) {
      return m_workers.at(identity);
    } else {
      worker *wrk = new worker(identity);
      m_workers.insert(std::make_pair(identity, wrk));
      if (m_verbose) {
        console->log("I: registering new worker: ", identity.c_str());
      }
      return wrk;
    }
  }

  //  ---------------------------------------------------------------------
  //  Deletes worker from all data structures, and destroys worker

  void worker_delete(worker *&wrk, int disconnect) {
    assert(wrk);
    if (disconnect) {
      worker_send(wrk, k_mdpw_disconnect.data(), "", NULL);
    }

    if (wrk->m_service) {
      for (auto it = wrk->m_service->m_waiting.begin();
           it != wrk->m_service->m_waiting.end();) {
        if (*it == wrk) {
          it = wrk->m_service->m_waiting.erase(it);
        } else {
          ++it;
        }
      }
      wrk->m_service->m_workers--;
    }
    m_waiting.erase(wrk);
    //  This implicitly calls the worker destructor
    m_workers.erase(wrk->m_identity);
    delete wrk;
  }

  //  ---------------------------------------------------------------------
  //  Process message sent to us by a worker

  void worker_process(std::string sender, zmsg *msg) {
    assert(msg && msg->parts() >= 1);  //  At least, command

    std::string command = (char *)msg->pop_front().c_str();
    bool worker_ready = m_workers.count(sender) > 0;
    worker *wrk = worker_require(sender);

    if (command.compare(k_mdpw_ready.data()) == 0) {
      if (worker_ready) {  //  Not first command in session
        worker_delete(wrk, 1);
      } else {
        if (sender.size() >= 4  //  Reserved service name
            && sender.find_first_of("mmi.") == 0) {
          worker_delete(wrk, 1);
        } else {
          //  Attach worker to service and mark as idle
          std::string service_name = (char *)msg->pop_front().c_str();
          wrk->m_service = service_require(service_name);
          wrk->m_service->m_workers++;
          worker_waiting(wrk);
        }
      }
    } else {
      if (command.compare(k_mdpw_reply.data()) == 0) {
        if (worker_ready) {
          //  Remove & save client return envelope and insert the
          //  protocol header and service name, then rewrap envelope.
          std::string client = msg->unwrap();
          msg->wrap(k_mdp_client.data(), wrk->m_service->m_name.c_str());
          msg->wrap(client.c_str(), "");
          msg->send(*m_socket);
          worker_waiting(wrk);
        } else {
          worker_delete(wrk, 1);
        }
      } else {
        if (command.compare(k_mdpw_heartbeat.data()) == 0) {
          if (worker_ready) {
            wrk->m_expiry = s_clock() + n_heartbeat_expiry;
          } else {
            worker_delete(wrk, 1);
          }
        } else {
          if (command.compare(k_mdpw_disconnect.data()) == 0) {
            worker_delete(wrk, 0);
          } else {
            console->error("E: invalid input message (", (int)*command.c_str(),
                           ")");
            msg->dump();
          }
        }
      }
    }
    delete msg;
  }

  //  ---------------------------------------------------------------------
  //  Send message to worker
  //  If pointer to message is provided, sends that message

  void worker_send(worker *worker, const char *command, std::string option,
                   zmsg *msg) {
    msg = (msg ? new zmsg(*msg) : new zmsg());

    //  Stack protocol envelope to start of message
    if (option.size() > 0) {  //  Optional frame after command
      msg->push_front(option.c_str());
    }
    msg->push_front(command);
    msg->push_front(k_mdpw_worker.data());
    //  Stack routing envelope to start of message
    msg->wrap(worker->m_identity.c_str(), "");

    if (m_verbose) {
      console->log("I: sending ", mdps_commands[(int)*command].data(),
                   " to broker");
      msg->dump();
    }
    msg->send(*m_socket);
    delete msg;
  }

  //  ---------------------------------------------------------------------
  //  This worker is now waiting for work

  void worker_waiting(worker *worker) {
    assert(worker);
    //  Queue to broker and service waiting lists
    m_waiting.insert(worker);
    worker->m_service->m_waiting.push_back(worker);
    worker->m_expiry = s_clock() + n_heartbeat_expiry;
    // Attempt to process outstanding requests
    service_dispatch(worker->m_service, 0);
  }

  //  ---------------------------------------------------------------------
  //  Process a request coming from a client

  void client_process(std::string sender, zmsg *msg) {
    assert(msg && msg->parts() >= 2);  //  Service name + body

    std::string service_name = (char *)msg->pop_front().c_str();
    service *srv = service_require(service_name);
    //  Set reply return address to client sender
    msg->wrap(sender.c_str(), "");
    if (service_name.length() >= 4 && service_name.find_first_of("mmi.") == 0) {
      service_internal(service_name, msg);
    } else {
      service_dispatch(srv, msg);
    }
  }

 public:
  //  Get and process messages forever or until interrupted
  void start_brokering() {
    int64_t now = s_clock();
    int64_t heartbeat_at = now + n_heartbeat_interval;
    while (!s_interrupted) {
      zmq::pollitem_t items[] = {{*m_socket, 0, ZMQ_POLLIN, 0}};
      int64_t timeout = heartbeat_at - now;
      if (timeout < 0) timeout = 0;
      zmq::poll(items, 1, (long)timeout);

      //  Process next input message, if any
      if (items[0].revents & ZMQ_POLLIN) {
        zmsg *msg = new zmsg(*m_socket);
        if (m_verbose) {
          console->log("I: received message:");
          msg->dump();
        }
        std::string sender = (char *)msg->pop_front().c_str();
        msg->pop_front();  // empty message
        std::string header = (char *)msg->pop_front().c_str();

        if (header.compare(k_mdp_client.data()) == 0) {
          client_process(sender, msg);
        } else if (header.compare(k_mdpw_worker.data()) == 0) {
          worker_process(sender, msg);
        } else {
          console->error("E: invalid message:");
          msg->dump();
          delete msg;
        }
      }
      //  Disconnect and delete any expired workers
      //  Send heartbeats to idle workers if needed
      now = s_clock();
      if (now >= heartbeat_at) {
        purge_workers();
        for (auto it = m_waiting.begin(); it != m_waiting.end() && (*it) != 0;
             it++) {
          worker_send(*it, k_mdpw_heartbeat.data(), "", NULL);
        }
        heartbeat_at += n_heartbeat_interval;
        now = s_clock();
      }
    }
  }

 private:
  zmq::context_t *m_context;  //  0MQ context
  zmq::socket_t *m_socket;    //  Socket for clients & workers
  const int m_verbose;        //  Print activity to stdout
  std::string m_endpoint;     //  Broker binds to this endpoint
  std::map<std::string, service *> m_services;  //  Hash of known services
  std::map<std::string, worker *> m_workers;    //  Hash of known workers
  std::set<worker *> m_waiting;                 //  List of waiting workers
};

#endif