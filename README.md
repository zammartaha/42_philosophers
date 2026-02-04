*This project has been created as part of the 42 curriculum by tzammar.*

# Philosophers - I never thought philosophy would be so deadly

## Description

**Philosophers** is a project at 42 based on the famous "Dining Philosophers" problem proposed by Edsger Dijkstra.

The project is a simulation of a classic synchronization problem. Philosophers sit at a round table with a bowl of spaghetti in the middle. They alternate between three states: **eating**, **sleeping**, and **thinking**. To eat, a philosopher needs two forks. However, there are only as many forks as there are philosophers. This creates a resource contention problem where data races and deadlocks must be avoided to ensure no philosopher starves to death.

This project is divided into two parts:
1.  **Mandatory:** Using **Threads** and **Mutexes**.
2.  **Bonus:** Using **Processes** and **Semaphores**.

## Instructions

### Compilation
This generates the executable philo.

Bonus (Processes & Semaphores): To compile the process-based simulation, run:

Bash

make bonus
This generates the executable philo_bonus.

## Usage
**Both executables take the same arguments:**
```Bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
```
**Arguments:**
* **number_of_philosophers:** The number of philosophers and also the number of forks.
* **time_to_die (in ms):** If a philosopher doesn't start eating 'time_to_die' ms after the beginning of their last meal (or the start of the simulation), they die.
* **time_to_eat (in ms):** The time it takes for a philosopher to eat. During this time, they will hold two forks.
* **time_to_sleep (in ms):** The time a philosopher will spend sleeping.
* **number_of_times_each_philosopher_must_eat (optional):** If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

**Example:**
```Bash
./philo 5 800 200 200
```

## Features

### Mandatory (Threads)
* **One Process:** The simulation runs in a single process.
* **Threads:** Each philosopher is a thread.
* **Mutexes:** Forks are represented by mutexes to prevent multiple threads from accessing the same resource simultaneously.
* **Shared Memory:** Threads share the same memory space, requiring careful synchronization to avoid data races when checking the "death" flag or printing logs.

### Bonus (Processes)
* **Multiple Processes:** The simulation forks a new process for each philosopher.
* **Semaphores:** Forks are represented by a named semaphore. All forks are placed in the center of the table (a semaphore with a value equal to the number of philosophers).
* **No Shared Memory:** Since processes do not share memory, the main process waits for child processes (philosophers) to signal their status.
* **Kill signal:** If one philosopher dies, the main process detects it and kills all other child processes immediately.

## Resources

### References
* **[GeeksforGeeks - Multithreading in C](https://www.geeksforgeeks.org/multithreading-c-2/)** - Basics of thread creation.
* **[Man7.org - Pthread Mutex](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)** - Documentation on locking and unlocking mutexes.
* **[Man7.org - Semaphores](https://man7.org/linux/man-pages/man7/sem_overview.7.html)** - Overview of POSIX semaphores (used in bonus).
* **[CodeVault](https://www.youtube.com/c/CodeVault)** - Excellent video tutorials on C threads, race conditions, and semaphores.