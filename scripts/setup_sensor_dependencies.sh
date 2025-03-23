#!/bin/bash

sudo echo "root aquired"

# check that setup is done 
if [ $BENDER_SETUP != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# update git submodules
bash $BENDER_SCRIPTS_DIR/update_submodules.sh

# install all the stuff we can rip from the web
sudo apt-get install ros-iron-diagnostics unzip -y
sudo apt-get install libssl-dev libusb-1.0-0.dev libudev-dev pkg-config libgtk-3-dev build-essential -y
sudo apt-get install v4l-utils libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev -y

# grab steam if we are on an x86 machine
if [[ "$(arch)" = "x86_64" ]]; then
   sudo apt install software-properties-common apt-transport-https curl steam-installer steam-devices -y
fi

# download librealsense
cd $BENDER_DEPENDENCIES_DIR
if [ ! -d librealsense-2.53.1 ]; then
   wget https://github.com/IntelRealSense/librealsense/archive/refs/tags/v2.53.1.zip
   unzip v2.53.1.zip
   rm -rf v2.53.1.zip
fi

cd $BENDER_DEPENDENCIES_DIR/unitree_lidar_sdk
mkdir -p build
cd build
cmake ..
make -j$(nproc)
sudo make install

cd $BENDER_DEPENDENCIES_DIR/YDLidar-SDK
mkdir -p build
cd build
cmake ..
make -j$(nproc)
sudo make install

cd $BENDER_DEPENDENCIES_DIR/openvr
mkdir -p build
cd build
cmake ..
make -j$(nproc)
sudo make install


cd $BENDER_DEPENDENCIES_DIR/librealsense-2.53.1
sudo ./scripts/setup_udev_rules.sh
sudo ./scripts/patch-realsense-ubuntu-lts-hwe.sh
mkdir -p build
cd build
cmake .. -DFORCE_RSUSB_BACKEND=true -DCMAKE_BUILD_TYPE=release
make -j$(nproc) 
sudo make install

