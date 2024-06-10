import secrets
import json

def generate_token():
    return secrets.token_hex(16)

def load(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)