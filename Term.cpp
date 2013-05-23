// Name: Steven Kolln
// Description: Polynomial class contains the method and constructor definitions for the Term class.

#include "polyFunctions.h"
#include "Term.h"

using namespace std;


template <class T> Term<T>::Term()
{}
template <class T> Term<T>::Term(const T& c, int d)
{
	coefficient=c;
	degree=d;
}
template <class T> const T& Term<T>::getCoefficient() const
{
	return coefficient;
}
template <class T> const int& Term<T>::getDegree() const
{
	return degree;
}
template <class T> void Term<T>::setDegree(const int& n)
{
	degree=n;
}
template <class T> void Term<T>::setCoefficient(T element)
{
	coefficient=element;
}
/*const bool& Term::getPositive() const
{
	return positive;
}*/
//Adds terms
template <class T> const Term<T> Term<T>::operator+(const Term<T>& t)
{
	return Term<T>((coefficient+t.coefficient),(degree+t.degree) );
}
//Compares terms based on degrees then coefficients. This is done to support the sort method.
template <class T> bool Term<T>::operator<(const Term<T>& t)
{
	if (degree==t.degree)
	{
		if (coefficient<t.coefficient)
			return true;
		else
			return false;
	}
	else if (degree<t.degree)
		return true;
	else
		return false;
}

template <class T> istream& operator>>(istream& i, Term<T>& t) 
{
	//Checks for a valid degree and coefficient
	cout << "Please enter a number that will represent a valid coefficient." << endl;
	T choice;
	i >> choice;
	t.coefficient=choice;
	cout << "Please enter a natural number that will represent the degree of your term." << endl;
	bool valid=false;
	while (!valid)
	{
		choice=getValidInt();
		if (choice<0)
			cout << "Please enter a natural number greater than or equal to 0." << endl;
		else
		{
			t.degree=choice;
			valid=true;
		}
	}
	return i;
}
//Checks the degree and coeficient for correct addition and subtraction symbols and formating of terms.
template <class T> ostream& operator<<(ostream& o, const Term<T>& t)
{
	//if the degree is zero, print coeficient positivly
	if (t.degree>=0)
	{
		if (t.coefficient==1)
		{
			if (t.degree==0)
			{
				cout << t.coefficient;
			}
			if (t.degree==1)
			{
				cout << "x";
			}
			if (t.degree>1)
			{	
				cout << "x^" << t.degree;
			}
		}
		//print negative coeficient
		if (t.coefficient==-1)
		{
			if (t.degree==0)
			{
				cout << t.coefficient;
			}
			if (t.degree==1)
			{
				cout << "-x";
			}
			if (t.degree>1)
			{
				cout << "-x^" << t.degree;
			}
		}
		//Print negative coefficient 
		if (t.coefficient<-1)
		{
			if (t.degree==0)
			{
				cout << t.coefficient;
			}
			if (t.degree==1)
			{
				cout << t.coefficient << "x";
			}
			if (t.degree>1)
			{
				cout << t.coefficient << "x^" << t.degree;
			}
		}
		//print positive coefficient
		if (t.coefficient>1)
		{
			if (t.degree==0)
			{
				cout << t.coefficient;
			}
			if (t.degree==1)
			{
				cout << t.coefficient << "x";
			}
			if (t.degree>1)
			{
				cout << t.coefficient << "x^" << t.degree;
			}
		}
		if (t.coefficient==0)
		{
		}
	}
	else
	{
		cout << "can't do it. degree < 0 " << endl << endl;
		/*
		if (t.degree==0)
			o << t.coefficient;
		if (t.degree==1)
			o << t.coefficient <<"x";
		if (t.degree>1)
			o << t.coefficient << "x^" << t.degree;
		if (t.degree <0)
			o << "error in degree less than 0";*/
	}
	return o;
}



