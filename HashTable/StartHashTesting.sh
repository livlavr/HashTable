#!/bin/bash

echo "[ Begin Comparing ]"

mkdir -p TestsResults
mkdir -p build

cmake -S . -B build
cd build || exit
make

./HashTablesTesting > ../TestsResults/ChainHashTestsResults.txt
echo "[     Success Testing    ]"
