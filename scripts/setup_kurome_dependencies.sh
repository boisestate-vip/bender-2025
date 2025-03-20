#!/bin/bash

sudo echo "root aquired"

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# update git submodules
bash $BENDER_SCRIPTS_DIR/update_submodules.sh

cd $BENDER_DEPENDENCIES_DIR

# download ceres
rm -rf ceres-solver-2.2.0
wget ceres-solver.org/ceres-solver-2.2.0.tar.gz
gunzip ceres-solver-2.2.0.tar.gz
tar xf ceres-solver-2.2.0.tar
rm -rf ceres-solver-2.2.0.tar

# install all the other stuff we can grab from the web
sudo apt install libabsl-dev
sudo apt install libgoogle-glog-dev
sudo apt install libsfml-dev
sudo apt install libeigen3-dev

# build and install ceres
cd $BENDER_DEPENDENCIES_DIR/ceres-solver-2.2.0
mkdir -p build
cd build
cmake ..
make -j$(nproc)
sudo make install


