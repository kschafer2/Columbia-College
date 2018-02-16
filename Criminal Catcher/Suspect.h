//
//  Suspect.h
//  CISS350 Assignment 6
//
//  Created by Kyle Schafer on 8/1/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#include <iostream>
#include <string>
#include "BinaryTree.h"
using namespace std;

#ifndef Suspect_h
#define Suspect_h

//SUSPECT CLASS
class Suspect
{
private:
    
//PRIVATE MEMBER VARIABLES
    string name; //to hold the suspect's name
    BinaryTree<string> attributes; //to hold the suspect's attributes
    
public:
    
//CONSTRUCTOR, DESTRUCTOR, COPY CONSTRUCTOR
/* 1.  */    Suspect();
/* 2.  */    ~Suspect();
/* 3.  */    Suspect(const Suspect&);
    
//OVERLOADED OPERATORS
/* 4.  */    void operator = (const Suspect&);
/* 5.  */    bool operator == (Suspect&);
/* 6.  */    bool operator < (Suspect&);
/* 7.  */    bool operator > (Suspect&);
/* 8.  */    friend ostream& operator << (ostream&, const Suspect&);
    
//MUTATORS
/* 9.  */    void SetName(string);
/* 10. */    void AddAttribute(string);
/* 11. */    void MakeEmpty();
    
//ACCESSORS
/* 12. */    string GetName();
/* 13. */    string FindAttribute(string, bool&);
/* 14. */    bool IsEmpty();
};

#endif /* Suspect_h */
