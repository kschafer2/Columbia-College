//
//  main.cpp
//  CISS350 Assignment 6
//
//  Created by Kyle Schafer on 7/31/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Suspect.h"

/*-------------------------------------------------------------------------------------------
 GLOBAL ACCESS
 ------------------------------------------------------------------------------------------*/

//ENUMERATED OPERATION
//used for switch menu readability
enum Operation {ADD, INQUIRY, TIP, CHECK, PRINT, QUIT};

//GLOBAL VARIABLES
fstream oFile; //for printing output
fstream ioFile; //for input and printing output
bool activeInquiry = false; //to determine whether or not an inquiry is acive
string codeName; //to hold the name of the inquiry
BinaryTree<Suspect> suspectTree; //to hold all suspects
BinaryTree<Suspect> inquiryTree; //to hold all suspects active in inquiry

/*---------------------------------------------------------------------------------------------
 FUNCTION PROTOTYPES
 ----------------------------------------------------------------------------------------------
 
 -Alphabetical order
 -See defintions after function main for more information
 
 */

/* 1.  */    void Add();
/* 2.  */    void Check();
/* 3.  */    void FindCriminal(string);
/* 4.  */    void FormatName(string &name);
/* 5.  */    void Goodbye();
/* 6.  */    void ImportSuspects();
/* 7.  */    void Inquiry();
/* 8.  */    void InquiryMenu(Operation&);
/* 9.  */    void MainMenu(Operation&);
/* 10. */    void Print();
/* 11. */    void Tip();
/* 12. */    void TreeBuilder(vector<Suspect>, int, int);

/*-------------------------------------------------------------------------------------------
 *** FUNCTION MAIN BEGINS ***
 -------------------------------------------------------------------------------------------*/

int main()
{
    ioFile.open("Criminal.mf", ios::in); //opens "Criminal.mf" for input
    oFile.open("Criminal.trn", ios::out); //opens "Criminal.trn" for output
    
    Operation choice; //to hold user's choice
    ImportSuspects(); //imports suspects from "Criminal.mf"
    
    do
    {
        if(activeInquiry)
            InquiryMenu(choice); //Displays inquiry menu if an inquiry is active
        else
            MainMenu(choice); //Displays main menu if an inquiry is not active
        
        switch(choice)
        {
            case ADD:       Add(); //call function 1. Add
                            break;
                
            case INQUIRY:   Inquiry(); //call function 7. Inquiry
                            break;
                
            case TIP:       Tip(); //call function 11. Tip
                            break;
                
            case CHECK:     Check(); //call function 2. Check
                            break;
                
            case PRINT:     Print(); //call function 10. Print
                            break;
                
            case QUIT:      Goodbye(); //call function 5. Goodbye
        }
        
    } while(choice != QUIT); //menu loops until user decides to quit

    return 0;
}

/*--------------------------------------------------------------------------------------------
 1. FUNCTION ADD
 ---------------------------------------------------------------------------------------------
 
 -Prompts user to enter suspect name and list of attributes
 -Adds suspect to suspectTree
 
 PRE: activeInquiry = false
 
 POST: suspect is in suspectTree
 
 */

