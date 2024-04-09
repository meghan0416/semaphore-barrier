#include "barrier.h"
#include <semaphore>

namespace synchronization
{
   /* Shared members */
   int enter; // The number of threads that have entered the barrier
   int exit; // The number of threads that have exited the barrier
   int threads; // The total number of threads in the program

   /* Mutex semaphores */
   std::counting_semaphore mutexEnter; // Lock for changing enter value
   std::counting_semaphore mutexExit; // Lock for changing exit value

   /* Barrier semaphores */
   std::counting_semaphore gate; // Gate for all threads to wait until the last gate enters
   std::counting_semaphore lastGate; // Special gate to wait only used by the last thread to enter


   barrier::barrier( int numberOfThreads ) {
      enter = 0; // Initialize the counts
      exit = 0;
      threads = numberOfThreads;
      
      mutexEnter(1); // Initialize the locks
      mutexExit(1);

      gate(0); // Initialize the gates
      lastGate(0);

      return;
   }

   barrier::~barrier( ) {
      // Write your code here
      ~gate();
      ~lastGate();
      ~mutexExit();
      ~mutexEnter();
      
      return;
   }

   void barrier::arriveAndWait( void ) {
      // Write your code here
      mutexEnter.acquire(); // Get the enter lock
      enter++; // Increment the count
      if(enter == threads) { // If I'm the last one
         enter = 0; // Reset the count
         gate.release(); // Start the chain of releasing
         lastGate.acquire(); // Wait to be released
         mutexEnter.release(); // Release the lock, end of this cycle
      }
      else {
         mutexEnter.release(); // Release the lock
         gate.acquire(); // Wait to be released
         mutexExit.acquire(); // Get the exit lock
         exit++;
         if(exit == threads-1) { // If I'm the last one
            exit = 0; // Reset the count
            mutexExit.release(); // Release the lock
            lastGate.release(); // Release the last thread
         }
         else {
            mutexExit.release(); // Release the lock
            gate.release(); // Release the next thread
         }
      }
      return;
   }

}
