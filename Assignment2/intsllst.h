//************************  intSLLst.h  **************************
//           singly-linked list class to store integers

#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

/* Basically an inline class. This is the node of the list consisting of
 * 1) user-desired data: info
 * 2) pointer to next node element: next
 * 3) constructor which passes values to info and pointer to next node, initially null.
 */
class IntSLLNode
{
public:
    int info;
    class IntSLLNode *next;
    IntSLLNode(int el, IntSLLNode *ptr = 0)
    {
        info = el; next = ptr;
    }
};

/* Creates a linked list. The only member variables are pointers to the
 * head node and tail node.
 */
class IntSLList
{
    IntSLLNode *head, *tail;
public:
    IntSLList() {head = tail = 0;}
    ~IntSLList();
    int isEmpty() {return head == 0;}
    void addToHead(int);
    void addToTail(int);
    int  deleteFromHead(); // delete the head and return its info;
    int  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(int);
    bool isInList(int) const;
    void printAll() const;
};

#endif
