#!/bin/bash

# check that setup is done 
if [ "$BENDER_SETUP" != "true" ]; then
   echo "Setup script must be run"
   exit 1
fi

# check that an argument is passed
if (( $# != 1 )); then
   echo "Please pass a workspace name"
   exit 1
fi

mkdir -p $BENDER_WORKSPACES_DIR/$1

