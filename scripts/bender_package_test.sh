#!/bin/bash

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# update git submodules
bash $BENDER_SCRIPTS_DIF/update_submodules.sh

# initialize file we are going to store our successes in
mkdir -p $BENDER_DIR/bin
touch $BENDER_DIR/bin/packages

# package directories
packages=("$BENDER_DIR/src/sensors/

