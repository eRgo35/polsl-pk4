#!/bin/sh

#setup up venv
python -m venv .venv

# run in console to start dev mode
source ./.venv/bin/activate

#install dependecies
pip install -r requirements.txt
