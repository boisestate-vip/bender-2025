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

# set device name for bender
mkdir -p $SCRIPT_DIR/../bin
chmod 733 $SCRIPT_DIR/../bin 
rm -f $SCRIPT_DIR/../bin/name
touch $SCRIPT_DIR/../bin/name
echo $1 >> $SCRIPT_DIR/../bin/name

source /home/$SUDO_USER/.bashrc





