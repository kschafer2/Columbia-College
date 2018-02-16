//
//  Doctor.h
//  CISS350 Assignement 3
//
//  Created by Kyle Schafer on 7/11/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#ifndef Doctor_h
#define Doctor_h
#include <string>
#include "Patient.h"
using namespace std;

//Doctor class
class Doctor
{
private:
    
    //Variables
    string name; //to hold doctor's name
    int room; //to hold doctor's preferred room number
    int code; //to hold doctor's specialty code
    
public:
    
    //Constructor
    Doctor()
    {
        name = "";
        room = -1;
        code = -1;
    }
    
    //Mutators
    
    //SET NAME
    void setName(string docName) //sets doctor's name
    {
        name = docName;
    }
    
    //SET ROOM
    void setRoom(int docRoom) //sets doctor's room #
    {
        room = docRoom;
    }
    
    //SET CODE
    void setCode(int docCode) //sets doctor's code
    {
        code = docCode;
    }
    
    //Accessors
    
    //GET NAME
    string getName() //returns doctor's name
    {
        return name;
    }
    
    //GET ROOM
    int getRoom() //returns doctor's room number
    {
        return room;
    }
    
    //GET CODE
    int getCode() //returns doctor's specialty code
    {
        return code;
    }

};


#endif /* Doctor_h */
