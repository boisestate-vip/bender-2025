#!/bin/bash

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# check that correct number of arguments is passed
if (( $# != 3 )); then
   echo "usage: $0 [ workspace name ] [ system name ] [ package name ]"
   exit 1
fi

# enter the system directory
cd $BENDER_WORKSPACES_DIR/$1
mkdir -p $2/ros2_ws/src && cd $2/ros2_ws

# find the appropriate package
case "$3" in
   "rplidar" | "a1m8" )
      package=rplidar
      type=sensors ;;
   "ydlidar" | "gs2" )
      package=ydlidar
      type=sensors ;;
   "synexens" | "cs20" )
      package=synexens
      type=sensors ;;
   "realsense" )
      package=realsense
      type=sensors ;;
   "vectornav" )
      package=vectornav
      type=sensors ;;
   "vive" )
      package=vive
      type=sensors ;;
   "unitree" )
      package=unitree
      type=sensors ;;
   "diff_drive" )
      package=diff_drive
      type=nav ;;
   "kurome" )
      package=kurome
      type=nav ;;
   *)
      echo "invalid package specified"
      exit 1 ;;
esac

# copy package over to workspace
package="${package}_ws"
cp -r "$BENDER_DIR/src/$type/$package/src/" .

