#!/bin/bash

sudo echo "root aquired"

# the the directory that this script is being run in
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# get all the exports we want
. $SCRIPT_DIR/setup.sh

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

if (( $ROS_VERSION != 2 )); then
   echo "Ros2 must be installed and sourced on this system"
   exit 1
fi

sudo apt install libsystemd-dev -y

# install the config files
sudo mkdir -p /etc/bender
cp $BENDER_DIR/src/daemon/defaults/daemon.default.conf .
mv daemon.default.conf daemon.conf
echo "BENDER_DIR=$BENDER_DIR" >> daemon.conf
echo "ROS_DISTRO=$ROS_DISTRO" >> daemon.conf
echo "BENDER_HOSTNAME=$BENDER_HOSTNAME" >> daemon.conf
sudo mv daemon.conf /etc/bender
cp $BENDER_DIR/src/daemon/defaults/cmd.default.conf .
mv cmd.default.conf cmd.conf
sudo mv cmd.conf /etc/bender

# try and get the status of the bender daemon
systemctl status benderd > /dev/null
if [ "$?" -eq "0" ]; then
   exit 0 # the daemon has already been installed and is running on the system
fi

# otherwise, go about the steps daemon of installation

# build and install relevent executables
cd $BENDER_DIR/src/daemon/source
make
sudo make install

# copy all releavant daemon files to their locations
sudo cp $BENDER_DIR/src/daemon/defaults/bender.service /lib/systemd/system
sudo systemctl enable bender.service
sudo systemctl start bender.service

# copy man pages into their locations
sudo cp $BENDER_DIR/src/daemon/defaults/man/bender /usr/local/man/man1/bender.1
sudo gzip /usr/local/man/man1/bender.1
sudo cp $BENDER_DIR/src/daemon/defaults/man/magma /usr/local/man/man1/magma.1
sudo gzip /usr/local/man/man1/magma.1
sudo mkdir -p /usr/local/man/man7
sudo cp $BENDER_DIR/src/daemon/defaults/man/bender.config /usr/local/man/man7/bender.config.1
sudo gzip /usr/local/man/man7/bender.config.1
