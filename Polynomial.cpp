// Name: Steven Kolln
// Description: Polynomial class contains the method and constructor definitions for the Polynomial class.

#include "polyFunctions.h"
#include "Polynomial.h"
//#include "polyFunctions.cpp"

using namespace std;
//Default constructor with current set to zero

template <class T> Polynomial<T>::Polynomial()
{
	counter=0;
}
//Sets the coefficient and degree of the term of the polynomial. Last int is what term will be changed:
//Parameters: T coefficient, int degree, int which term.
//Constraint: All numbers are assumed to be valid.
template <class T> void Polynomial<T>::set(T element, const int& d, const int& n)
{
	polynomial[n].setCoefficient(element);
	polynomial[n].setDegree(d);
}
//This method determiens what spot in the terms array of the polynomial to place the next term. The term is added and the count is increased.
template <class T> void Polynomial<T>::addTerm(const Term<T>& t)
{
	polynomial[counter]=t;
	counter++;
}
template <class T> void Polynomial<T>::setCounter(const int& n)
{
	counter=n;
}
//Addition for adding two polynomials together.
template <class T> const Polynomial<T> Polynomial<T>::operator+(Polynomial<T>& p)
{
	//temp is the copied version of the calling polynomial
	Polynomial<T> temp;
	//Value to be returned
	Polynomial<T> final;
	for (int i=0;i<counter;i++)
	{
		temp.addTerm(polynomial[i]);
	}
	temp.counter=counter;
	temp.evaluate();
	p.evaluate();
	//If both arrays added together have less then 10 elements, add them to the final array sort them and evaluate those with common degrees.
	if (temp.counter+p.counter<=10)
	{
		int i=temp.counter;
		//Take all the terms not in temp and add them from temp to final
		for (int secondCount=0;secondCount<p.counter;secondCount++)
		{
			temp.polynomial[i]=p.polynomial[secondCount];
			i++;
			temp.counter++;
		}
		temp.evaluate();
		sort(temp.polynomial, temp.counter);
		final=temp;
	}
	else
	{
		cout << endl <<  "Product for polynomials entered will have greater than 10 terms." << endl << "Highest degrees will be kept and the rest will be truncated." << endl;
		//This array holds all possible terms.
		Term<T> allTerms[100];
		int position=0;
		for (int i=0; i<counter;i++)
		{
			allTerms[i]=temp.polynomial[i];
			position++;
		}
		for (int i=0;i<p.counter;i++)
		{
			allTerms[position]=p.polynomial[i];
			position++;
		}
		//All terms from both polynomials are placed into this array
		sort(allTerms, position);
		int iteratorCount=0;
		//Placed one by one into final and evaluated each placement. This makes sure this will stop once all possible terms are included.
		//Note **** only highest 10 terms are included
		while (final.counter!=10)
		{
			final.addTerm(allTerms[iteratorCount]);
			final.evaluate();
			iteratorCount++;
		}
		sort(final.polynomial, final.counter);
	}
	return final;
}
template <class T> Polynomial<T> Polynomial<T>::operator+(const int& n)
{
	//Calling polynomial placed into temp
	Polynomial<T> temp;
	for (int i=0;i<counter;i++)
	{
		temp.addTerm(polynomial[i]);
	}
	if (counter<10)
	{
		//A term with degree zero is added to represent the int. If it can't fit it will not be added as only the 10 highest terms can fit
		Term<T> t(n, 0);
		temp.addTerm(t);
		temp.evaluate();
		sort(temp.polynomial, temp.counter);
	}
	return temp;
}
//Swap method. Takes the two ints you would like to swap.
template <class T> void Polynomial<T>::swap(Term<T> t[], int index1, int index2)
{
	Term<T> temp=t[index1];
	t[index1]=t[index2];
	t[index2]=temp;
}
//Bubblesort. Sorts the array of terms from highest degree to lowest.
template <class T> void Polynomial<T>::sort(Term<T> terms[], int length)
{
	int position, scan;
	for (position=length-1;position>=0; position--)
	{
		for (scan=0; scan<=position-1;scan++)
		{
			if (terms[scan] < terms[scan+1] >0)
				swap(terms, scan, scan+1);
		}
	}
}
//Implemented in a very similar manor to previous addition method.
template <class T> Polynomial<T> operator+(const int& n, const Polynomial<T>& p)
{
	Polynomial<T> temp;
	for (int i=0;i<p.counter;i++)
	{
		temp.addTerm(p.polynomial[i]);
	}
	if (temp.counter<10)
	{
		Term<T> t(n, 0);
		temp.addTerm(t);
		temp.evaluate();
		sort(temp.polynomial, temp.counter);
	}
	return temp;
}
template <class T> Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& p)
{
	int tempCount=0;
	//Array of all possible terms
	Term<T> allTerms[100];
	Polynomial<T> final;
	//Starting with the first array All points are multiplied by all other points in the second array. Once itteration is completed, the second position is multiplied by every other in the second, etc. They are then sorted evaluated and placed by highest ten terms in matter of degree
	for (int i=0;i<counter;i++)
	{
		for (int j=0;j<p.counter;j++)
		{
			allTerms[tempCount]=Term<T>((polynomial[i].getCoefficient()*p.polynomial[j].getCoefficient()), (polynomial[i].getDegree()+p.polynomial[j].getDegree()));
			tempCount++;
		}
	}
	sort(allTerms, tempCount);
	int iteratorCount=0;
	while (final.counter!=10&&!(final.counter==tempCount))
		{
			final.addTerm(allTerms[iteratorCount]);
			final.evaluate();
			iteratorCount++;
		}
	sort(final.polynomial, final.counter);
	return final;
}
template <class T> Polynomial<T> Polynomial<T>::operator*(const int& n)
{
	//Temporary array is created. Each point in the array is multiplied by the number
	Polynomial<T> temp;
	for (int i=0;i<counter;i++)
	{
		temp.addTerm(polynomial[i]);
	}
	for (int i=0;i<temp.counter;i++)
	{
		temp.polynomial[i]=Term<T>((temp.polynomial[i].getCoefficient()*n), temp.polynomial[i].getDegree());
	}
	return temp;
}
template <class T> void Polynomial<T>::writeToFile()
{
	//User is asked for a file and one polynomial is written to that file.
	ofstream ofile;
	cout << "Enter the name of the file you would like to output to." << endl;
	string s;
	cin >> s;
	s=s+".txt";
	ofile.open(s.c_str());
	ofile << counter;
	for (int i=0;i<counter;i++)
	{
		ofile << "\n" << polynomial[i].getCoefficient() << " " << polynomial[i].getDegree();
	}
	ofile.close();	
}
//Multiplies each point in the array by the number
template <class T> Polynomial<T> operator*(const int& n, const Polynomial<T>& p)
{
	Polynomial<T> temp;
	for (int i=0;i<p.counter;i++)
	{
		temp.addTerm(p.polynomial[i]);
	}
	for (int i=0;i<p.counter;i++)
	{
		temp.polynomial[i]=Term<T>(temp.polynomial[i].getCoefficient()*n, temp.polynomial[i].getDegree());
	}
	
	return temp;
}
//Takes the power of the x value to the degree and multiplies it to the coefficient. These are added into a variable called answer which is the total tally for all numbers
template <class T> int Polynomial<T>::evalPoly(const int& n)
{
	int answer=0;
	for (int i=0;i<counter;i++)
	{
		//cout << "nums is " << pow(n,polynomial[i].getDegree())*polynomial[i].getCoefficient() << endl;
		answer+=pow(n,polynomial[i].getDegree())*polynomial[i].getCoefficient();
		//cout << "ans is " << answer << endl;
	}
	return answer;
} 
template <class T> ifstream& operator>>(ifstream& file, Polynomial<T>& p)
{
	int choice, t2;
	T t1;
	bool valid;
	file >> choice;
	//checks if degree is valid
	if (choice>0&&choice<=MAX_TERMS)
	{
		valid=true;
		cout << "File is valid. Will read from file." << endl;
	}
	else
	{
		cout <<  "A valid int was not used; will not read from the file." << endl;
		valid=false;
	}
	if (valid)
	{
		while (!file.eof()&&choice>0)
		{
			file >> t1;
			file >> t2;
			if (t2<0)
			{
				cout << "This Term will not be used as a negative is in the denominator; Term will be truncated" << endl;
			}
			else
			{
				//cout << "in the " << count << "time we have values " << t1 << " " << t2 << endl;
				//cout << "before adds terms one and two are " << Term<int>(t1,t2);
				p.addTerm(Term<T>(t1,t2));
				choice--;
				//cout << "The polynomail for this iteration is " << p.polynomial[count] << endl;
			}
			
		}
		p.counter--;
	}
	else
	{
		p.polynomial[0]=Term<T>(0,1);
	}
	p.evaluate();
	p.sort(p.polynomial, p.counter);
	//cout << p.polynomial[0] << "    " << p.polynomial[1] << "        " << p.polynomial[2] << "      " << p.polynomial <<"    " <<  p.polynomial << endl;
	return file;
}
template <class T> Term<T> Polynomial<T>::getTerm(const int& n)
{
	return polynomial[n];
}
template <class T> int Polynomial<T>::getCount()
{
	return counter;
}
//Assigns polynomial p to the called polynomial. Itterates through and an array to do so.
template <class T> void Polynomial<T>::operator=(const Polynomial<T>& p)
{
	counter=p.counter;
	for (int i=0; i<p.counter; i++)
	{
		polynomial[i]=Term<T>(p.polynomial[i].getCoefficient(), p.polynomial[i].getDegree());
	}
}

