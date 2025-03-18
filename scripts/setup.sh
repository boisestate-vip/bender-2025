#!/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

echo "exporting paths..."

export BENDER_DIR=$SCRIPT_DIR/..
export BENDER_DEPENDENCIES_DIR=$BENDER_DIR/dependencies
export BENDER_SCRIPTS_DIR=$BENDER_DIR/scripts
export BENDER_BIN_DIR=$BENDER_DIR/bin

shopt -s nullglob

echo "exporting aliases..."

scripts=($BENDER_SCRIPTS_DIR/*)

mkdir -p $BENDER_BIN_DIR

for f in "${scripts[@]}"; do
   if [ "$f" != "$BENDER_SCRIPTS_DIR/setup.sh" ] && \
      [ "$f" != "$BENDER_SCRIPTS_DIR/teardown.sh" ]; then
      name="${f##*/}"
      name="${name%%.*}"
      echo "alias $name='$f'" >> $BENDER_BIN_DIR/bender_aliases
   fi
done

source $BENDER_BIN_DIR/bender_aliases