void Add()
{
    Suspect suspect; //to hold suspect information
    string name; //to hold user input name
    string attribute; //to hold user input attribute
    bool again = true; //for loop control
    
    //prompts user for suspect name
    //loops until name is <= 20 characters
    while(again)
    {
        cout << "Suspect Name: ";
        oFile << "Suspect Name: ";

        getline(cin, name); //get user input name
        
        FormatName(name); //formats name properly
        
        oFile << name << endl; //sends name to "Criminal.trn"
        
        if(name.length() <= 20)
        {
            suspect.SetName(name); //sets suspect's name to user input name
            again = false; //stops name loop
        }
        
        else
        {
            cout << endl << "Invalid input. There is a 20 character limit." << endl;
            oFile << endl << "Invalid input. There is a 20 character limit." << endl;
        }
    }
    
    again = true; //again reset to true for attribute input validation
    
    cout << endl << "Now enter " << name << "'s attributes." << endl
        << "Press return after each attribute." << endl
        << "Enter 'end' when finished." << endl << endl;
    oFile << endl << "Now enter " << name << "'s attributes." << endl
        << "Press return after each attribute." << endl
        << "Enter 'end' when finished." << endl << endl;
    
    int counter = 1; //to hold attribute number
    int situation = 0; //for use in switch menu
    
    //loops until at least one attribute and "end" received from user
    while(again)
    {
        
        cout << "Attribute " << counter << ": ";
        oFile << "Attribute " << counter << ": ";
        
        getline(cin, attribute); //get attribute from user
        for (auto & c: attribute) c = tolower(c); //whole string lowercase
        oFile << attribute << endl; //outputs attribute to ""Criminal.trn"
        
        if(attribute == "end" && counter == 1)
            situation = 1;
        
        else if(attribute == "end")
            situation = 2;

        else if(attribute.length() <= 20)
            situation = 3;
        
        switch(situation)
        {
            case 1: cout << endl << "Please enter at least one attribute." << endl;
                    oFile << endl << "Please enter at least one attribute." << endl;
                    break;
    
            case 2: suspectTree.PutItem(suspect); //add suspect to suspectTree
                    again = false;
                    break;
        
            case 3: suspect.AddAttribute(attribute); //add attribute to suspect
                    counter++; //increment attribute counter
                    break;
                
            default: cout << endl << "Invalid input. There is a 20 character limit." << endl;
                     oFile << endl << "Invalid input. There is a 20 character limit." << endl;
                     break;
        }
        situation = 0; //reset situation for next attribute
    }
}

/*--------------------------------------------------------------------------------------------
 2. FUNCTION CHECK
 ---------------------------------------------------------------------------------------------
 
 -Prompts user to enter suspect name and list of attributes
 -Displays message accordingly
 
 POST: message displayed
 
 */

void Check()
{
    Suspect suspect; //to hold a suspect
    string name; //to hold user input name
    bool again = true; //for loop control
    bool found; //to know if matching suspect is found
    
    //prompts user for name
    //loops until name <= 20 characters
    while(again)
    {
        cout << "Suspect Name: ";
        oFile << "Suspect Name: ";
        
        getline(cin, name); //gets name from user
        
        FormatName(name); //formats name properly
        
        oFile << name << endl; //outputs name to "Criminal.trn"
        
        if(name.length() <= 20)
        {
            suspect.SetName(name); //sets suspect name
            
            if(activeInquiry) //looks for suspect in inquiryTree
                suspect = inquiryTree.FindItem(suspect, found);
            
            else //looks for suspect in suspectTree
                suspect = suspectTree.FindItem(suspect, found);
            
            if(found)
            {
                cout << endl << name << " was found in the suspect records."
                << endl << suspect << endl;
                oFile << endl << name << " was found in the suspect records."
                << endl << suspect <<endl;
            }
            else
            {
                cout << name << " is not in the suspect records." << endl;
                oFile << name << " is not in the suspect records." << endl;
            }
            
            again = false; //stops name loop
        }
        
        else
        {
            cout << endl << "Invalid input. There is a 20 character limit." << endl;
            oFile << endl << "Invalid input. There is a 20 character limit." << endl;
        }
    }
}

/*--------------------------------------------------------------------------------------------
 3. FUNCTION FIND CRIMINAL
 ---------------------------------------------------------------------------------------------
 
 -Searches through inquiryTree and attempts to find the criminal
 
 PRE: suspects are in suspectTree
 
 POST: suspects without an attribute matching tip are deleted
 if no suspects remain, the criminal is not found and activeInquiry = false
 if only one suspect remains, the criminal is found and activeInquiry = false
 
 */

