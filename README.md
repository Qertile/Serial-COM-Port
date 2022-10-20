# Serial Test Program
This program using win32API to Tx/Rx from serial COM port under windows OS

## Overview
---
This document is for developers to get up and running.

## Getting Started
---
### Requirements
1. Windows operating system
2. GNU C compiler (e.g. gcc)
3. USB to TTL dongle
4. Your testing device

### Set up
- Create your own main.c or using the given example.c 
- Include serial.h and serial.c (if needed)
- Define your own testing commands base on the Interface Control Document (ICD) of the target device

### In main()
Make sure your code in main() follows the sequence below.

1. `initComPort()` 
   
   Passing number of COM port and baudrate as function arguments.
   
2. `GC(type)()`
 
   1. generate command, usually header
   2. generate command, usually the main content of testing command
   3. generate command, usually footer
   > Note: This step depends on user's testing command, if the user need advance seting of command (e.g lsb or msb) see `command_t` in serial.h
   
   > Note: While using `GC(ascii)`, don't forget add one more byte at the argument `cpn_len` (due to #define "abc" is a string in C, there is a '\0' at the end of string)


3. `printCommand()` 
    > Note: It is not necessary to print out the command, it's for user to check and debug.

4. `transmit()`
   
    There is no argument needed while calling this function. Number of bytes been sent will print on terminal.

5. `receive()`

    There is no argument needed while calling this function. The terminate condition of this function is when it received a 0x0D byte ('CR' in ascii code) or timeout. Number of bytes received and received message will print on terminal.
    

6. `GC(clear)(_command_)`

    Always remember to free the memory space after using it.

7. `closePort()`

    Don't forget close the port you just opened.

### Compile and Run
Open the terminal at the same directory with your main.c
```
gcc -o main main.c
./main.exe
```
Then the user should see the command has been sent and the message received from testing device.\


## History Version
---
see `change_log.md`

  
## License
---
There is no license or copyright, just use it :)