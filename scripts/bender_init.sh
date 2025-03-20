#!/bin/bash

# check for root
if [[ "$(whoami)" != "root" ]]; then
   echo "Script must be run as root or using sudo"
   exit 1
fi

# check that an argument is passed
if (( $# != 1 )); then
   echo "Please pass the system name for initialization"
   exit 1
fi

# add user to the dialout group
usermod -a -G dialout $SUDO_USER

# get script dir
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# add startup to .bashrc
echo ". $SCRIPT_DIR/setup.sh" >> /home/$SUDO_USER/.bashrc 

source /home/$SUDO_USER/.bashrc

# set device name for bender
rm -f $BENDER_BIN_DIR/name
touch $BENDER_BIN_DIR/name
echo $1 >> $BENDER_BIN_DIR/name




