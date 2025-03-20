#!/bin/bash

if [ $BENDER_SETUP != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

cd $BENDER_DEPENDENCIES_DIR/YDLidar-SDK
git pull origin master

cd $BENDER_DEPENDENCIES_DIR/openvr
git pull origin master

cd $BENDER_DEPENDENCIES_DIR/pcl
git pull origin master

cd $BENDER_DIR/src/nav/kurome_ws/src/kurome
git pull origin main

cd $BENDER_DIR/src/nav/diff_drive_ws/src/diff_drive
git pull origin main
