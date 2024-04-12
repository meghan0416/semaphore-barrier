# Project: Reusable Barrier with Semaphores
by: Meghan Grayson (meg230001)
    Vaishnavi Karaguppi (vxk210093)
Date: April 12, 2024

This project implements a reusable barrier for N threads through the use of POSIX semaphores. All threads must wait inside the barrier until all threads have arrived, and they cannot re-enter the barrier until all threads have exited.

To test the barrier, a multi-threaded program solving the prefix sum problem using Hillis and Steele's parallel algorithm was provided. 


## Instructions ##
Clone or download the project repository.
Navigate to the project directory.
Compile the program using the provided Makefile.
Run the compiled program with appropriate command-line arguments as mentioned in the "Usage" section.


## Usage ##
To run the program, use the following command-line arguments in bash:
./prefix-sum <Input-Size> <Number-Of-Threads>

Note that:
<Input-Size> must be an integer greater than zero.
<Number-Of-Threads> must be an integer greater than zero.