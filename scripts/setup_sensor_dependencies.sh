#!/bin/bash

sudo echo "root aquired"

# check that setup is done 
if [ $BENDER_SETUP != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# update git submodules
bash $BENDER_SCRIPTS_DIR/update_submodules.sh

cd $BENDER_DEPENDENCIES_DIR/unitree_lidar_sdk
mkdir -p build
cd ./build
cmake ..
make -j$(nproc)
sudo make install

cd $BENDER_DEPENDENCIES_DIR/YDLidar-SDK
mkdir -p build
cd ./build
cmake ..
make -j$(nproc)
sudo make install
