#include "IntDLList.h" // Double linked list header file
#include "IntSLList.h" // single linked list header file
#include <iomanip>     // output formatting
#include <iostream>

using namespace std;

/**********************************************************************************************************
 * Struct to represent a process with its attributes *
 ***********************************************************************************************************/
struct Process {
    int id;             // Identifier for the process
    int arrivalTime;    // Time at which process arrive in the ready queue
    int burstTime;      // Time required for the process to complete
    int completionTime; // Time at which process is completed
    int waitingTime; // Time required for the process to wait in the ready queue
    int turnaorundTime; // Total time taken by the process from its arrival time
                        // to completion
    int remainingBurstTime; // The remaining burst time of the process in a
                            // preemptive algorithm
    int priority;           // Priority of the process in process scheduler
};
/*********************************************************************************************************
**********************************************************************************************************/

/*********************************************************************************************************
 *   Function to run the First Come First Served (FCFS) scheduling algorithm *
 **********************************************************************************************************/
void runFCFS(IntSLList<Process>& processes, int n) {
    int currentTime = 0;         // Initialize the current time to 0
    int totalWaitingTime = 0;    // Initialize the total waiting time to 0
    int totalTurnaroundTime = 0; // Initialize the total turnaround time to 0

    IntSLList<Process>
        arrivalQueue; // create a single linked list called arrivalQueue to store
                      // the arriving processes

    // Output formatting for the process information table
    cout << "\t\t FCFS SCHEDULING" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "|          Process Information Table          |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;
    cout << "| Process # | Waiting time | Turn Around time |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;

    // Main scheduling loop
    while (!processes.isEmpty() || !arrivalQueue.isEmpty()) {

        // Check if any processes have arrived and move them from the original list
        // to the arrival queue list
        while (!processes.isEmpty() &&
            processes.getHead()->getInfo().arrivalTime <= currentTime) {

            arrivalQueue.addToTail(
                processes.getHead()
                ->getInfo());       // Add the process list to the arrival queue
            processes.deleteFromHead(); // Remove the process from the original list
        }

        if (!arrivalQueue.isEmpty()) {

            // Get the first process in the arrival queue
            Process currentProcess =
                arrivalQueue.getHead()
                ->getInfo(); // Get the process at the front of the arrival queue
            arrivalQueue
                .deleteFromHead(); // Remove the process from the arrival queue

            // Ensure we don't move time backwards if there's idle time
            if (currentProcess.arrivalTime > currentTime) {

                currentTime =
                    currentProcess.arrivalTime; // Set the current time to the arrival
                                                // time of the current process
            }

            // Calculate the completion time and other process metrics
            currentProcess.completionTime =
                currentTime + currentProcess.burstTime; // Calculate the completion
                                                        // time of the current process
            currentProcess.turnaorundTime =
                currentProcess.completionTime -
                currentProcess.arrivalTime; // Calculate the turnaround time of the
                                            // current process
            currentProcess.waitingTime =
                currentProcess.turnaorundTime -
                currentProcess
                .burstTime; // Calculate the waiting time of the current process

        // Update the totals for turnaround and waiting times
            totalTurnaroundTime +=
                currentProcess
                .turnaorundTime; // Add the turnaround time of the current process
                                 // to the total turnaorund time
            totalWaitingTime +=
                currentProcess.waitingTime; // Add the waiting time of the current
                                            // processs to the total waiting time

            // Display process information in the table
            cout << "| " << setw(9) << currentProcess.id << " | " << setw(12)
                << currentProcess.waitingTime << " | " << setw(15)
                << currentProcess.turnaorundTime << " |" << endl;

            currentTime =
                currentProcess.completionTime; // Update the current time to the
                                               // completion time of the current time
        }
        else {
            currentTime++; // If there are no processes in the queue, simulate time
                           // passing
        }
    }

    // Calculate and display the average turnaround and waiting times
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) /
        n; // Calculate the average turnaround time
    double averageWaitingTime = static_cast<double>(totalWaitingTime) /
        n; // Caluclate the average waiting time

