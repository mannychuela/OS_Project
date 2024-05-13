This program in C++ simulates four CPU scheduling algorithms and three page replacement algorithms. 

A single Linked list is data structure for this program

- CPU scheduling algorithms: 

    + First Come First Serve (FCFS): This is the simplest scheduling algorithm. In this type of algorithm, processes are dispatched according to their arrival time in the ready queue.

    + Shortest Job First (Preemptive): In this type of scheduling, the process with the smallest execution time is selected for execution next. It can be preemptive, where a process is interrupted when a new process with less burst time arrives.

    + Priority Scheduling: In this type of scheduling, each process is assigned a priority. The process with the highest priority (smallest integer = highest priority) is to be executed first and so on.

    + Round Robin (RR): Round Robin is the preemptive process scheduling algorithm. Each process is provided a fix time to execute, it is called a quantum. Once a process is executed for a given time period, it is preempted and other process executes for a given time period.

When the user selects an algorithm, the program will display the results in a table, showing the order in which the processes were executed with their corresponding waiting times, and turnaround times.

- Page replacement algorithms:

    + First-In First-Out (FIFO): Replaces the oldest page in memory when it's necessary to load a new page.
    
    + Least Recently Used (LRU): eplaces the least recently used page when it's necessary to load a new page into memory.

    + Optimal Algorithm: Replaces the page that will not be used for the longest time in the future.

Each algorithm has to return the number of page faults.

