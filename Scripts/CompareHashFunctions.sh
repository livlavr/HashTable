#!/bin/bash

echo "[  Begin Comparing  ]"

cd ..
cd HashFunctionsComparing

mkdir -p TestsResults
mkdir -p TestsSrc
# python TestsGenerator/StringTestsGenerator.py || exit
cd ..

mkdir -p build      || exit
rm -rf build/*      || exit
cmake -S . -B build || exit
cd build            || exit
make                || exit

./bin/HashFunctionsComparing --hash sumHash             < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/SumHashResults.txt             || exit
./bin/HashFunctionsComparing --hash polynomialHash      < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/PolynomialHashResults.txt      || exit
./bin/HashFunctionsComparing --hash crc32Hash           < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/Crc32HashResults.txt           || exit
./bin/HashFunctionsComparing --hash crc32HashOptimized  < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/Crc32HashOptimizedResults.txt  || exit
./bin/HashFunctionsComparing --hash crc32HashIntrinsics < ../HashFunctionsComparing/TestsSrc/Tests.txt > ../HashFunctionsComparing/TestsResults/Crc32HashIntrinsicsResults.txt || exit

echo "[ Success Comparing ]"
