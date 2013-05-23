// Name: Steven Kolln
// Description: Header file for the assignment 4 functions.
#ifndef ____polyFunctions__
#define ____polyFunctions__

#include <iostream>
#include <fstream>
#include <cctype>
#include <cmath>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Polynomial.h"
#include "Term.h"

using namespace std;

//Retrieves a valid int from input. 
//Constraint: only checks for valid numbers, does not check for what the values need to be between.
int getValidInt();
//Use: Converts and int to a string for easy concatination.
//Parameter: Int which is desired to be turned into a string
//Constraint: for negatives give the absolute value and concatinate a - after the method call.
string numberToString(int);
//Asks the user if the want to use their own files  to read from.
bool ownFiles();
//Returns a string of the file the user would like to use.
string userFileMethod();
//Determines whether to read from a file or not.
bool readFromFile();



#endif