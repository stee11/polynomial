// Name: Steven Kolln
// Description: Header file for the UI class

#ifndef ____UI__
#define ____UI__

#include "polyFunctions.h"
#include "Polynomial.h"
#include "Complex.h"
//#include "Polynomial.cpp"

using namespace std;

const int LIMIT=10;

class UI
{
	private:
		Polynomial<int> intPoly[10];
		Polynomial<double> doublePoly[10];
		bool doubleP, intP, complexP;
		//Polynomial<Complex> complexPoly[10];
		//These count to be sure the ammount in array do not exceed 10
		int intPolyNumber, doublePolyNumber, complexPolyNumber; 
	public:
		UI();
		//While loop of all actions user can perform
		void start();
		//User can create a polynomial. Each one assigned a number.
		//Parameter; number as to which polynomial they would like to use
		void createPoly();
		//Let the user add polynomials
		void add();
		//Let the user multiply polynomials. Will not create new polynomials just multiply them
		void multiply();
		//Let the user see a specific Polynomial
		//Parameter: the number is the number polynomial they would like to see.
		void seePoly();
		//User is shown all polynomials
		void seeAll();
		//User creates a polynomial from file.
		//Paramter: the string name of the file.
		bool createPolyFromFile();
		//Shows the users all options to choose from
		//Writes a polynomial to an output file.
		void writeToFile();
		void showOptions();
		//This function does the actual printing of a polynomial. There is a function for each data type
		//Parameter: The number of which poly to print 1-10
		void printPolyInt(const int&);
		void printPolyDouble(const int&);
		void printPolyComplex(const int&);
		
};


#endif

