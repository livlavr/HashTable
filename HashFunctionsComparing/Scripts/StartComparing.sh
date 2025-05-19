#!/bin/bash

echo "[ Begin Comparing ]"

cd ..

mkdir -p TestsResults
mkdir -p build

mkdir -p TestsSrc
python TestingSystem/TestGen/StringTestsGenerator.py || exit

cmake -S . -B build
cd build || exit
make

./HashFunctionsComparing --hash sumHash             < ../TestsSrc/Tests.txt > ../TestsResults/SumHashResults.txt
./HashFunctionsComparing --hash polynomialHash      < ../TestsSrc/Tests.txt > ../TestsResults/PolynomialHashResults.txt
./HashFunctionsComparing --hash crc32Hash           < ../TestsSrc/Tests.txt > ../TestsResults/Crc32HashResults.txt
./HashFunctionsComparing --hash crc32HashOptimized  < ../TestsSrc/Tests.txt > ../TestsResults/Crc32HashOptimizedResults.txt
./HashFunctionsComparing --hash crc32HashIntrinsics < ../TestsSrc/Tests.txt > ../TestsResults/Crc32HashIntrinsicsResults.txt

echo "[     Success Comparing    ]"