void FindCriminal(string tip)
{
    Suspect suspect; //to hold a suspect
    bool finished = false; //to know when there are no more suspects to search
    bool found = false; //to know when an attribute is found
    int suspectCount = 0; //to hold number of remaining suspects
    string attribute; //to hold an attribute
    
    inquiryTree.ResetTree(POST_ORDER); //makes queue of suspects in postorder
    
    //loops until all suspects have been searched
    while(!finished)
    {
        //gets the next suspect
        suspect = inquiryTree.GetNextItem(POST_ORDER, finished);
        
        //searches suspects attributes for one that matches tip
        suspect.FindAttribute(tip, found);
        
        //increment suspectCount if a matching attribute is found
        if(found)
            suspectCount++;
        
        //otherwise delete the suspect from inquiryTree
        else
            inquiryTree.DeleteItem(suspect);
        
        //found set to false for next suspect search
        found = false;
    }
    
    //switch based on number of remaining suspects
    switch(suspectCount)
    {
        case 0:
        {
            activeInquiry = false; //no matching suspects
            
            //no suspects match with the tip information
            cout << endl << "***No matching suspects***" << endl
            << "***Inquiry: " << codeName << " terminated***" << endl;
            oFile << endl << "***No matching suspects***" << endl
            << "***Inquiry: " << codeName << " terminated***" << endl;
            break;
        }
            
        case 1:
        {
            activeInquiry = false; //criminal has been found
            
            cout << endl << "***Inquiry: " << codeName << " has been solved!***" << endl
            << "***The criminal has been found!***" << endl;
            oFile << endl << "***Inquiry: " << codeName << " has been solved!***" << endl
            << "***The criminal has been found!***" << endl;
            
            //prints the criminal's information
            inquiryTree.Print(IN_ORDER, cout);
            inquiryTree.Print(IN_ORDER, oFile);
            
            break;
        }
            
        default:
        {
            //more than one suspect could be the criminal
            cout << endl << "The criminal is still at large!" << endl
            << "More tips are needed to find the criminal." << endl;
            oFile << endl << "The criminal is still at large!" << endl
            << "More tips are needed to find the criminal." << endl;\
            
            break;
        }
    }
}

/*--------------------------------------------------------------------------------------------
 4. FUNCTION FORMAT NAME
 ---------------------------------------------------------------------------------------------
 
 -Formats first letter of each word to uppercase and all other characters to lowercase
 
 POST: name is reformatted (Xxx Xxxxx)
 
 */

void FormatName(string &name)
{
    for (auto & c: name) c = tolower(c); //whole string lowercase
    
    name[0] = toupper(name[0]); //first letter of string uppercase
    
    //any characters following a whitespace character becomes uppercase
    for(int i = 0; i < name.length(); i++)
    {
        if(name[i] == ' ')
            name[i + 1] = toupper(name[i + 1]);
    }
}

/*--------------------------------------------------------------------------------------------
 5. FUNCTION GOODBYE
 ---------------------------------------------------------------------------------------------
 
 -Displays farewell message
 -Closes input file "Criminal.mf" and reopens for output
 -Prints suspectTree to "Criminal.mf" in pre order for next program execution
 -Closes both files
 
 POST: "Criminal.mf" updated
 closes both files
 
 */

void Goodbye()
{
    cout << endl << "Thank you for using the Criminal Catcher." << endl
    << "Have a wonderful day!" << endl;
    oFile << endl << "Thank you for using the Criminal Catcher." << endl
    << "Have a wonderful day!" << endl;
    
    ioFile.close(); //close "Criminal.mf"
    ioFile.open("Criminal.mf", ios::out); //open "Criminal.mf" for output
    
    suspectTree.Print(IN_ORDER, ioFile); //prints suspectTree to "Criminal.mf" in order
    
    ioFile.close();
    oFile.close();
}

/*--------------------------------------------------------------------------------------------
 6. FUNCTION IMPORT SUSPECTS
 ---------------------------------------------------------------------------------------------
 
 -Imports suspects from "Criminal.mf" to suspectTree
 
 PRE: "Criminal.mf" contains suspects
 
 POST: suspectTree contains suspects from "Criminal.mf"
 
 */

