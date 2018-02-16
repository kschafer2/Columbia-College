//
//  Queue.h
//  CISS350 Assignement 6
//
//  Created by Kyle Schafer on 8/2/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include <string>
#include <iostream>
using namespace std;

//NODE STRUCTURE TEMPLATE
template<class T>
struct Node //stucture used to hold information
{
    T data; //holds item data
    Node<T>* next; //to point to the next node in the queue
};

//QUEUE CLASS TEMPLATE
template<class T>
class Queue
{
private:
    
//PRIVATE MEMBER VARIABLES
    Node <T>* front; //to point to the front node in the queue
    Node <T>* rear; //to point to the last node in the queue
    int length; //to hold number of nodes in queue
    
public:
    
//CONSTRUCTOR AND DESTRUCTOR
/* 1. */    Queue();
/* 2. */    ~Queue();
    
//PUBLIC MEMBER FUNCTIONS
/* 3. */    void Enqueue(T&); //adds item to back of queue
/* 4. */    void Dequeue(T&); //gets item at front of queue
/* 5. */    bool IsEmpty() const; //returns bool based on number of items in queue
/* 6. */    int GetLength() const; //returns number of patients in queue
/* 7. */    void Clear(); //removes all patients from queue
};

#endif /* Queue_h */

/*--------------------------------------------------------------------------------------------
 1. CONSTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Front and rear set to nullptr
 -Length set to 0
 
 */
template<class T>
Queue<T>::Queue()
{
    front = nullptr;
    rear = nullptr;
    length = 0;
}

/*--------------------------------------------------------------------------------------------
 2. DESTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Calls function 7. Clear to deallocate queue
 
 */

template<class T>
Queue<T>::~Queue()
{
    Clear();
}

/*--------------------------------------------------------------------------------------------
 3. FUNCTION ENQUEUE
 ---------------------------------------------------------------------------------------------
 
 -Adds item to the end of the queue
 
 */

template<class T>
void Queue<T>::Enqueue(T& item)
{
    //to hold a new node
    Node<T>* newNode = nullptr;
    
    //creates new node and stores item in data
    newNode = new Node<T>;
    newNode->data = item;
    newNode->next = nullptr;
    
    if (IsEmpty()) //if no nodes in queue
    {
        //front and rear point to the new node
        front = newNode;
        rear = newNode;
    }
    
    else
    {
        //otherwise adds newNode to the end of the queue
        rear->next = newNode;
        rear = newNode;
    }
    
    //increment length
    length++;
}

/*--------------------------------------------------------------------------------------------
 4. FUNCTION DEQUEUE
 ---------------------------------------------------------------------------------------------
 
 -Gets item at the front of the queue
 -Sets new front item to next item in queue
 
 */

template<class T>
void Queue<T>::Dequeue(T& item)
{
    Node<T>* temp = nullptr;
    
    if(!IsEmpty())
    {
        //item set to data in front node
        item = front->data;
        
        //front is set to the next node in queue
        //front node deleted
        temp = front;
        front = front->next;
        delete temp;
        
        //decrement length
        length--;
    }
    
    //if queue is empty, rear set to null
    if(IsEmpty())
        rear = nullptr;
    
}

/*--------------------------------------------------------------------------------------------
 5. FUNCTION IS EMPTY
 ---------------------------------------------------------------------------------------------
 
 -Returns true if length = 0
 -Otherwise returns false
 
 */

template<class T>
bool Queue<T>::IsEmpty() const
{
    if(length == 0)
        return true;
    
    else
        return false;
}

/*--------------------------------------------------------------------------------------------
 6. FUNCTION GET LENGTH
 ---------------------------------------------------------------------------------------------
 
 -Returns length
 
 */

template<class T>
int Queue<T>::GetLength() const
{
    return length;
}

/*--------------------------------------------------------------------------------------------
 2. FUNCTION CLEAR
 ---------------------------------------------------------------------------------------------
 
 -Calls function 4. Dequeue for all items in the queue
 
 */

template<class T>
void Queue<T>::Clear()
{
    T item;
    
    while(!IsEmpty())
        Dequeue(item);
}
