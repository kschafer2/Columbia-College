//
//  Queue.h
//  CISS350 Assignement 3
//
//  Created by Kyle Schafer on 7/11/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
#include <string>
#include "Doctor.h"
#include "Patient.h"
using namespace std;

//Queue class
class Queue
{
private:
    struct Node //stucture used to hold information
    {
        Patient data; //holds a patient object
        Node *next; //to point to the next node in the queue
    };
    
    Node *front; //to point to the front node in the queue
    Node *rear; //to point to the last node in the queue
    int length; //to hold number of nodes in queue (# of patients)
    
public:
    //Constructor
    Queue();
    
    //Destructor
    ~Queue();
    
    //Operations
    void enqueue(Patient &); //adds patient to back of queue
    void dequeue(Patient &); //gets patient at front of queue
    bool isEmpty() const; //returns bool based on number of patients in queue
    int getLength() const; //returns number of patients in queue
    void clear(); //removes all patients from queue
};


#endif /* Queue_h */