void ImportSuspects()
{
    string str; //to hold input from the file
    Suspect suspect; //to hold a suspect to add to suspectTree
    vector<Suspect> suspectVector;
    int numSuspects = 0;
    
    while(ioFile) //continues to find suspect information until the end of the file
    {
        getline(ioFile, str); //gets line from file
        
        if(isupper(str[0]) && islower(str[1])) //input formatted for name (Xxxx Xxxxx)
            suspect.SetName(str); //sets suspect name
        
        else
        {
            while(islower(str[0]) && ioFile) //input formatted for attribute (xxxx xxxxx)
            {
                suspect.AddAttribute(str); //set suspect attribute to input
                getline(ioFile, str); //ensures all attributes for suspect are imported
            }
            
            if(!suspect.IsEmpty()) //suspect has name and attributes
            {
              //  suspectTree.PutItem(suspect); //adds suspect to the suspect tree
                suspectVector.push_back(suspect);
                numSuspects++;
                suspect.MakeEmpty(); //clears info in suspect
            }
        }
    }
    
    //builds a balanced tree assuming suspectVector is in order
    TreeBuilder(suspectVector, 0, numSuspects);
}

/*--------------------------------------------------------------------------------------------
 7. FUNCTION INQUIRY
 ---------------------------------------------------------------------------------------------
 
 -Prompts user for code name
 -Begins an inquiry
 
 PRE: activeInquiry = false
 
 POST: activeInquiry = true
       codeName set to user input
       inquiryTree is a copy of suspectTree
 
 */

void Inquiry()
{
    bool again = true; //for loop control
    
    while(again) //loops until codeName is <= 20 characters
    {
        cout << "Code Name: ";
        oFile << "Code Name: ";

        getline(cin, codeName); //gets codeName from user
        oFile << codeName << endl; //outputs codeName to "Criminal.trn"
        
        if(codeName.length() <= 20)
            again = false;
        
        else
        {
            cout << endl << "Invalid input. There is a 20 character limit." << endl;
            oFile << endl << "Invalid input. There is a 20 character limit." << endl;
        }
    }
    
    inquiryTree = suspectTree; //inquiryTree set to suspectTree
    activeInquiry = true; //inquiry is active
}

/*--------------------------------------------------------------------------------------------
 8. FUNCTION INQUIRY MENU
 ---------------------------------------------------------------------------------------------
 
 -Displays the inquiry menu and prompts user to enter a command
 -Switches command based on user input
 
 PRE: activeInquiry = true
 
 POST: choice set to specified Operation
 
 */

void InquiryMenu(Operation& choice)
{
    //Local Variables
    bool again = true; //used for loop control
    int command = 0; //to hold user input command as an integer
    string str; //to hold input string
    
    int i = 257;
    char c;
    c = (char)i;
    cout << c;
    
    //displays inquiry menu
    cout << endl << "***Inquiry: "<< codeName << " is Active***" << endl
    << endl << "1. TIP" << endl << "2. CHECK" << endl
    << "3. PRINT" << endl << "4. QUIT" << endl;
    oFile << endl << "***Inquiry: "<< codeName << " is Active***" << endl
    << endl << "1. TIP" << endl << "2. CHECK" << endl
    << "3. PRINT" << endl << "4. QUIT" << endl;
    
    //prompts for command from user
    //loops until command is between 1-4
    while(again)
    {
        cout << "COMMAND #: ";
        oFile << "COMMAND #: ";
        
        getline(cin, str); //gets input as a string
        stringstream(str) >> command; //converts string to integer
        oFile << command << endl; //outputs command integer to "Criminal.trn"
        
        if(command >= 1 && command <= 4)
            again = false;
        
        else
        {
            cout << endl << "Invalid input. Please enter a number between 1 and 4." << endl;
            oFile << endl << "Invalid input. Please enter a number between 1 and 4." << endl;
        }
    }
    
    //choice set to specified Operation
    switch(command)
    {
        case 1: choice = TIP;
            break;
            
        case 2: choice = CHECK;
            break;
            
        case 3: choice = PRINT;
            break;
            
        case 4: choice = QUIT;
    }
}

/*--------------------------------------------------------------------------------------------
 9. FUNCTION MAIN MENU
 ---------------------------------------------------------------------------------------------
 
 -Displays the main menu and prompts user to enter a command
 -Switches command based on user input
 
 PRE: activeInquiry = false
 
 POST: choice set to specified Operation
 
 */

