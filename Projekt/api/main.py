import shlex
from flask import Flask, jsonify, request
from flask_cors import CORS
from codecs import encode
from auth import generate_token, load
# from sentiment import *
from rpc import *
def generateID():
    num = 0
    while num < 100000:
        yield num
        num += 1

# from dummyfuncs import translate_text_dummy, sentiment_analyze_dummy

generator = generateID()
#begin client init
client = RPCClient("tcp://localhost:5555", True)
#test case
# res = client.send(b"ping", b"test")

# print(res)

users = load('users.json')
sessions = load('sessions.json')

#begin flask app
app = Flask(__name__)
CORS(app)

@app.route("/api/ping", methods=['GET'])
def ping():

    # return jsonify(data = "Online")

    try:
        client.send(b"ping", b"Online")
        reply = client.recv()
        if reply is None:
            raise Exception("Server reply is None")
    except KeyboardInterrupt:
        reply = ["int"]
    except Exception as e:
        return jsonify(
            data=f"Error: {str(e)}"
        )

    return jsonify(
        data = reply[0].decode("utf-8")
    )
@app.route("/api/translate", methods=['POST'])
def translate():
    auth = request.headers.get('Authorization')
    
    if not auth in sessions.values():
        return jsonify(
            data = "Unauthorized"
        ), 403

    req = request.get_json()
    srcLanguage = None
    dstLanguage = None
    mode = None
    data = None
    id = next(generator)

    if req:
        if 'srcLanguage' in req:
            srcLanguage = req['srcLanguage'].replace('\07', ' ').replace('"', '&quot;')
        if 'dstLanguage' in req:
            dstLanguage = req['dstLanguage'].replace('\07', ' ').replace('"', '&quot;')
        if 'mode' in req:
            mode = req['mode'].replace('\07', ' ').replace('"', '&quot;')
        if 'data' in req:
            data = req['data'].replace('\07', '').replace('"', '&quot;')
    if data == None or mode == None or srcLanguage == None or dstLanguage == None:
        return jsonify(
            data = "Not enough parameters in request, aborting"
        )

    # return translate_text_dummy(data)

    try:
        client.send(b"translate", f'{srcLanguage}\07{dstLanguage}\07{mode}\07{data}'.encode())
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]
    else:
        if reply is None:
            reply = ["err"]

    return jsonify(
        data = reply[0].decode("utf-8")
    )

@app.route("/api/detect", methods=['POST'])
def detect():
    auth = request.headers.get('Authorization')
    
    if not auth in sessions.values():
        return jsonify(
            data = "Unauthorized"
        ), 403

    req = request.get_json()
    data = shlex.quote(req.get('data')).replace('\07', ' ').replace('"', '&quot;')

    if data is None:
        return jsonify(data="Not enough parameters in request, aborting")

    try:
        client.send(b"detect", f'{data}'.encode())
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]

    return jsonify(data=reply[0].decode("utf-8"))

@app.route("/api/anonymize", methods=['POST'])
def anonymize():
    auth = request.headers.get('Authorization')
    
    if not auth in sessions.values():
        return jsonify(
            data = "Unauthorized"
        ), 403

    req = request.get_json()
    data = req.get('data').replace('\07', ' ').replace('"', '&quot;')

    if data is None:
        return jsonify(data="Not enough parameters in request, aborting")

    try:
        client.send(b"anonymize", f'{data}'.encode())
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]

    return jsonify(data=reply[0].decode("utf-8"))
    
@app.route("/api/sentiment", methods=['POST'])
def sentiment():
    auth = request.headers.get('Authorization')
    
    if not auth in sessions.values():
        return jsonify(
            data = "Unauthorized"
        ), 403

    req = request.get_json()
    mode = None
    data = None
    id = next(generator)

    if req:
        mode = req.get('mode').replace('\07', ' ').replace('"', '&quot;')
        data = req.get('data').replace('\07', ' ').replace('"', '&quot;')

    if data == None or mode == None:
        return jsonify(
            data = "Not enough parameters in request, aborting"
        )
    
    # return sentiment_analyze_dummy(data)

    try:
        client.send(b"sentiment", f'{mode}\07{data}'.encode())
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]
    else:
        if reply is None:
            reply = ["err"]

    if reply:
        try:
            reply_str = reply[0].decode("utf-8")
            sentiment, probability = reply_str.split("\07")
            return jsonify(
                sentiment = sentiment,
                probability = probability
            )
        except Exception as e:
            return jsonify(
                data="Error while decoding server response"
            )
    else:
        return jsonify(
            data="An error occurred while processing sentimen"
        )

@app.route("/api/signin", methods=['POST'])
def signin():
    # development-only super simple auth service
    req = request.get_json()
    email = None
    password = None
    id = next(generator)

    if req:
        if 'email' in req:
            email = req['email']
        if 'password' in req:
            password = req['password']
    if email == None or password == None:
        return jsonify(
            token = 0,
            data = "Invalid request, aborting"
        )

    if email not in users:
        return jsonify(
            token = 0,
            data = "Invalid request"
        )

    if password != users[email]:
        return jsonify(
            token = 0,
            data = "Invalid request"
        )

    if email not in sessions:
        sessions[email] = generate_token()

    return jsonify(
        token = sessions[email],
        data = "Login successful"
    )
    
@app.route("/api/auth", methods=['POST'])
def auth():
    # check if token is correct and return
    req = request.get_json()
    token = None
    id = next(generator)

    if req:
        if 'token' in req:
            token = req['token']
    
    if token == None:
        return jsonify(
            data = False,
        )
    
    if token in sessions.values():
        return jsonify(
            data = True,
        )
    else:
        return jsonify(
            data = False,
        )
    
if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=8080)