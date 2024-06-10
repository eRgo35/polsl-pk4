#!/bin/sh

# setup up venv
python -m venv .venv

# install dependencies
./.venv/bin/pip install -r requirements.txt

# change venv if ran `source ./activate.sh`
source $(pwd)/.venv/bin/activate

echo "Run 'source ./.venv/bin/activate' to activate the virtual environment."