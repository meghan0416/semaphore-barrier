/*
 *
 * Authors: Meghan Grayson and Vaishnavi Karaguppi
 * Last modified date: April 12, 2024
 * 
 * This is the class implementation for a reusable thread barrier with semaphores. 
 * 
 */

#include "barrier.h"

namespace synchronization
{
   /*
    * The constructor for the barrier.
    * Initializes the values of member variables as needed
    *    @param numberOfThreads -- an integer representing the number of threads that will use the barrier
    *    @returns -- none
    */
   barrier::barrier( int numberOfThreads ) {
      enter = 0; // Initialize the counts to zero
      exit = 0;
      threads = numberOfThreads; // Set the thread count
      sem_init(&mutexEnter, 0, 1); // Initialize the locks to 1
      sem_init(&mutexExit, 0, 1);
      sem_init(&gate, 0, 0); // Initialize the gates to 0
      sem_init(&lastGate, 0, 0); 
      return;
   }

   /*
    * The destructor for the barrier
    * Called by default when the barrier is out of scope
    *    @returns -- none
    */
   barrier::~barrier( ) {
      // Write your code here
      sem_destroy(&mutexEnter); // Destroy all the semaphores
      sem_destroy(&mutexExit);
      sem_destroy(&gate);
      sem_destroy(&lastGate);
      return;
   }
   
   /*
    * The function used by threads to synchronize.
    * Does not allow threads to pass through the method again until all threads have finished the iteration.
    *    @returns -- none
    */
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