void MainMenu(Operation &choice)
{
    //Local Variables
    bool again = true; //used for loop control
    int command = 0; //to hold user input command as an integer
    string str; //to hold input string
    
    //displays main menu
    cout << endl << "***Welcome to the Criminal Catcher!***" << endl << endl
    << "1. ADD" << endl << "2. INQUIRY" << endl << "3. CHECK" << endl
    << "4. PRINT" << endl << "5. QUIT" << endl;
    oFile << endl << "***Welcome to the Criminal Catcher!***" << endl << endl
    << "1. ADD" << endl << "2. INQUIRY" << endl << "3. CHECK" << endl
    << "4. PRINT" << endl << "5. QUIT" << endl;
    
    //prompts for command from user
    //loops until command is between 1-5
    while(again)
    {
        cout << "COMMAND #: ";
        oFile << "COMMAND #: ";
        
        getline(cin, str); //gets input as string
        stringstream(str) >> command; //converts string to integer
        oFile << command << endl; //outputs command integer to "Criminal.trn"
        
        if(command >= 1 && command <= 5)
            again = false;
        
        else
        {
            cout << endl << "Invalid input. Please enter a number between 1 and 5." << endl;
            oFile << endl << "Invalid input. Please enter a number between 1 and 5." << endl;
        }
    }
    
    //choice set to specified Operation
    switch(command)
    {
        case 1: choice = ADD;
            break;
            
        case 2: choice = INQUIRY;
            break;
            
        case 3: choice = CHECK;
            break;
            
        case 4: choice = PRINT;
            break;
            
        case 5: choice = QUIT;
    }
}

/*--------------------------------------------------------------------------------------------
 10. FUNCTION PRINT
 ---------------------------------------------------------------------------------------------
 
 -Prints suspects in order
 
 POST: list of suspects output to console and outfile
 
 */

void Print()
{
    cout << endl << "ACTIVE SUSPECTS" << endl;
    oFile << endl << "ACTIVE SUSPECTS" << endl;
    
    if(activeInquiry) //prints inquiryTree suspects
    {
        inquiryTree.Print(IN_ORDER, cout);
        inquiryTree.Print(IN_ORDER, oFile);
    }
    
    else //prints suspectTree suspects
    {
        suspectTree.Print(IN_ORDER, cout);
        suspectTree.Print(IN_ORDER, oFile);
    }
}

/*--------------------------------------------------------------------------------------------
 11. FUNCTION TIP
 ---------------------------------------------------------------------------------------------
 
 Acquires tip information from user
 Attempts to find the criminal by calling function 3. Find Criminal
 
 PRE: activeInquiry = true
 
 Post: see function Find Criminal
 
 */

void Tip()
{
    bool again = true; //for loop control
    string tip; //to hold user input tip information
    
    //prompts user for tip information
    //loops until tip is <= 20 characters
    while(again)
    {
        cout << "Tip Information: ";
        oFile << "Tip Information: ";

        getline(cin, tip); //gets tip information from user
        for (auto & c: tip) c = tolower(c); //whole string lowercase
        oFile << tip << endl; //outputs tip to "Criminal.trn"
        
        if(tip.length() <= 20)
        {
            FindCriminal(tip); //try to match suspect attributes with tip information
            again = false;
        }
        
        else
        {
            cout << endl << "Invalid input. There is a 20 character limit." << endl;
            oFile << endl << "Invalid input. There is a 20 character limit." << endl;
        }
    }

}

/*--------------------------------------------------------------------------------------------
 12. FUNCTION TREE BUILDER
 ---------------------------------------------------------------------------------------------
 
 -Builds a balanced suspectTree from sorted suspectVector 
 
 PRE: suspectVector is sorted in order
      suspectTree is empty at first call
 
 POST: suspectTree is balanced and includes all elements in suspectVector
 
 */
void TreeBuilder(vector<Suspect> suspectVector, int start, int end)
{
    if (start < end)
    {
        int middle = (start+end)/2; //find the middle
        
        suspectTree.PutItem(suspectVector[middle]); //add middle to suspectTree
        
        //recursive call in which middle becomes end
        TreeBuilder(suspectVector, start, middle);
        
        //recursive call in which start becomes middle + 1
        TreeBuilder(suspectVector, middle + 1, end);
    }
}






