#!/bin/bash

tests_dir=TestsSrc

mkdir -p $tests_dir

echo "[ WARNING ] If TestsGenerator error, change python interpretator in .py script"
./TestingSystem/StringTestsGenerator.py

echo "[  Success Tests Generating  ]"
