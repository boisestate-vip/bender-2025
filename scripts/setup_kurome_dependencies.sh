#!/bin/bash

sudo echo "root aquired"

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# update git submodules
bash $BENDER_SCRIPTS_DIR/update_submodules.sh


# download ceres
cd $BENDER_DEPENDENCIES_DIR
if [ ! -d ceres-solver-2.2.0 ]; then
   wget ceres-solver.org/ceres-solver-2.2.0.tar.gz
   gunzip ceres-solver-2.2.0.tar.gz
   tar xf ceres-solver-2.2.0.tar
   rm -rf ceres-solver-2.2.0.tar
fi

# install all the other stuff we can grab from the web
sudo apt install libabsl-dev -y
sudo apt install libgoogle-glog-dev -y
sudo apt install libsfml-dev -y
sudo apt install libeigen3-dev -y

# build and install ceres
cd $BENDER_DEPENDENCIES_DIR/ceres-solver-2.2.0
mkdir -p build
cd build
cmake ..
make -j$(nproc)
sudo make install