// Print the results
    cout << "+----------------------------------------------+" << endl;
    cout << "     --- Average Turnaround time: " << averageTurnaroundTime
        << " ---" << endl;
    cout << "     --- Average Waiting time: " << averageWaitingTime << " ---"
        << endl;
}
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
 * Function to run the Shortest Job First (SJF) Preemptive scheduling algorithm
 **
 *******************************************************************************************************************************************/
void runSJFPreemptive(IntSLList<Process>& processes, int n) {

    int currentTime = 0;           // Current time
    int totalWaitingTime = 0;      // Total waiting time of all processes
    int totalTurnaroundTime = 0;   // Total turnaround time of all processes
    IntSLList<Process> readyQueue; // Queue for ready processes
    IntSLList<Process> executedProcesses; // List for executed processes

    // Main scheduling loop
    while (!processes.isEmpty() || !readyQueue.isEmpty()) {

        // Move arriving processes to the ready queue
        while (!processes.isEmpty() &&
            processes.getHead()->getInfo().arrivalTime <= currentTime) {

            readyQueue.sortInsert(
                processes.getHead()->getInfo()); // Sort the processes by arrival time
            processes.deleteFromHead();          // Remove the processes
        }

        //
        if (!readyQueue.isEmpty()) {
            Process p =
                readyQueue.getHead()
                ->getInfo(); // Get the process at the front of the ready queue
            readyQueue.deleteFromHead(); // Remove the processes from the ready queue
            p.remainingBurstTime--;      // Decrement the reamining burst time of the
                                         // process

            // if the process has completet execution
            if (p.remainingBurstTime == 0) {
                p.completionTime =
                    currentTime + 1; // Calculate the completion time of the process
                p.turnaorundTime =
                    p.completionTime -
                    p.arrivalTime; // Calculate the turnaround time of the process
                p.waitingTime =
                    p.turnaorundTime -
                    p.burstTime; // Calculate the waiting time of the process

                // Update total turnaround and waiting times
                totalWaitingTime +=
                    p.waitingTime; // Calculate the total waiting time of all processes
                totalTurnaroundTime +=
                    p.turnaorundTime; // Calculate the total turnaround time of all
                                      // processes

                executedProcesses.addToTail(
                    p); // Add the process to the list of executed processes
            }
            else {
                readyQueue.sortInsert(p); // Put the process back in the ready queue
            }
            currentTime++; // Update the current time by incrementing it
        }
        else {
            currentTime++; // If there are no processes in the ready queue, simulate
                           // time passing
        }
    }

    // Output formatting for the process information table
    cout << "\t\t SJF SCHEDULING" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "|          Process Information Table          |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;
    cout << "| Process # | Waiting Time | Turnaround Time  |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;

    // Display information for executed processes
    while (!executedProcesses.isEmpty()) {
        Process p = executedProcesses.getHead()
            ->getInfo(); // Get the process at the front of the list
        executedProcesses.deleteFromHead(); // Remove the process from the list

        // Output information for the process
        cout << "| " << setw(9) << p.id << " | " << setw(12) << p.waitingTime
            << " | " << setw(15) << p.turnaorundTime << " |" << endl;
    }

    // Calculate and display the average turnaround and waiting times
    double averageWaitingTime = static_cast<double>(totalWaitingTime) /
        n; // Calculate average waiting time
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) /
        n; // Calculate average turnaround time

    cout << "+-----------+--------------+------------------+" << endl;
    cout << "     --- Average waiting time: " << averageWaitingTime << " ---"
        << endl;
    cout << "     --- Average turnaround time: " << averageTurnaroundTime
        << " ---" << endl;
}
/********************************************************************************************************************************************
********************************************************************************************************************************************/

/*******************************************************************************************************************************************
 * Function to run the Priority Scheduling Preemptive algorithm *
 *******************************************************************************************************************************************/
