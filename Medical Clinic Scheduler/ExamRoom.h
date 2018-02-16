//
//  ExamRoom.h
//  CISS350 Assignement 3
//
//  Created by Kyle Schafer on 7/11/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#ifndef ExamRoom_h
#define ExamRoom_h

#include "Queue.h"
#include <string>
#include "Doctor.h"
#include "Patient.h"
using namespace std;

class ExamRoom
{
private:
    Doctor roomDoctor; //to hold the doctor in the exam room
    Patient roomPatient; //to hold the patient in the exam
    Queue waitingRoom; //to attach waiting room to exam room
    
public:
    //Exception classes
    class NoDoctor
    {};
    
    class NoPatient
    {};
    
    //Constructor
    ExamRoom()
    {};
    
    //Mutators
    void setDoctor(Doctor newDoctor); //sets room doctor
    void setPatient(Patient newPatient); //sets room patient
 
    
    //Accessors
    bool hasDoctor(); //true if there's a doctor, else false
    bool hasPatient(); //true if there's a patient, else false
    Doctor getDoctor(); //returns room doctor
    Patient getPatient(); //returns room patient
    int getRoomNumber(); //returns room number
    int getCode(); //returns current room code
    int getWait(); //returns length of waiting room
    void addToWait(Patient &waitingPatient); //adds patient to waiting room queue
    void getNextPatient(); //room patient set to next patient in waiting room queue
    void vacateRoom(); //room doctor and patient are set to default

};

#endif /* ExamRoom_h */
