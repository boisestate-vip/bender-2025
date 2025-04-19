
This is a simple program to
control the odrive with the keyboard.

# Compilation

## Normal

gcc -o controller.e controller.c
gcc -o controller2.e controller.c

## Inverted control

gcc -o controller.invert.e controller.c -DINVERT
gcc -o controller2.invert.e controller2.c -DINVERT

## Debug

gcc -o controller.debug.e controller.c -DDEBUG
gcc -o controller2.debug.e controller2.c -DDEBUG

# Usage

## Movement 

\[ w, a, s, d, \] with the standard effects are the keys used for movement input

## Program Control

 * i - increase speed, print current speed
 * o - decrease speed, print current speed
 * **q - quit program**
