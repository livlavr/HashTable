#!/bin/bash

echo "[  Begin Comparing  ]"

cd ..
cd HashFunctionsComparing

mkdir -p TestsResults
mkdir -p TestsSrc
python TestingSystem/TestsGenerator/StringTestsGenerator.py || exit
cd ..

cmake -S . -B build || exit
cd build || exit
make || exit

./HashFunctionsComparing/HashFunctionsComparing --hash sumHash             < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/SumHashResults.txt             || exit
./HashFunctionsComparing/HashFunctionsComparing --hash polynomialHash      < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/PolynomialHashResults.txt      || exit
./HashFunctionsComparing/HashFunctionsComparing --hash crc32Hash           < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/Crc32HashResults.txt           || exit
./HashFunctionsComparing/HashFunctionsComparing --hash crc32HashOptimized  < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/Crc32HashOptimizedResults.txt  || exit
./HashFunctionsComparing/HashFunctionsComparing --hash crc32HashIntrinsics < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/Crc32HashIntrinsicsResults.txt || exit

echo "[ Success Comparing ]"