void runPriorityPreemptive(IntSLList<Process>& processes, int n) {
    int currentTime = 0; // Initialize the current time to 0
    int totalWaitingTime =
        0; // Initialize the total waiting time of all proceses to 0
    int totalTurnaroundTime =
        0; // Total turnaround time of all processes initialized to 0
    IntSLList<Process> readyQueue;        // Create a single linked list
    IntSLList<Process> executedProcesses; // List for executed processes

    // Main scheduling loop
    while (!processes.isEmpty() || !readyQueue.isEmpty()) {

        // Move arriving processes to the ready queue
        while (!processes.isEmpty() &&
            processes.getHead()->getInfo().arrivalTime <= currentTime) {

            readyQueue.sortPriority(
                processes.getHead()->getInfo()); // Sorts the processes in readyQueue
                                                 // based on priority
            processes.deleteFromHead();          // Remove the process from the list
        }

        // Execute the process with the highest priority
        if (!readyQueue.isEmpty()) {

            Process p =
                readyQueue.getHead()->getInfo(); // Gets the process with the highset
                                                 // priority from the readyQueue list
            readyQueue.deleteFromHead();         // Remove the process from the list

            // Calculate the waiting time for the process
            if (p.remainingBurstTime == p.burstTime) {

                p.waitingTime =
                    currentTime -
                    p.arrivalTime; // Calculate the waiting time for the process
            }

            p.remainingBurstTime--; // Decrement the remaining burst time of the
                                    // process

            // Calculate process turnaround time
            if (p.remainingBurstTime == 0) {
                p.completionTime = currentTime + 1; // Set completion time
                p.turnaorundTime = p.completionTime - p.arrivalTime; // TAT Formula

                // Update total turnaround and waiting times
                totalWaitingTime +=
                    p.waitingTime; // Updates the total waiting time by adding the
                                   // waiting time of the process
                totalTurnaroundTime +=
                    p.turnaorundTime; // Updates the total turnaround time by adding the
                                      // turnaround time of the process

                executedProcesses.addToTail(
                    p); // Add the process to the list of executed processes
            }
            else {
                readyQueue.sortPriority(p); // switched from sort insert // Sort the
                                            // process back in the readyQueue list
            }
            currentTime++; // Increment time
        }
        else {
            currentTime++; // If there are no processes in the ready queue, simulate
                           // time passing
        }
    }

    // Output formatting for the process information table
    cout << "\t\t PRIORITY SCHEDULING" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "|          Process Information Table          |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;
    cout << "| Process # | Waiting Time | Turnaround Time  |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;

    // Display information for executed processes
    while (!executedProcesses.isEmpty()) {

        Process p =
            executedProcesses.getHead()
            ->getInfo(); // Get the process from the executedProcess list
        executedProcesses
            .deleteFromHead(); // Remove the process from the exexcuteProcess list

        cout << "| " << setw(9) << p.id << " | " << setw(12) << p.waitingTime
            << " | " << setw(15) << p.turnaorundTime << " |" << endl;
    }

    // Calculate and display the average turnaround and waiting times
    double averageWaitingTime = static_cast<double>(totalWaitingTime) /
        n; // Calculate the average waiting time
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) /
        n; // Calculate the average turnaround time

    cout << "+-----------+--------------+------------------+" << endl;
    cout << "     --- Average waiting time: " << averageWaitingTime << " ---"
        << endl;
    cout << "     --- Average turnaround time: " << averageTurnaroundTime
        << " ---" << endl;
}
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
 * Function to run the Round Robin (RR) scheduling algorithm *
 *******************************************************************************************************************************************/
