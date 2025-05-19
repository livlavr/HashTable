#!/bin/bash

generateAndOpenPlots () {
    cd Plot
    mkdir -p img
    python PlotBuilder.py

    cd ..
}

python -m venv venv
source venv/bin/activate
pip install matplotlib

cd HashFunctionsComparing
cd Scripts
./StartComparing.sh

cd ..
generateAndOpenPlots
cd ..

# cd HashTablesComparing
# ./StartHashTesting.sh
#
# generateAndOpenPlots

deactivate
