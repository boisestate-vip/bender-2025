#!/bin/bash

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# update git submodules
bash $BENDER_SCRIPTS_DIR/update_submodules.sh

# initialize file we are going to store our successes in
mkdir -p $BENDER_DIR/bin
rm -f $BENDER_BIN_DIR/packages
touch $BENDER_DIR/bin/packages

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
   colcon build
   if (( $? != 0 )); then
      echo "${path##*/} FAILED" >> $BENDER_BIN_DIR/packages
   else
      echo "${path##*/} SUCCEEDED" >> $BENDER_BIN_DIR/packages
   fi
done

cat $BENDER_BIN_DIR/packages
