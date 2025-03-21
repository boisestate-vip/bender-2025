#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

sudo echo "root aquired"

sudo bash $SCRIPT_DIR/bender_init.sh $1
. $SCRIPT_DIR/setup.sh
bash $SCRIPT_DIR/setup_and_test_packages.sh
