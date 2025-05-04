
This is a simple program to
control the odrive with the keyboard.

# Compilation

## Normal

```
gcc -o command.e command.c
```

## Inverted control

```
# motor 0 is inverted
gcc -o command.invert.e command.c -DINVERTM0
```

```
# motor 1 is inverted
gcc -o command.invert.e command.c -DINVERTM1
```

## Debug

```
gcc -o command.debug.e command.c -DDEBUG
```

# Usage

## Movement 

\[ w, a, s, d, \] with the standard effects are the keys used for movement input
 * \<SPACEBAR> - stop moving
 * u - stop moving

## Arm Control

 * q - spin drum forward
 * e - spin drum backwards
 * \<SPACEBAR> - stop drum
 * r - raise arm
 * f - lower arm

## Program Control

 * i - increase speed, print current speed
 * o - decrease speed, print current speed
 * p - print system status
 * **k - quit program**

## Odrive Control

 * c - clear odrive errors
 * x - reboot odrives


