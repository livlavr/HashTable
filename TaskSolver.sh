#!/bin/bash

generateAndOpenPlots () {
    cd Plot
    mkdir -p img
    cd src
    python PlotBuilder.py

    cd ..
    open img/*
    cd ..
}

python3 -m venv venv
source venv/bin/activate
pip install matplotlib

cd HashFunctionsComparing
./StartComparing.sh

generateAndOpenPlots

cd HashTablesComparing
./StartHashTesting.sh

generateAndOpenPlots

deactivate
