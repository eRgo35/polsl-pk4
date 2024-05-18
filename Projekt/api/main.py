from flask import Flask, jsonify, request
from flask_cors import CORS
from codecs import encode
# from sentiment import *
from rpc import *
def generateID():
    num = 0
    while num < 100000:
        yield num
        num += 1

from dummyfuncs import translate_text_dummy, sentiment_analyze_dummy

generator = generateID()
#begin client init
client = RPCClient("tcp://localhost:5555", True)
#test case
res = client.send(b"ping", b"test")

print(res)


#begin flask app
app = Flask(__name__)
CORS(app)

@app.route("/api/ping", methods=['GET'])
def ping():
    try:
        client.send(b"ping", b"Online")
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]
    else:
        if reply is None:
            reply = ["err"]
    return jsonify(
        data = str(reply[0], encoding="utf-8")
    )
@app.route("/api/translate", methods=['POST'])
def translate():
    req = request.get_json()
    srcLanguage = None
    dstLanguage = None
    data = None
    id = next(generator)

    if req:
        if 'srcLanguage' in req:
            srcLanguage = req['srcLanguage']
        if 'dstLanguage' in req:
            dstLanguage = req['dstLanguage']
        if 'data' in req:
            data = req['data']
    if data == None or srcLanguage == None or dstLanguage == None:
        return jsonify(
            data = "Not enough parameters in request, aborting"
        )
    #todo Implement zmq
    return translate_text_dummy(data)

    try:
        client.send(b"translate", f'{srcLanguage}\00\00{dstLanguage}\00\00{data}'.encode())
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]
    else:
        if reply is None:
            reply = ["err"]

    return jsonify(
        data = str(reply[0], encoding="utf-8")
    )
    

@app.route("/api/sentiment")
def sentiment():
    req = request.get_json()
    mode = None
    data = None
    id = next(generator)

    if req:
        if 'mode' in req:
            mode = req['mode']
        if 'data' in req:
            data = req['data']
    if data == None or mode == None:
        return jsonify(
            data = "Not enough parameters in request, aborting"
        )
    
    return sentiment_analyze_dummy(data)
    #todo Implement zmq
    try:
        client.send(b"sentiment", f'{mode}\00\00{data}')
        reply = client.recv()
    except KeyboardInterrupt:
        reply = ["int"]
    else:
        if reply is None:
            reply = ["err"]
    return jsonify(
        data = str(reply[0], encoding="utf-8")
    )

if __name__ == "__main__":
    app.run(debug=True, port=8080)

