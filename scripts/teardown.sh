
shopt -s expand_aliases

echo "removing aliases..."
for f in "${scripts[@]}"; do
   name="${f##*/}"
   name="${name%%.*}"
   unalias $name 2&> /dev/null
done

rm -f $BENDER_BIN_DIR/bender_aliases

echo "removing paths..."

export BENDER_DIR=""
export BENDER_DEPENDENCIES_DIR=""
export BENDER_SCRIPTS_DIR=""