void runRoundRobin(IntSLList<Process>& processes, int n, int quantumTime) {
    int currentTime = 0;           // Current time
    int totalWaitingTime = 0;      // Total waiting time of all processes
    int totalTurnaroundTime = 0;   // Total turnaround time of all processes
    IntSLList<Process> readyQueue; // Queue for ready processes
    IntSLList<Process> executedProcesses; // List for executed processes

    // Main scheduling loop
    while (!processes.isEmpty() || !readyQueue.isEmpty()) {

        // Move arriving processes to the ready queue
        while (!processes.isEmpty() &&
            processes.getHead()->getInfo().arrivalTime <= currentTime) {

            readyQueue.addToTail(
                processes.getHead()->getInfo()); // Add the process to the ready queue
            processes.deleteFromHead(); // Remove the process from the processes list
        }

        // Execute processes in the ready queue
        if (!readyQueue.isEmpty()) {

            Process p = readyQueue.getHead()
                ->getInfo(); // Get the first process in the ready queue
            readyQueue.deleteFromHead(); // Remove the process from the ready queue

            /*  To calculate the time slice, we used the conditional operator ?. The
             * condition before ? evaluates if the burst time is greater than the
             * quantum time that the user has pre-determined.
             *
             *  Two values can be assigned to timeSlice, depending on the condition.
             * The value of quantumTime will be assigned if true, and the value of
             * remainingBurstTime will be assigned if false.
             */
            int timeSlice = (p.remainingBurstTime > quantumTime)
                ? quantumTime
                : p.remainingBurstTime;

            currentTime +=
                timeSlice; // Update the current time based on the value of timeSlice
            p.remainingBurstTime -=
                timeSlice; // Update the remaining burst time of the process

            // If the process has finished, add it to the list of executed processes
            if (p.remainingBurstTime == 0) {

                p.completionTime =
                    currentTime; // Set the completion time of the process
                p.turnaorundTime =
                    p.completionTime -
                    p.arrivalTime; // Calculate the turnaround time of the process
                p.waitingTime =
                    p.turnaorundTime -
                    p.burstTime; // Calculate the waiting time of the process

                // Update total turnaround and waiting times
                totalWaitingTime += p.waitingTime; // Add the waiting time of the
                                                   // process to the total waiting time
                totalTurnaroundTime +=
                    p.turnaorundTime; // Add the turnaround time of the process to the
                                      // total turnaround time

                executedProcesses.addToTail(
                    p); // Add the process to the list of executed processes
            }
            else {
                readyQueue.addToTail(p); // Put the process back in the ready queue
            }
        }
        else {
            currentTime++; // If there are no processes in the ready queue, simulate
                           // time passing
        }
    }

    // Output formatting for the process information table
    cout << "\t\t ROUND ROBIN SCHEDULING" << endl;
    cout << "+---------------------------------------------+" << endl;
    cout << "|          Process Information Table          |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;
    cout << "| Process # | Waiting Time | Turnaround Time  |" << endl;
    cout << "+-----------+--------------+------------------+" << endl;

    // Display information for executed processes
    while (!executedProcesses.isEmpty()) {

        Process p = executedProcesses.getHead()
            ->getInfo();        // Get the first process in the list
        executedProcesses.deleteFromHead(); // Remove the process from the list

        cout << "| " << setw(9) << p.id << " | " << setw(12) << p.waitingTime
            << " | " << setw(15) << p.turnaorundTime << " |" << endl;
    }

    // Calculate and display the average turnaround and waiting times
    double averageWaitingTime = static_cast<double>(totalWaitingTime) /
        n; // Calculate the average waiting time
    double averageTurnaroundTime = static_cast<double>(totalTurnaroundTime) /
        n; // Calculate the average turnaround time

    cout << "+-----------+--------------+------------------+" << endl;
    cout << "     --- Average waiting time: " << averageWaitingTime << " ---"
        << endl;
    cout << "     --- Average turnaround time: " << averageTurnaroundTime
        << " ---" << endl;
}
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
 * Function to prompt the user to enter the time quantum for the Round Robin
 *algorithm                                                     *
 *******************************************************************************************************************************************/
int timeQuantumPrompt(int& timeQuantum) {

    cout << "Enter the time quantum: "; // Prompt the user to enter the quantum
                                        // time
    cin >> timeQuantum;
    return timeQuantum; // Return the quantum time determined by the user
}
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/

