#include "barrier.h"

namespace synchronization
{
   barrier::barrier( int numberOfThreads ) {
      enter = 0; // Initialize the counts
      exit = 0;
      threads = numberOfThreads; // Set the thread count
      sem_init(&mutexEnter, 0, 1); // Initialize the locks
      sem_init(&mutexExit, 0, 1);
      sem_init(&gate, 0, 0); // Initialize the gates
      sem_init(&lastGate, 0, 0); 
      return;
   }

   barrier::~barrier( ) {
      // Write your code here
      sem_destroy(&mutexEnter); // Destroy all the semaphores
      sem_destroy(&mutexExit);
      sem_destroy(&gate);
      sem_destroy(&lastGate);
      return;
   }

   void barrier::arriveAndWait( void ) {
      // Write your code here
      sem_wait(&mutexEnter); // Get the enter lock
      enter++; // Increment the count
      if(enter == threads) { // If I'm the last one
         enter = 0; // Reset the count
         sem_post(&gate); // Start the chain of releasing
         sem_wait(&lastGate); // Wait to be released
         sem_post(&mutexEnter); // Release the lock, end of this cycle
      }
      else {
         sem_post(&mutexEnter); // Release the lock
         sem_wait(&gate); // Wait to be released
         sem_wait(&mutexExit); // Get the exit lock
         exit++;
         if(exit == threads-1) { // If I'm the last one
            exit = 0; // Reset the count
            sem_post(&mutexExit); // Release the lock
            sem_post(&lastGate); // Release the last thread
         }
         else {
            sem_post(&mutexExit); // Release the lock
            sem_post(&gate); // Release the next thread
         }
      }
      return;
   }

}
