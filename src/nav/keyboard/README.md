
This is a simple program to
control the odrive with the keyboard.

# Compilation

## Normal

gcc -o controller.e controller.c

## Inverted control

gcc -o controller.invert.e controller.c -DINVERT

## Debug

gcc -o controller.debug.e controller.c -DDEBUG
