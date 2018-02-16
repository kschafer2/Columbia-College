//
//  Patient.h
//  CISS350 Assignement 3
//
//  Created by Kyle Schafer on 7/11/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#ifndef Patient_h
#define Patient_h
#include <string>
using namespace std;

//Specialty Code Constants
const int PED = 1;              const int PSY = 7;
const int GEN = 2;              const int NEU = 8;
const int INT = 3;              const int ORT = 9;
const int CAR = 4;              const int DET = 10;
const int SUR = 5;              const int OPT = 11;
const int OBS = 6;              const int ENT = 12;

//Patient class
class Patient
{
private:
    
    //Variables
    string name; //to hold patient name
    int age; //to hold patient age
    int code; //to hold patient specialty code
    
public:
    
    //Constructor
    Patient()
    {
        name = "";
        age = -1;
        code = -1;
    }
    
    //Mutators
    
    //SET NAME
    void setName(string patName) //sets patient name
    {
        name = patName;
    }
    
    //SET AGE
    void setAge(int patAge) //sets patient age
    {
        age = patAge;
    }
    
    //SET CODE
    void setCode(int patCode) //sets patient specialty code
    {
        if(age >= 16)
            code = patCode;
        
        //if under 16, code is automatically set to 1 (PED) for pediatrician
        if(age < 16)
            code = PED;
    }
    
    //Accessors
    
    //GET NAME
    string getName() //returns patient's name
    {
        return name;
    }
    
    //GET AGE
    int getAge() //returns patient's age
    {
        return age;
    }
    
    //GET CODE
    int getCode() //returns patient's specialty code
    {
        return code;
    }
    
};

#endif /* Patient_h */
