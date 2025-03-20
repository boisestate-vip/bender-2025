#!/bin/bash

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# package directories
packages=("$BENDER_DIR/src/sensors/realsense_ws" \
          "$BENDER_DIR/src/sensors/rplidar_ws" \
          "$BENDER_DIR/src/sensors/synexens_ws" \
          "$BENDER_DIR/src/sensors/unitree_ws" \
          "$BENDER_DIR/src/sensors/vectornav_ws" \
          "$BENDER_DIR/src/sensors/vive_ws" \
          "$BENDER_DIR/src/sensors/ydlidar_ws" \
          "$BENDER_DIR/src/nav/kurome_ws" \
          "$BENDER_DIR/src/nav/diff_drive_ws")

for path in ${packages[@]}; do
   cd $path
   rm -rf build install log
done

# dependency directories
deps=("$BENDER_DEPENDENCIES_DIR/YDLidar-SDK" \
      "$BENDER_DEPENDENCIES_DIR/ceres-solver-2.2.0" \
      "$BENDER_DEPENDENCIES_DIR/librealsense-2.53.1" \
      "$BENDER_DEPENDENCIES_DIR/openvr" \
      "$BENDER_DEPENDENCIES_DIR/pcl" \
      "$BENDER_DEPENDENCIES_DIR/unitree_lidar_sdk")

for path in ${deps[@]}; do
   cd $path
   rm -rf build 
done
