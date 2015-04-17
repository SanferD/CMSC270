#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

template<class T>
class DLLNode
{
public:
    DLLNode()
    {
        next = prev = 0;
    }
    DLLNode(const T& el, DLLNode *n = 0, DLLNode *p = 0)
    {
        info = el; next = n; prev = p;
    }
    T info;
    DLLNode *next, *prev;
};

template<class T>
class DoublyLinkedList
{
public:
    DoublyLinkedList()
    {
        head = tail = 0;
    }

    class Iterator
    {
        friend class DoublyLinkedList;
    private:
        DLLNode<T> *nodePtr;
        // The constructor is private, so only our friends
        // can create instances of Iterators.
        // Postcondition: The iterator has been constructed
        //                from newPtr.
        Iterator (DLLNode<T> *newPtr)
        {
            nodePtr = newPtr;
        } // constructor

    public:
        // Postcondition: The iterator has been constructed.
        Iterator()
        {
        } // default constructor

        // Postcondition: true has been returned if the
        //                iterator is not equal to itr;
        //                otherwise, false has been returned.
        bool operator!= (const Iterator& itr) const
        {
            return nodePtr != itr.nodePtr;
        } // overloading !=

        // Postcondition: A reference to the item the iterator
        //                is positioned at has been returned.
        T& operator*() const
        {
            return nodePtr -> info;
        } // overloading *

        // Precondition: The iterator is positioned at an item.
        // Postcondition: The iterator has been positioned at
        //                the next item in the Linked object.
        Iterator operator++(int)
        {
            Iterator temp = *this;
            nodePtr = nodePtr -> next;
            return temp;
        } // post-increment ++

        /* post-increment -- */
        Iterator operator--(int)
        {
            Iterator temp = *this;
            nodePtr = nodePtr -> prev;
            return temp;
        }

    }; // class Iterator

    // Postcondition: An iterator positioned at the front of
    //                the DoublyLinkedList has been returned.
    Iterator begin()
    {
        return Iterator(head);
    } // begin

    // Postcondition: An iterator positioned just after the
    //                back of the DoublyLinkedList has been
    //                returned.
    Iterator end()
    {
        return Iterator (0);
    } // end

    ~DoublyLinkedList()
    {
        clear();
    }
    bool isEmpty() const
    {
        return head == 0;
    }
    void clear();
    void setToNull()
    {
        head = tail = 0;
    }

    template<class T>
    Iterator insert(Iterator pos, const T &val)
    {
        DLLNode<T> *insNode =
                new DLLNode<T>(val,
                               pos!=end() ? pos.nodePtr : 0,
                               pos!=begin() ? pos.nodePtr->prev : 0);
        if(!head && !tail)
            head = tail = insNode;
        else
        {
            head = pos!=begin() ? head : insNode;
            tail = pos!=end() ? tail : insNode;
        }

        return Iterator(insNode);
    }

    Iterator erase (Iterator position);
    T& firstEl();
    T* find(const T&) const;
protected:
    DLLNode<T> *head, *tail;
    friend ostream& operator<<(ostream&, const DoublyLinkedList<T>&);
};



template<class T>
ostream& operator<<(ostream& out, const DoublyLinkedList<T>& dll)
{
    for (DLLNode<T> *tmp = dll.head; tmp != 0; tmp = tmp->next)
        out << tmp->info << ' ';
    return out;
}

template<class T>
T* DoublyLinkedList<T>::find(const T& el) const
{
    DLLNode<T> *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    if (tmp == 0)
        return 0;
    else return &tmp->info;
}


template<class T>
T& DoublyLinkedList<T>::firstEl()
{
    return head->info;
}

template<class T>
void DoublyLinkedList<T>::clear()
{
    for (DLLNode<T> *tmp; head != 0; )
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
}



#endif // STACK_H
