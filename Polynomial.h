// Name: Steven Kolln
// Description: Contains the class definition and prototypes for the Polynomial class.

#ifndef ____Polynomial__
#define ____Polynomial__

#include "polyFunctions.h"
#include "Term.h"

using namespace std;

const int MAX_TERMS=10;

template <class T>
class Polynomial
{
	private:
		//An array of terms with a max of ten terms
		Term<T> polynomial[MAX_TERMS];
		//Number of terms currently in the array
		int counter;
	public:
		//default
		Polynomial();
		//takes int for counter
		Polynomial(int);
		//output stream and polynomial
		template <class S> friend ostream& operator<<(ostream&, Polynomial<S>&);
		template <class S> friend istream& operator>>(istream&, Polynomial<S>&);
		template <class S> friend ifstream& operator>>(ifstream&, Polynomial<S>&);
		template <class S> friend Polynomial operator+(const int&,const Polynomial<S>&);
		Polynomial operator+(const int&);
		const Polynomial operator+(Polynomial&);
		//takes the term you want to add to a polynomial
		void addTerm(const Term<T>&);
		//Gets rid of like terms and adds together
		void evaluate();
		void operator=(const Polynomial&);
		Polynomial operator*(const Polynomial&);
		template <class S> friend Polynomial operator*(const int&, const Polynomial<S>&);
		Polynomial operator*(const int&);
		int evalPoly(const int&);
		void writeToFile();
		//Swap method. Is a helper method for the sort. 
		//Parameter:  Takes the two ints you would like to swap and these two items are switched within the array of terms.
		void swap(Term<T>[], int, int);
		//Bublesort. Sorts the array of terms from highest degree to lowest
		//Parameter: It takes an array of terms and an int which represents how many terms are in the array.
		void sort(Term<T>[], int);
		//sets a t value along with the position and couner
		void set(T, const int&, const int&);
		void setCounter(const int&);
		Term<T> getTerm(const int&);
		int getCount();
		
};

#endif