template <class T> istream& operator>>(istream& c, Polynomial<T>& p)
{
	//checks for a valid number of terms and degree. creates term if valid
	cout << "How many terms will this polynomial be? Please enter a value between 1 and 10." << endl;
	bool done=false;
	int choice=0;
	while(!done)
	{
		choice=getValidInt();
		if (choice>0&&choice<=MAX_TERMS)
			done=true;
		else
			cout << "You did not enter a value between 1 and ten. Please enter an int value between 1 and 10." << endl;
	}	
	int counter=0;
	Term<T> t;
	while (counter<choice)
	{
		//for loop that starts at highest degree
		cin >> t;
		p.addTerm(t);
		counter++;
	}
	p.evaluate();
	p.sort(p.polynomial, p.counter);
	return c;
}
//Checks all points in the array. Starting with the first checks the degree of itself and all others to see if there are polynomials with the same degree. If so they are added together and a counter is removed to make up for the removed term.
template <class T> void Polynomial<T>::evaluate()
{
	for (int i=0; i<counter;i++)
	{
		for (int j=0; j<counter; j++)
		{
			if (i==j)
			{}
			else
			{
				if (polynomial[i].getDegree()==polynomial[j].getDegree())
				{
					polynomial[i]=Term<T>(((polynomial[i].getCoefficient())+polynomial[j].getCoefficient()), polynomial[i].getDegree());
					int placement=j;
					while (j<counter)
					{
						polynomial[j]=polynomial[j+1];
						j++;
					}
					counter--;
				}
			}
		}
	}
}
//These methods call the term output stream method. Also format pluses and minuses for addition and subtraction
template <class T> ostream& operator<<(ostream& o, Polynomial<T>& p)
{
	int iterator=0;
	int neg=0, pos=0;
	int endTerm=0;
	bool degZero=false;
	bool coe=false;
	//While there are more terms
	while (iterator<p.counter)
	{
		//cout << "printing " << iterator << " itteration" << endl;
		//cout << "endTerm is " << endTerm << endl;
		//cout << "counter is " << p.counter << endl;
		//cout <<"This polynomial at [0] is " <<  p.polynomial[0] << "coeficient and degree is " << p.polynomial[0].getCoefficient() << " " << p.polynomial[0].getDegree() << endl;
		//cout <<"This polynomial at [1] is " <<  p.polynomial[1] << "coeficient and degree is " << p.polynomial[1].getCoefficient() << " " << p.polynomial[1].getDegree() << endl;
		
		//If this is the first itteration through
		if (iterator==0)
		{
			//cout << "enters" << endl;
			if (p.polynomial[iterator].getDegree()==0)
			{
				endTerm=endTerm+p.polynomial[iterator].getCoefficient();
				iterator++;
			}
			else
			{
				o << p.polynomial[iterator];
				iterator++;
			}
			//cout << "number is " << iterator << endl <<" << endl << p.polynomial[iterator-1].getCoefficient() << endl;
			if (p.polynomial[iterator-1].getCoefficient()==0)
			{
				//cout << "true" << endl;
				coe=true;
			}
		}
		//If not add a plus or minus sign before the term
		else
		{
			//cout << "number is in else" << iterator << endl;
			if (coe)
			{
				cout << p.polynomial[iterator];
				iterator++;
			}
			else if (p.polynomial[iterator].getCoefficient()>0)
			{
				degZero=true;
				o << "+" << p.polynomial[iterator];
				iterator++;
			}
			else
			{
				degZero=true;
				o << p.polynomial[iterator];
				iterator++;
			}
		}
	}
	if (iterator>0)
	{
		//cout << endl << "pos is " << pos << endl << "neg is " << neg << endl;
		//If there was one iteration print the endTerm if it is not zero
		if (iterator==1)
		{
			if (endTerm!=0)
				cout << endTerm;
		}
		//If not add the plus and minus sign before the end term is printed
		else
		{
			if (endTerm!=0)
			{
				if (endTerm>0)
				{
					cout << "+" << endTerm;
				}
				else if (endTerm<0);
				{
					cout << endTerm;
				}
			}
		}
		/*else if (pos!=0)
		{
			if (degZero==true)
				cout << "+" << pos;
			else
				cout << pos;
		}
		else
		{
			cout << "-" << neg;
		}
*/	}
	//cout << endl;
	return o;
}




