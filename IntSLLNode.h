template <class T> class IntSLLNode {
public:
	IntSLLNode(); // Default Constructor

	// Special Constructor:
	// Takes value of type T and pointer to next node as parameters
	IntSLLNode(T, IntSLLNode<T>*);

	T getInfo();                   // returns data from node
	IntSLLNode<T>* getNext();      // returns a pointer to the next node
	void setInfo(T);               // set data in node
	void setNext(IntSLLNode<T>*); // set pointer to the next node

private:
	T info;              // actual data
	IntSLLNode<T>* next; // Points to the next node in the list
};

template <class T>
IntSLLNode<T>::IntSLLNode() // Default Constructor
{
	// Initialize the 'next' pointer
	// to nullptr (0) to signify no next node initially
	next = 0;
}

template <class T>
IntSLLNode<T>::IntSLLNode(T i, IntSLLNode<T>* n) // Special Constructor
{
	// Initialize 'info' with the provided data value 'i'
	info = i;
	// Initialize 'next' with the provided next node pointer 'n'
	next = n;
}

template <class T> T IntSLLNode<T>::getInfo() {
	// Return data from node
	return info;
}

template <class T> IntSLLNode<T>* IntSLLNode<T>::getNext() {
	// Return Pointer to next node
	return next;
}

template <class T> void IntSLLNode<T>::setInfo(T i) {
	// Set the data of the node to the provided value 'i'
	info = i;
}

template <class T> void IntSLLNode<T>::setNext(IntSLLNode<T>* n) {
	// Set the 'next' pointer to the provided pointer 'n'
	next = n;
}
