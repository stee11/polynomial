// Name: Steven Kolln
// Description: Functions definitions for assignment 4

#include "polyFunctions.h"
#include "Polynomial.h"
#include "Term.cpp"

using namespace std;

//Method descriptions are located before each method.

//Retrieves a valid int from input
int getValidInt()
{
	bool tryAgain = true;
	int value;
	
    while (tryAgain)
	{
		cin >> value;
		if (cin.fail())
		{
			cout << "*** Invalid Input *** Please enter a int value: ";
			cin.clear();
			cin.ignore (1000, '\n');
	    }
		else
			tryAgain = false;
	}
	return value;
}
//Determines whether to read from a file or not.
bool readFromFile()
{
	cout << "Would you like to enter inputs yourself or read from a file. Press f for file or any other key for input yourself." << endl;
	string input;
	cin.ignore();
	getline(cin, input);
	//the first character is only used here
	char answer=toupper(input.substr(0,1).c_str()[0]);
	if (answer=='F')
		return true;
	return false;
}

//Converts and int to a string for easy concatination
//Parameter: takes an int
string numberToString(int n)
{
	string s;
	ostringstream stream;
	stream << n;
	s=stream.str();
	return s;
}
////Asks the user if the want to use their own files  to read from.
bool ownFiles()
{
	cout << "Would you like to enter your own files to read from? Press y for yes and anything else for no." << endl << endl;
	string input;
	cin >> input;
	//the first character is only used here
	char answer=toupper(input.substr(0,1).c_str()[0]);
	if (answer=='Y')
		return true;
	return false;
}
//Returns a string of the file the user would like to use.
string userFileMethod()
{
	cout << endl << "What is the name of the file(s) you would like to use? Give the name of the file(s) without number or extension. Refer to readme with questions." << endl << endl;
	string input;
	cin >> input;
	cout << endl;
	return input;
}