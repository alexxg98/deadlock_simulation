/*CSC 33200 Operating Systems - Assignment 3
Alexandria Guo

Implement a solution using Pthreads that synchronizes the threads access to the output screen and prevent deadlock. In particular, represent northbound and southbound farmers as separate threads (use several threads representing the northbound and southbound farmers). Once a farmer is on the bridge the associated thread will:
1. Print to the screen "North/South Tunbridge farmer can cross the bridge" after the thread has granted access to the lock
2. Print of the screen "North/South Tunbridge is travelling on the bridge..." as
3. Sleep for a random period (up to 3 seconds)
Print to the screen "North/South Tunbridge has left the bridge" before releasing the lock
Meanwhile, the other village farmer is waiting for the bridge to be clear.
*/

//To compile run: g++ -pthread -o p3 assignment3.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 //Number of threads; Number of farmers for each North and South

//Set up mutex to nitialize later
pthread_mutex_t first_mutex = PTHREAD_MUTEX_INITIALIZER;

//Inital count for each farmer
int North = 1;
int South = 1;

//Method for bridge crossing
void Bridge(char direction[], int value){
  srand(time(NULL)); //Set seed for random number
  int sleep_period = rand()%4 + 1; //Random number between 1 and 3
  printf("%s Tunbridge #%d farmer is traveling the bridge...\n", direction, value);
  sleep(sleep_period); //Sleep for random period defined above
}

//Thread for North Farmer
void *NorthFarmer(void *arg){
  pthread_mutex_lock(&first_mutex); //lock mutex when farmer on bridge
  char direction[] = "North";
  printf("%s Tunbridge #%d farmer can cross the bridge\n", direction, North);
  Bridge(direction, North); //Farmer traveling across bridge
  printf("%s Tunbridge #%d farmer has left the bridge\n\n", direction, North);
  North++;
  pthread_mutex_unlock(&first_mutex); //unlock mutex when farmer is done
  pthread_exit(0); //Terminate the calling thread
}

//Thread for South Farmer
void *SouthFarmer(void *arg){
  pthread_mutex_lock(&first_mutex); //lock mutex when farmer on bridge
  char direction[] = "South";
  printf("%s Tunbridge #%d farmer can cross the bridge\n", direction, South);
  Bridge(direction, South); //Farmer traveling across bridge
  printf("%s Tunbridge #%d farmer has left the bridge\n\n", direction, South);
  South++;
  pthread_mutex_unlock(&first_mutex); //unlock mutex when farmer is done
  pthread_exit(0); //Terminate the calling thread
}


int main(int argc, char const *argv[]) {
  pthread_t North[NUM_THREADS]; //North Thread
  pthread_t South[NUM_THREADS]; //South Thread
  pthread_mutex_init(&first_mutex, NULL); //Initialize Mutex

  //Create North and South Farmer threads
  for(int i=0; i<NUM_THREADS; i++){
    int CreateFirst = pthread_create(&North[i], NULL, NorthFarmer, NULL);
    int CreateSecond = pthread_create(&South[i], NULL, SouthFarmer, NULL);
    if (CreateFirst != 0 || CreateSecond != 0) {
      fprintf(stderr, "Thread Creation Failed");
      return 1;
    }
  }
  //Wait for each thread to finish
  for(int i=0; i<NUM_THREADS; i++){
    int JoinFirst = pthread_join(North[i], NULL);
    int JoinSecond = pthread_join(South[i], NULL);
    if (JoinFirst != 0 || JoinSecond != 0) {
      fprintf(stderr, "Join Failed");
      return 1;
    }
  }
  //Destroy the mutex lock
  pthread_mutex_destroy(&first_mutex);
  return 0;
}
