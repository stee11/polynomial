// Name: Steven Kolln
// Description: Contains the class definition and prototypes for the Term class.

#ifndef ____Term__
#define ____Term__

#include "polyFunctions.h"

using namespace std;

template <class T> class Term
{
	private: 
		T coefficient;
		int degree;
		//bool positive;
	public:
		//Constructor for the Term class; will default to zero if no values are inputed. 
		//Parameters: The first parameter must be of type int which is the coeffiecient and the second is the degree of the term
		Term(const T&, int=0);
		Term();
		//Getter methods for the class's instance data.
		const T& getCoefficient() const;
		const int& getDegree() const;
		void setDegree(const int&);
		void setCoefficient(T);
		//const bool& getPositive() const;
		//This method adds two terms together if calling object is of type term. Parameter must be of type Term.
		const Term operator+(const Term<T>&);
		bool operator<(const Term<T>&);
		template <class S> friend ostream& operator<<(ostream&, const Term<S>&);
		template <class S> friend istream& operator>>(istream&, Term<S>&);
		
};

#endif