#!/bin/bash

echo "[ Begin Comparing ]"

mkdir -p TestsResults
mkdir -p build

./TestingSystem/GenerateComparingTests.sh

cmake -S . -B build
cd build || exit
make

./HashFunctionsComparing --string lengthHash     < ../TestsSrc/StringTests.txt > ../TestsResults/StringLengthHashResults.txt
./HashFunctionsComparing --string sumHash        < ../TestsSrc/StringTests.txt > ../TestsResults/StringSumHashResults.txt
./HashFunctionsComparing --string polynomialHash < ../TestsSrc/StringTests.txt > ../TestsResults/StringPolynomialHashResults.txt
./HashFunctionsComparing --string crc32Hash      < ../TestsSrc/StringTests.txt > ../TestsResults/StringCrc32HashResults.txt
echo "[     Success Comparing    ]"
