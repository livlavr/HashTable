#!/bin/bash

cd ..
cd build
make
python ../ChainHashTable/UnitTests/UnitTests.py
