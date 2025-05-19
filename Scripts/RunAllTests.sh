#!/bin/bash

generateAndOpenPlots () {
    cd Plot
    mkdir -p img
    python PlotBuilder.py

    cd ..
}

cd ..
python -m venv venv
source venv/bin/activate
pip install matplotlib

cd Scripts
./CompareHashFunctions.sh

cd ..
cd HashFunctionsComparing
generateAndOpenPlots
cd ..

# cd HashTablesComparing
# ./StartHashTesting.sh
#
# generateAndOpenPlots

deactivate
