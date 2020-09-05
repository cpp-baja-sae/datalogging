#!/bin/sh

python3 generate_code.py
mkdir -p output 
cd output 
cmake ..
make