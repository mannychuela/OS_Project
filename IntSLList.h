#include "IntSLLNode.h" // include node class
#include <iostream> // for input-output
#include <stdio.h> 

using namespace std; //standard namespace

template <class T> class IntSLList {
public:
    IntSLList();  // Default constructor: creates an empty list
    ~IntSLList(); // Destructor: deallocate memory
    void addToHead(T val); // addToHead(T val): creates a new node with val as info,
    // and this new node is the new head

    void addToTail(const T& val);  //creates a new node with val as
  // info, and this new node is the new tail

    void
        deleteFromHead(); // deleteFromHead: remove head from the list,
                          // the new head is the previous head-> next
                          // if the list had only one node, head and tail point null
    void deleteFromTail();
    bool isEmpty(); // In the list is empty, returns true; otherwise, returns
                    // false
    void sortInsert(T val); // sortInsert(T val): creates a new node, and it is
                            // inserted sortly
    void sortPriority(const T& val); // sortPriority(T val) creates a new node,
                                     // and it is sorted based on priority
    void insert(int pos, T val); // insert(int pos, T val): creates a new node,
                                 // and it is inserted in position pos
    void printList();            // printList(): prints all nodes in the list
    int countNodes();            // return number of nodes in the list
    IntSLLNode<T>* getHead();    // return head

private:
    IntSLLNode<T>* head; // A pointer to the first node
    IntSLLNode<T>* tail; // A pointer to the last node
};

template <class T>
IntSLList<T>::IntSLList() // Default Constructor
{
    tail = head = 0;
}

template <class T>
IntSLList<T>::~IntSLList() // Destructor
{
    // Declare a pointer prtNode
    IntSLLNode<T>* prtNode;
    // prtNode points head
    prtNode = head;

    // While there is a node in the list, remove it
    while (prtNode != 0) {
        // prtNode points head-> next
        prtNode = head->getNext();
        // delete head
        delete head;
        // the new head is prtNode
        head = prtNode;
    }
}

template <class T> void IntSLList<T>::addToHead(T val) {
    head =
        new IntSLLNode<T>(val, head); // crear nodo, luego head apunta a ese nodo
    if (tail == 0) {
        tail = head;
    }
}

template <class T> void IntSLList<T>::addToTail(const T& val) {
    IntSLLNode<T>* newNode = new IntSLLNode<T>(val, nullptr); //create new node
    //check if list is empty
    if (isEmpty()) {
        head = tail = newNode; //create first node, which is why head and tail point to the same node in this case
    }
    else {
        tail->setNext(newNode); //add new node and set tail to point to it
        tail = newNode;
    }
}

template <class T> void IntSLList<T>::deleteFromHead() {
    //check if head is null
    if (head != 0) {
        IntSLLNode<T>* tmp; //pointer to head
        tmp = head; //assign head to pointer
        head = head->getNext(); //assign head to next node in the list
        if (head == 0) {
            tail = 0;
        }
        delete tmp; //delete first head node
    }
}

template <class T> void IntSLList<T>::deleteFromTail() {
    //check if head is null
    if (head != 0) {
        IntSLLNode<T>* tmp; //pointer to head
        tmp = head; //assign head to pointer
        if (head != tail) {
            while (tmp->getNext() != tail) {
                tmp = tmp->getNext(); //assign next node to tmp
            }
            tail = tmp; //assign tmp to tail
            tmp = tmp->getNext(); //assign next node to tmp
            tail->setNext(0);
        }
        else {
            head = tail = 0;
        }
        delete tmp; //delete node
    }
}
template <class T> void IntSLList<T>::printList() {
    IntSLLNode<T>* current = head;
    while (current != nullptr) {
        // Print the data from the current node
        cout << current->getInfo() << "\n";

        // Move to the next node
        current = current->getNext();
    }
    cout << endl;
}

//return empty head node if true
template <class T> bool IntSLList<T>::isEmpty() { return head == nullptr; }

//return list head
template <class T> IntSLLNode<T>* IntSLList<T>::getHead() { return head; }

//return number of nodes in the list
template <class T> int IntSLList<T>::countNodes() {
    int count = 0;                 // Initialize the count to 0
    IntSLLNode<T>* current = head; // Start at the head of the list

    while (current != nullptr) {
        count++;                      // Increment the count for each node
        current = current->getNext(); // Move to the next node
    }

    return count; // Return the total count
}

//sort nodes in list
template <class T> void IntSLList<T>::sortInsert(const T val) {
    IntSLLNode<T>* newNode = new IntSLLNode<T>(val, nullptr);

    if (isEmpty() ||
        val.remainingBurstTime < head->getInfo().remainingBurstTime) {
        // If the list is empty or the new process has a shorter burst time than the
        // head, insert it at the beginning.
        newNode->setNext(head);
        head = newNode;
        if (tail == nullptr) {
            // Update the tail if the list was initially empty.
            tail = newNode;
        }
    }
    else {
        IntSLLNode<T>* current = head; //set head to current node
        IntSLLNode<T>* prev = nullptr; //previous node is null

        while (current != nullptr && val.remainingBurstTime >=
            current->getInfo().remainingBurstTime) {
            prev = current; //move previous to current
            current = current->getNext(); //current node is now the next node
        }

        // Insert the new process between prev and current.
        prev->setNext(newNode);
        newNode->setNext(current);

        if (current == nullptr) {
            // Update the tail if the new process becomes the last one.
            tail = newNode;
        }
    }
}

//sort list based on priority
template <class T> void IntSLList<T>::sortPriority(const T& val) {
    IntSLLNode<T>* newNode = new IntSLLNode<T>(val, nullptr); //new node

    //check if list is empty or if priority is smaller than current head or if they are equal
    if (isEmpty() || val.priority < head->getInfo().priority ||
        (val.priority == head->getInfo().priority &&
            val.arrivalTime < head->getInfo().arrivalTime)) { //condition to
                                                                // check arrival time
        newNode->setNext(head); //set head to next node
        head = newNode;
        if (tail == nullptr) {
            tail = newNode; //set tail as new node
        }
    }
    else {
        IntSLLNode<T>* current = head; //current node is now the head
        IntSLLNode<T>* prev = nullptr; //previous node is now null

        //check if nodes are null and compare priority
        while (current != nullptr &&
            (val.priority > current->getInfo().priority ||
                (val.priority == current->getInfo().priority &&
                    val.arrivalTime >=
                    current->getInfo()
                    .arrivalTime))) { //condition to check arrival time
            prev = current;
            current = current->getNext();
        }

        //move nodes forward in the list
        prev->setNext(newNode);
        newNode->setNext(current);

        if (current == nullptr) {
            tail = newNode; //newNode is now the tail of the list
        }
    }
}
