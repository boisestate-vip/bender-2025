#!/bin/bash

sudo echo "root aquired"

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# do everything
bash $BENDER_SCRIPTS_DIR/setup_sensor_dependencies.sh
bash $BENDER_SCRIPTS_DIR/setup_kurome_dependencies.sh
bash $BENDER_SCRIPTS_DIR/bender_package_test.sh