/******************************************************************************************************************************************
 * Function to create a deep copy of the process list for case 5 *
 *******************************************************************************************************************************************/
IntSLList<Process> deepCopy(IntSLList<Process>& processes) {
    IntSLList<Process> copy; // Create a new list to store the deep copy

    IntSLLNode<Process>* current =
        processes
        .getHead(); // Set the current node to the head of the original list

    while (current != nullptr) {

        // Create a new node with the same info and add it to the copy list
        copy.addToTail(current->getInfo());
        current = current->getNext();
    }

    return copy;
}
/*******************************************************************************************************************************************
*******************************************************************************************************************************************/

/*******************************************************************************************************************************************
 *   Function to display scheduling algorithm menu *
 *******************************************************************************************************************************************/
void schedulingMenu() {

    cout << "Choose the scheduling algorithm:" << endl;
    cout << "1. First Come First Served (FCFS)" << endl;
    cout << "2. Shortest Job First (Preemptive)" << endl;
    cout << "3. Priority Scheduling (Preemptive)" << endl;
    cout << "4. Round Robin (RR)" << endl;
    cout << "5. All of the above" << endl;
}

/********************************************************************************************************************************************
 *  Main Program * This main program contains a menu handled by a swtich case,
 *that depending on the users choice, will execute the desired algoritm or all *
 *  at once. *
 ********************************************************************************************************************************************/

