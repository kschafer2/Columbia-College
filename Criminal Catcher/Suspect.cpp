//
//  Suspect.cpp
//  CISS350 Assignment 6
//
//  Created by Kyle Schafer on 8/1/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "Suspect.h"
using namespace std;

/*--------------------------------------------------------------------------------------------
 1. CONSTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Assigns an empty string to name
 
 */

Suspect::Suspect()
{
    name = "";
};

/*--------------------------------------------------------------------------------------------
 2. DESTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Calls attributes's function 17. MakeEmpty
 
 */

Suspect::~Suspect()
{
    attributes.MakeEmpty();
}

/*--------------------------------------------------------------------------------------------
 3. COPY CONSTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Makes a copy of the original suspect object by copying name and attributes
 
 */

Suspect::Suspect(const Suspect& original)
{
    name = original.name; //copies name
    attributes = original.attributes; //copies attributes
}

/*--------------------------------------------------------------------------------------------
 4. ASSIGNMENT OPERATOR OVERLOAD
 ---------------------------------------------------------------------------------------------
 
 -Makes a copy of the original suspect object by copying name and attributes
 
 */

void Suspect::operator = (const Suspect& original)
{
    name = original.name; //copies name
    attributes = original.attributes; //copies attributes
}

/*--------------------------------------------------------------------------------------------
 5. EQUALS OPERATOR OVERLOAD
 ---------------------------------------------------------------------------------------------
 
 -Returns true if both suspect object names are equal
 -Otherwise returns false
 
 */

bool Suspect::operator == (Suspect& right)
{
    if(name == right.name)
        return true;
    else
        return false;
}

/*--------------------------------------------------------------------------------------------
 6. LESS THAN OPERATOR OVERLOAD
 ---------------------------------------------------------------------------------------------
 
 -Returns true if left suspect name is less than right suspect name
 -Otherwise returns false
 
 */

bool Suspect::operator < (Suspect& right)
{
    if(name < right.name)
        return true;
    else
        return false;
}

/*--------------------------------------------------------------------------------------------
 7. GREATER THAN OPERATOR OVERLOAD
 ---------------------------------------------------------------------------------------------
 
 -Returns true if left suspect name is greater than right suspect name
 -Otherwise returns false
 
 */

bool Suspect::operator > (Suspect& right)
{
    if(name > right.name)
        return true;
    else
        return false;
}

/*--------------------------------------------------------------------------------------------
 8. STREAM INSERTION OPERATOR OVERLOAD
 ---------------------------------------------------------------------------------------------
 
 -Sends suspect's formatted name and attributes (in pre order) to the ostream object
 -Returns the ostream object
 
 */

ostream& operator << (ostream& stream, const Suspect& obj)
{
    stream << "---------------"<< endl << "NAME:" << endl
    << obj.name << endl << endl << "ATTRIBUTES:" << endl;
    
    obj.attributes.Print(PRE_ORDER, stream);
    
    return stream;
}

/*--------------------------------------------------------------------------------------------
 9. FUNCTION SET NAME
 ---------------------------------------------------------------------------------------------
 
 -Sets suspect name to str
 
 */

void Suspect::SetName(string str)
{
    name = str;
}

/*--------------------------------------------------------------------------------------------
 10. FUNCTION ADD ATTRIBUTE
 ---------------------------------------------------------------------------------------------
 
 -Adds str to suspect's attributes binary tree by calling attributes's function 22. Put Item
 
 */

void Suspect::AddAttribute(string str)
{
    attributes.PutItem(str);
}

/*--------------------------------------------------------------------------------------------
 11. FUNCTION MAKE EMPTY
 ---------------------------------------------------------------------------------------------
 
 -Sets suspect to a blank suspect
 -Sets name to empty string and alls attributes's Make Empty function
 
 */

void Suspect::MakeEmpty()
{
    name = "";
    attributes.MakeEmpty();
}

/*--------------------------------------------------------------------------------------------
 12. FUNCTION GET NAME
 ---------------------------------------------------------------------------------------------
 
 -Returns suspect's name
 
 */

string Suspect::GetName()
{
    return name;
}

/*--------------------------------------------------------------------------------------------
 13. FUNCTION FIND ATTRIBUTE
 ---------------------------------------------------------------------------------------------
 
 -Searches suspect's attributes binary tree for an attribute matching string item
 -Found set according to result of attributes's Find Item function
 -Returns attribute
 
 */

string Suspect::FindAttribute(string item, bool& found)
{
    string attribute;
    
    attribute = attributes.FindItem(item, found);
    
    return attribute;
}

/*--------------------------------------------------------------------------------------------
 14. FUNCTION IS EMPTY
 ---------------------------------------------------------------------------------------------
 
 -Returns true if the suspect's name is an empty string 
 -Returns true if the suspect's attributes binary tree is empty
 -Otherwise returns false
 
 */

bool Suspect::IsEmpty()
{
    if(name == "" || attributes.IsEmpty())
        return true;
    else
        return false;
}

