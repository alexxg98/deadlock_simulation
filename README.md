# Using Mutex-Locks to Rrevent Deadlocks
This is an assignment for my CSC 33200 class (Operating Systems)

### What the project entails:
A single-lane bridge connects the two Vermont villages of North Tunbridge and South Tunbridge. Farmers in the two villages use this bridge to deliver their produce to the neighboring town. The bridge can become deadlocked if a northbound and a southbound farmer get on the bridge at the same time. (Vermont farmers are stubborn and are unable to back up.) 

Implement a solution using Pthreads that synchronizes the threads access to the output screen and prevents deadlock. In particular, represent northbound and southbound farmers as separate threads (use several threads representing the northbound and southbound farmers). Once a farmer is on the bridge the associated thread will: 
* Print to the screen "North (or South) Tunbridge farmer can cross the bridge" after the thread has granted access to the lock. 
* Print on the screen "North (or South) Tunbridge is traveling on the bridge…” as  
* Sleep for a random period (up to 3 seconds). 
* Print to the screen "North (or South) Tunbridge farmer has left the bridge" before releasing the lock. 

Meanwhile, the other village farmer is waiting for the bridge to be clear. 

## Running the Project
Clone the repository:

```bash
$ git clone https://github.com/alexxg98/deadlock_simulation.git
```

cd into the respository:
```bash
$ cd deadlock_simulation
```

run the program by:
```bash
$ g++ -pthread -o p3 assignment3.c
$ ./p3
```
