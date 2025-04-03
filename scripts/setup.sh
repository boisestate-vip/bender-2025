#!/bin/bash

# the the directory that this script is being run in
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# setup all the variables used by the other scripts
export BENDER_SETUP="true"
export BENDER_DIR=$SCRIPT_DIR/..
export BENDER_DEPENDENCIES_DIR=$BENDER_DIR/dependencies
export BENDER_SCRIPTS_DIR=$BENDER_DIR/scripts
export BENDER_BIN_DIR=$BENDER_DIR/bin
export BENDER_WORKSPACES_DIR=$BENDER_DIR/workspaces

# ensures we can set the hostname seperate of an environment if needed
if [ -z "$BENDER_HOSTNAME" ]; then
   export BENDER_HOSTNAME=$(<$BENDER_BIN_DIR/name)
fi

shopt -s nullglob

scripts=($BENDER_SCRIPTS_DIR/*)

mkdir -p $BENDER_BIN_DIR
rm -f $BENDER_BIN_DIR/bender_aliases


# export all the scripts into the local env exported as their
# names so that they can be run easier
for f in "${scripts[@]}"; do
   if [ "$f" != "$BENDER_SCRIPTS_DIR/setup.sh" ] && \
      [ "$f" != "$BENDER_SCRIPTS_DIR/teardown.sh" ]; then
      name="${f##*/}"
      name="${name%%.*}"
      echo "alias $name='$f'" >> $BENDER_BIN_DIR/bender_aliases
      alias $name='$f'
   fi
done

source $BENDER_BIN_DIR/bender_aliases

# export the directory openvr is in so that
# the later build files can find it
export OPENVR_DIRECTORY="$BENDER_DEPENDENCIES_DIR/openvr"
