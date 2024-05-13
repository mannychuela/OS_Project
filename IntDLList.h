#include "IntDLLNode.h"
#include <limits>

template <class T>
class IntDLList {
public:
    //Default constructor: creates an empty list
    IntDLList();

    //Destructor: deallocate memory
    ~IntDLList();

    //addToHead(T val): creates a new node with val as info, 
    //and this new node is the new head 
    void addToHead(T val);

    //addToTail(T val): creates a new node with val as info, 
    //and this new node is the new tail 	
    void addToTail(T val);

    //deleteFromHead: remove head from the list,
    //the new head is the previous head->next
    //if the list had only one node, head and tail point null
    void deleteFromHead();

    //deleteFromTail: remove tail from the list,
    //the new tail is the previous node to tail
    //if the list had only one node, head and tail point null
    void deleteFromTail();

    //In the list is empty, returns true
    //otherwise, returns false
    bool isEmpty();

    //printList(): prints all nodes in the list from head to tail
    void printList();


    int getSize() const;

    bool isPagePresent(const IntDLList<T>& pageList, T page);

    int simulateFIFO(T numberOfFrames);

    int simulateLRU(T numberOfFrames);

    int findFarthestFutureUse(const IntDLList<T>& pageReferences, T page, IntDLLNode<T>* startNode);

    int simulateOptimal(const IntDLList<T>& pageReferences, T numberOfFrames);

private:
    IntDLLNode<T>* head; //A pointer to the first node
    IntDLLNode<T>* tail; //A pointer to the last node
};

/****************
  Default constructor: creates an empty list
  head and tail point null
*****************/
template <class T>
IntDLList<T>::IntDLList()
{
    tail = head = 0;
}

/***********************
  Destructor: deallocate memory removing each node from the list
*****************/
template <class T>
IntDLList<T>::~IntDLList()
{
    //Declare a pointer prtNode	
    IntDLLNode<T>* prtNode;
    //prtNode points head
    prtNode = head;

    //While there is a node in the list, remove it
    while (prtNode != 0)
    {
        //prtNode points head->next
        prtNode = head->getNext();

        //delete head
        delete head;

        //the new head is prtNode
        head = prtNode;
    }

    head = tail = nullptr;
}

/***********************
  printList(): prints all nodes in the list
*****************/
template <class T>
void IntDLList<T>::printList()
{
    IntDLLNode<T>* prtNode;
    prtNode = head;
    while (prtNode != 0)
    {
        cout << prtNode->getInfo() << " ";
        prtNode = prtNode->getNext();
    }
}


/***********************
  If the list is empty, returns true
  otherwise, returns false
*****************/
template <class T>
bool IntDLList<T>::isEmpty()
{
    bool res;
    res = false;
    if (head == 0)
    {
        res = true;
    }
    return res;
}

/***********************
  Implement other methods
***********************/
template <class T>
void IntDLList<T>::addToHead(T val)
{

    // Create a new node with val as info, this new node is the head

    if (!isEmpty()) {
        head->setPrev(new IntDLLNode<T>(0, val, head));
        head = head->getPrev();
    }
    else {
        tail = head = new IntDLLNode<T>(0, val, head);
    }
}

template <class T>
void IntDLList<T>::addToTail(T val)
{

    // Create a new node with val as info, the new node is the tail

    if (!isEmpty()) {
        tail->setNext(new IntDLLNode<T>(tail, val, 0));
        tail = tail->getNext();
    }
    else {
        head = tail = new IntDLLNode<T>(tail, val, 0);
    }
}

template <class T>
void IntDLList<T>::deleteFromHead()
{

    // Remove the head from the list
    // If the list has only one node, head and tail point to null

    if (!isEmpty()) {
        IntDLLNode<T>* tmp;
        tmp = head;
        head = head->getNext();

        if (head == 0) {
            tail = 0;
        }
        else {
            head->setPrev(0);
        }
        delete tmp;
    }
}

template <class T>
void IntDLList<T>::deleteFromTail()
{

    // Removes tail from the list, the new tail is the previous node to tail. 
    // if the list has only one node, head and tail point to null

    if (!isEmpty()) {
        IntDLLNode<T>* tmp;
        tmp = tail;
        if (head != tail) {
            tail = tmp->getPrev();
            tail->setNext(0);
        }
        else {
            head = tail = 0;
        }
        delete tmp;
    }
}

/***********************
  Return list size
***********************/
template <class T>
int IntDLList<T>::getSize() const {
    int count = 0;
    IntDLLNode<T>* ptr = head;
    while (ptr != nullptr) {
        count++;
        ptr = ptr->getNext();
    }
    return count;
}

/********************************
  Verify if page is in the list
********************************/
template <class T>
bool IntDLList<T>::isPagePresent(const IntDLList<T>& pageList, T page) {
    IntDLLNode<T>* ptr = pageList.head;
    while (ptr != nullptr) {
        if (ptr->getInfo() == page) {
            return true;
        }
        ptr = ptr->getNext();
    }
    return false;
}

