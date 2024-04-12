#ifndef BARRIER_H
#define BARRIER_H


#include <semaphore.h>

namespace synchronization
{


   // Provides a reusable barrier
   class barrier {
   private:
      int enter; //The number of threads that have entered the barrier
      int exit; //The number of threads that have exited the barrier
      int threads; //The total number of threads in the program
      /* Mutexes */
      sem_t mutexEnter; //Lock for changing enter value
      sem_t mutexExit; //Lock for changing exit value
      /* Gates */
      sem_t gate; //Gate for all threads to wait until the last thread enters
      sem_t lastGate; //Special gate to wait only used by the last thread to enter

   public:

      // Constructor
      barrier( int numberOfThreads );

      // Destructor
      ~barrier( );

      // Function to wait at the barrier until all threads have reached the barrier
      void arriveAndWait( void );
   };

}

#endif