int main() {

    IntSLList<Process> processes; // List to hold processes
    int n;
    int choice; // Variable choice stores the users choice for the algorithm
    int timeQuantum = 0;

    // Start of the program
    cout << "Operating System Project: scheduling algorithm and memory "
        "management\n"
        << endl;
    cout << "Please select one of the two options to begin." << endl;
    cout << "1. Scheduling Algorithms" << endl;
    cout << "2. Memory Management" << endl;
    cin >> choice;

    // main menu
    switch (choice) {

    case 1:

        cout << "Enter number of processes (10 max): "; // Prompt the user how many
                                                        // processes they want to
                                                        // enter, mo more than 10
        cin >> n; // Input the number of processes

        // Input validation for when the user enters the number of processes
        if (n <= 0 || n > 10) {
            cout << "Invalid number of processes. Exiting program..."
                << endl; // Prints message if the condition is met
            return 1;     // Exit program
        }

        // Input process information for the amount of processes pre-determined by
        // the user
        for (int i = 0; i < n; ++i) {
            Process p; // Creates a new procees called p

            cout << "Enter process information..."
                << endl;             // Prompt the user to input process information
            cout << "Process ID: ";   // Promtt user to enter the process ID
            cin >> p.id;              // Input the process ID
            cout << "Arrival Time: "; // Prompt the user for the arrival time
            cin >> p.arrivalTime;     // Input the arrival time
            cout << "Burst Time: ";   // Prompt the user for the burst time
            cin >> p.burstTime;       // Input the burst time
            cout << "Priority: ";     // Prompt the usre for the priority
            cin >> p.priority;        // Input the priority

            p.remainingBurstTime = p.burstTime;
            processes.addToTail(p); // Add the process to the single linked list
        }

        int choice2;
        // Prompt the user to choose the algorithms
        schedulingMenu();
        cin >> choice2; // Input the choice

        // Switch case that executes the desired algorithm
        switch (choice2) {

            // FCFS
        case 1:
            runFCFS(processes,
                n); // Call the FCFS function that will run the algorithm
            break;

            // SJF
        case 2:
            runSJFPreemptive(
                processes, n); // Call the SJF-Preemptive that will run the algorithm
            break;

            // PRIORITY
        case 3:
            runPriorityPreemptive(
                processes,
                n); // Call the Priority-Preemptive that will run the algorithm
            break;

            // ROUND ROBIN
        case 4:

            timeQuantumPrompt(timeQuantum); // Calls function that prompts the user to
                                            // enter the quantum time
            runRoundRobin(
                processes, n,
                timeQuantum); // Calls funciton that runs the Round Robin algorithm
            break;

            // RUN ALL ALGORITHMS
        case 5: {
            // Create a deep copy of the original list for each algorithm to avoid
            // data loss
            IntSLList<Process> fcfs =
                deepCopy(processes); // Copy the processes to a new single linked list
                                     // called fcfs
            runFCFS(
                fcfs,
                n); // Call runFCFS function to run algorithm and print its info table

            IntSLList<Process> sjf =
                deepCopy(processes); // Copy the processes to a new single linked list
                                     // called sjf
            runSJFPreemptive(
                sjf,
                n); // Call runSJFPreemptive to run algorithm and print its info table

            IntSLList<Process> priority =
                deepCopy(processes); // Copy the processes to a new single linked list
                                     // called priority
            runPriorityPreemptive(priority, n); // Call runPriorityPreemptive to run
                                                // algorithm and prints its info table

            // Time quantum for Round Robin
            timeQuantumPrompt(timeQuantum); // Prompt user for time quantum
            IntSLList<Process> roundRobin =
                deepCopy(processes); // Copy the proceeses to a new single linked list
                                     // called roundRobin
            runRoundRobin(roundRobin, n,
                timeQuantum); // Call runRoundRobin to run algorithm and
                              // print its info table
            break;
        }

              // if invalid input
        default:
            cout << "Invalid choice. Exiting." << endl;
            return 1;
        }

        //break case 1
        break;

    case 2:

        int numberOfFrames;

        cout << "Enter the number of frames: ";
        cin >> numberOfFrames;

        //frame input validation
        while (numberOfFrames < 1) {
            cout << "Enter a valid number of frames!" << endl;
            cout << "Enter the number of frames: ";
            cin >> numberOfFrames;
        }
        cout << endl;


        IntDLList<int> referenceList; //reference string implemented using a Doubly Linked List of integer data in nodes
        int numberOfReferences;       //reference amount input

        //reference amount input prompt
        cout << "Enter the number of references (MAX 20): ";
        cin >> numberOfReferences;

        //reference input validation
        while (numberOfReferences <= 0 || numberOfReferences > 20) {

            cout << "Enter a valid number of references!" << endl;
            cout << "Enter the number of references (MAX 20): ";
            cin >> numberOfReferences;
        }

        //reference string input prompt
        cout << "Enter the reference string: ";
        for (int i = 0; i < numberOfReferences; i++) {
            int referenceID;
            cin >> referenceID;
            referenceList.addToTail(referenceID);

        }

        //print reference list
        cout << "\t\tReference String: ";
        referenceList.printList();
        cout << endl;

        //calculate page faults for each algorithm (LRU, FIFO and Optimal)
        int LRUPageFaults = referenceList.simulateLRU(numberOfFrames);

        int FIFOPageFaults = referenceList.simulateFIFO(numberOfFrames);

        int OptimalPageFaults = referenceList.simulateOptimal(referenceList, numberOfFrames);

        //OUTPUT TABLE:

        cout << "\t\t _____________________________________________________" << endl;
        cout << "\t\t|                                                     |" << endl;
        cout << "\t\t|       MEMORY ALGORITHMS INFORMATION TABLE           |" << endl;
        cout << "\t\t|_____________________________________________________|" << endl;
        cout << "\t\t|                        |                            |" << endl;
        cout << "\t\t|      ALGORITHM         |       # PAGE FAULTS        |" << endl;
        cout << "\t\t|        FIFO            |" << setw(15) << FIFOPageFaults << setw(14) << "|" << endl;
        cout << "\t\t|        LRU             |" << setw(15) << LRUPageFaults << setw(14) << "|" << endl;
        cout << "\t\t|      OPTIMAL           |" << setw(15) << OptimalPageFaults << setw(14) << "|" << endl;
        cout << "\t\t|________________________|____________________________|" << endl;


        break;
    }

    return 0; // end program
}