/*********************************
  Least Recently Used Algorithm
*********************************/
template <class T>
int IntDLList<T>::simulateLRU(T numberOfFrames) {
    IntDLList<T> pageList; // List to keep track of pages in memory
    int pageFaults = 0;

    IntDLLNode<T>* refPtr = head; // Access head directly

    while (refPtr != nullptr) {
        T currentPage = refPtr->getInfo(); // Access getInfo() directly


        // Check if the page is already in the list
        IntDLLNode<T>* pageNode = pageList.head;
        IntDLLNode<T>* prevNode = nullptr;

        while (pageNode != nullptr && pageNode->getInfo() != currentPage) {
            prevNode = pageNode;
            pageNode = pageNode->getNext();
        }

        if (pageNode != nullptr) {
            // Page is already in the list, move it to the tail
            if (prevNode != nullptr) {
                prevNode->setNext(pageNode->getNext());
                if (pageNode->getNext() != nullptr) {
                    pageNode->getNext()->setPrev(prevNode);
                }
            }
            else {
                // If the pageNode is the head, update head
                pageList.head = pageNode->getNext();
                if (pageNode->getNext() != nullptr) {
                    pageNode->getNext()->setPrev(nullptr);
                }
            }

            // Move the page to the tail
            pageNode->setPrev(pageList.tail);
            pageNode->setNext(nullptr);

            if (pageList.tail != nullptr) {
                pageList.tail->setNext(pageNode);
            }
            pageList.tail = pageNode;
        }
        else {
            // Page is not in the list, add it to the tail
            pageList.addToTail(currentPage);
            pageFaults++;

            // Check if the page list has reached the limit
            if (pageList.getSize() > numberOfFrames) {
                // If the limit is reached, remove the least recently used page (head)
                pageList.deleteFromHead();
            }
        }

        refPtr = refPtr->getNext(); // Access getNext() directly
    }

    return pageFaults;
}

/*******************************
  First-In First-Out Algorithm
*******************************/
template <class T>
int IntDLList<T>::simulateFIFO(T numberOfFrames) {
    IntDLList<T> pageList; // List to keep track of pages in memory
    int pageFaults = 0;    //pageFaults initialization to 0

    IntDLLNode<T>* refPtr = head; // Access head directly

    while (refPtr != nullptr) {
        T currentPage = refPtr->getInfo(); //currentPage is now the first page in the queue

        //Increment pageFaults if page T not found in pageList
        if (!isPagePresent(pageList, currentPage)) {
            pageFaults++;

            // Check if the page list has reached the limit of frames
            if (pageList.getSize() < numberOfFrames) {
                // If not, add the new page to the tail
                pageList.addToTail(currentPage);
            }
            else {
                // If the limit is reached, remove the oldest page (head) and add the new page to the tail
                //Implementing the FIFO algorithm logic where the oldest page in the frame list is replaced
                pageList.deleteFromHead();
                pageList.addToTail(currentPage);
            }
        }

        refPtr = refPtr->getNext(); // Access getNext() directly
    }

    return pageFaults;
}

/*********************
  Optimal Algorithm
*********************/
template <class T>
int IntDLList<T>::simulateOptimal(const IntDLList<T>& pageReferences, T numberOfFrames) {
    IntDLList<T> pageList; // List to keep track of pages in memory
    int pageFaults = 0;    //page faults initialized to 0

    IntDLLNode<T>* refPtr = pageReferences.head; // Pointer to traverse the page references

  //check if page list is not empty
    while (refPtr != nullptr) {
        T currentPage = refPtr->getInfo(); // Current page reference

        //if current page is not present, then increment page faults
        if (!isPagePresent(pageList, currentPage)) {
            pageFaults++;

            //if there are empty frames still, then add the current page to the first empty frame
            if (pageList.getSize() < numberOfFrames) {
                pageList.addToTail(currentPage);
            }

            else {
                // Find the page to replace
                IntDLLNode<T>* farthestPage = nullptr;

                //initalized to -1 to ensure that the first page will always be used after than 
                //the current initialization time
                int farthestIndex = -1;

                // Iterate through the pages currently in memory
                // This will find the farthest future use for each page in the list
                for (IntDLLNode<T>* page = pageList.head; page != nullptr; page = page->getNext()) {

                    // Find the farthest future use of the current page in memory
                    int index = findFarthestFutureUse(pageReferences, page->getInfo(), refPtr->getNext());

                    // Update farthestPage and farthestIndex if the current page has a farther future use
                    if (index > farthestIndex) {
                        farthestIndex = index;
                        farthestPage = page;
                    }
                }

                // Replace the page that is not used for the longest time in the future
                if (farthestPage != nullptr) {
                    farthestPage->setInfo(currentPage);
                }
            }
        }

        refPtr = refPtr->getNext(); // Move to the next page reference
    }

    return pageFaults;
}

/*************************************************************
  Function to find the farthest future use of the given page
*************************************************************/
template <class T>
int IntDLList<T>::findFarthestFutureUse(const IntDLList<T>& pageReferences, T page, IntDLLNode<T>* startNode) {

    int index = 0;

    //starts from page desired to be verified, iterates the rest of the reference list and
    //updates the farthest index if the page is called again later in the reference list
    for (IntDLLNode<T>* refPtr = startNode; refPtr != nullptr; refPtr = refPtr->getNext(), ++index) {
        if (refPtr->getInfo() == page) {
            return index;
        }
    }
    return std::numeric_limits<int>::max(); // If the page is not found in the future, return the maximum possible value
}

