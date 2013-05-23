// Name: Steven Kolln
// Description: User interface class

#include "polyFunctions.h"
#include "UI.h"
#include "Polynomial.cpp"
#include "Term.cpp"

using namespace std;


//UI constructor which sets the number of polynomials to 0
UI::UI()
{
	intPolyNumber=complexPolyNumber=doublePolyNumber=0;
	doubleP=intP=complexP=false;
}
//Main loop of program. Ask for what action the user would like to do. Continues untill a 0 is pressed
void UI::start()
{
	//user choose what data type to use
	int response=-2;
	cout << "What data type would you like to work with on your polynomials?" << endl << "1. Integers     2. Doubles     3. Complex." << endl <<"Response:";
	while (response<1||response>3)
	{
		response=getValidInt();
		if (response<1||response>3)
		{
			cout << "You entered " << response << ". Please enter a number between 1 and 3." << endl << endl;
			cout << "What data type would you like to work with on your polynomials?" << endl << "1. Integers     2. Doubles     3. Complex." << endl <<"Response:";
		}
	}
	if (response==1)
	{
		intP=true;
		cout << "You will be working with integers." << endl;
	}
	else if (response==2)
	{
		doubleP=true;
		cout << "You will be working with doubles." << endl;
	}
	else if (response==3)
	{
		complexP=true;
		cout << "You will be working with Complex numbers." << endl;
	}
	response=-1;
	while (response!=6)
	{
		//main screen waiting to take answers for which action to start next
		showOptions();
		while (response<1||response>6)
		{
			response=getValidInt();
			if (response<1||response>6)
			{
				cout << "You entered " << response << ". Please enter a number between 1 and 6." << endl << endl;
				showOptions();
			}
			switch (response)
			{
				case 1:
					seeAll();
					response=-1;
					showOptions();
					break;
				case 2:
					add();
					response=-1;
					showOptions();
					break;
				case 3:
					multiply();
					response=-1;
					showOptions();
					break;
				case 4:
					createPoly();
					response=-1;
					showOptions();
					break;
				case 5:
					writeToFile();
					response=-1;
					showOptions();
				case 6:
					break;
				default:
					response=-1;
					cout << "You did not enter a correct value. Please try again" << endl;
					showOptions();
					break;
			}
		}
		
	}
	cout << endl << "Thanks! Exiting program!" << endl;
	
}
void UI::createPoly()
{
	//checks to make sure there is room for another polynomial
	if (intPolyNumber>=10||doublePolyNumber>=10||complexPolyNumber>=10)
	{
		cout << "You can not add any more polynomials you already have the max allowed number 10." << endl << endl;
	}
	//if not full
	else
	{
		bool readFile=false;
		cout << endl << "Would you like to read from a file or enter from a keyboard?" << endl << "1. Read from a file.     2. Enter from the keyboard." << endl << "Response:";
		int input=-1;
		//determines whether to read from a file or keyboard.input value is kept for later.
		while (input<1||input>2)
		{
			input=getValidInt();
			if  (input==1||input==2)
			{
				if (input==2)
				{
					cout << endl << "You will be reading from the keyboard." << endl;
				}
				else
				{
					cout << endl << "You will be reading from a file." << endl;
				}
			}
			else
			{
				cout << "You entered " << input << ". Please press: 1. Read from a file.     2. Enter from the keyboard." << endl << "Response:";
			}
		}
		int polysToCreate=11;
		//if using the integer version for ui
		if (intP)
		{
			//determines how many polynomials are available to make
			cout << "How many polynomials would you like to make? You have enough room for " << (LIMIT-intPolyNumber) << " more polynomials." << endl << "Response:";
			while ((LIMIT-intPolyNumber)<polysToCreate||polysToCreate<1)
			{
				polysToCreate=getValidInt();
				//cout << endl << "polys create is " << polysToCreate;
				if ((LIMIT-intPolyNumber)<polysToCreate)
					cout << "You don't have room for that! You have enough room for " << (LIMIT-intPolyNumber) << " not " << polysToCreate << ". Please enter another number." << endl << "Response:";
				if (polysToCreate<1)
				{
					cout << "Please enter a value greater than 0." << endl << "Please enter another number." << endl << "Response:";
				}
			}
			//reads from a file
			if (input==1)
			{
				while (polysToCreate>0)
				{
					Polynomial<int> p;
					bool worked = true;
					string inFileName;
					ifstream inStr;
					int quit=1;
					do 
					{
						cout << "Enter name of file to read from: ";
						cin >> inFileName;
						
						inStr.open (inFileName.c_str());
						if (inStr.fail())
						{
							cerr << "Error opening file. If you want to try again type 1 if not type any other number." << endl << "Response:";
							inStr.clear();
							inStr.ignore(80, '\n');
							worked = false;
							quit=getValidInt();
						}
						else 
							worked = true;
						
					} while (!worked&&quit==1);
					cout << endl;
					// Input file format is similar to how data is entered from keyboard
					// First number specifies the number of terms in the polynomial
					// Followed by pairs of numbers for each term 
					//          - first one is coefficient
					//          - second one is degree
					
					//It is assumed that files with degrees of only postive degrees are used. If not the polynomial is still instantiated however that term is skiped.
					inStr >> p;
					//cout << "p is " << p.getTerm(0) << endl;
					if((p.getTerm(0)).getDegree()==1&&(p.getTerm(0)).getCoefficient()==0)
					{
						cout << "Polynomial not added; It was not read from a file correctly." << endl << endl;
					}
					else
					{
						//Why doesn't this work???
						intPoly[intPolyNumber]=p;
						intPolyNumber++;
					}
					inStr.close();
					polysToCreate--;
				}
			}
			//read from keyboard
			else
			{
				for (int i=0;i<polysToCreate;i++)
				{
					Polynomial<int> polynom;
					cin >> polynom;
					intPoly[intPolyNumber]=polynom;
					intPolyNumber++;
				}
			}
		}
		//Does same procedure for the double version of UI
		else if (doubleP)
		{
			cout << "How many polynomials would you like to make? You have enough room for " << (LIMIT-doublePolyNumber) << " more polynomials." << endl << "Response:";
			while ((LIMIT-doublePolyNumber)<polysToCreate||polysToCreate<1)
			{
				polysToCreate=getValidInt();
				//cout << endl << "polys create is " << polysToCreate;
				if ((LIMIT-doublePolyNumber)<polysToCreate)
					cout << "You don't have room for that! You have enough room for " << (LIMIT-doublePolyNumber) << " not " << polysToCreate << ". Please enter another number." << endl << "Response:";
				if (polysToCreate<1)
				{
					cout << "Please enter a value greater than 0." << endl << "Please enter another number." << endl << "Response:";
				}
			}
			if (input==1)
			{
				while (polysToCreate>0)
				{
					Polynomial<double> p;
					bool worked = true;
					string inFileName;
					ifstream inStr;
					int quit=1;
					do 
					{
						cout << "Enter name of file to read from: ";
						cin >> inFileName;
						
						inStr.open (inFileName.c_str());
						if (inStr.fail())
						{
							cerr << "Error opening file. If you want to try again type 1 if not type any other number." << endl << "Response:";
							inStr.clear();
							inStr.ignore(80, '\n');
							worked = false;
							quit=getValidInt();
						}
						else 
							worked = true;
						
					} while (!worked&&quit==1);
					cout << endl;
					// Input file format is similar to how data is entered from keyboard
					// First number specifies the number of terms in the polynomial
					// Followed by pairs of numbers for each term 
					//          - first one is coefficient
					//          - second one is degree
					
					//It is assumed that files with degrees of only postive degrees are used. If not the polynomial is still instantiated however that term is skiped.
					inStr >> p;
					if((p.getTerm(0)).getDegree()==1&&(p.getTerm(0)).getCoefficient()==0)
					{
						cout << "Polynomial not added; It was not read from a file correctly." << endl << endl;
					}
					else
					{
						doublePoly[doublePolyNumber]=p;
						doublePolyNumber++;
					}
					inStr.close();
					polysToCreate--;
					
				}
			}
			else
			{
				for (int i=0;i<polysToCreate;i++)
				{
					Polynomial<double> polynom;
					cin >> polynom;
					doublePoly[doublePolyNumber]=polynom;
					doublePolyNumber++;
				}
			}
		}
		else if (complexP)
		{
			if (input==1)
			{
			}
			else
			{
			}
		}
	}
}
//Determines what two polynomials to add and displays their addition
void UI::add()
{
	if (intP)
	{
		//If there is at least 1 polynomial to add
		if (intPolyNumber>0)
		{
			seeAll();
			int again=1;
			while (again==1)
			{
				cout << "What is the initial polynomial you would like to use for addition?" << endl << "Response:";
				int choice1, choice2;
				bool response=false;
				choice1=getValidInt();
				while (!response)
				{
					if (choice1>0&&choice1<=intPolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << intPolyNumber << "." << endl << "Response:";
						choice1=getValidInt();
					}
				}
				response=false;
				cout << endl << "What is the second Polynomial you would like to use? The same Polynomial can be added." << endl << "Response:";
				choice2=getValidInt();
				while (!response)
				{
					if (choice2>0&&choice2<=intPolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << intPolyNumber << "." << endl << "Response:";
						choice2=getValidInt();
					}
				}
				Polynomial<int> p3=intPoly[choice1-1]+intPoly[choice2-1];
				cout << endl << intPoly[choice1-1] << " Added with " << intPoly[choice2-1] << " equals: " << p3 << endl;
				cout << "Would you like to add more polynomials? Press 1 for yes or any other number for no." << endl << "Response:";
				again=getValidInt();
			}
		}
		else
			seeAll();
	}
	// for double
	else if (doubleP)
	{
		if (doublePolyNumber>0)
		{
			seeAll();
			int again=1;
			while (again==1)
			{
				cout << "What is the initial polynomial you would like to use for addition?" << endl << "Response:";
				int choice1, choice2;
				bool response=false;
				choice1=getValidInt();
				while (!response)
				{
					if (choice1>0&&choice1<=doublePolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << doublePolyNumber << "." << endl << "Response:";
						choice1=getValidInt();
					}
				}
				response=false;
				cout << endl << "What is the second Polynomial you would like to use? The same Polynomial can be added." << endl << "Response:";
				choice2=getValidInt();
				while (!response)
				{
					if (choice2>0&&choice2<=doublePolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << doublePolyNumber << "." << endl << "Response:";
						choice2=getValidInt();
					}
				}
				Polynomial<double> p3=doublePoly[choice1-1]+doublePoly[choice2-1];
				cout << endl << doublePoly[choice1-1] << " Added with " << doublePoly[choice2-1] << " equals: " << p3 << endl;
				cout << "Would you like to add more polynomials? Press 1 for yes or any other number for no." << endl << "Response:";
				again=getValidInt();
			}
		}
		else
			seeAll();
	}
	else if (complexP)
	{
	}
}
void UI::writeToFile()
{
	if (intP)
	{
		if (intPolyNumber>0)
		{
			int choice;
			seeAll();
			cout << "Which polynomial would you like to write to a file?" << endl << "Response:";
			choice=getValidInt();
			bool response=false;
			while (!response)
			{
				if (choice>0&&choice<=intPolyNumber)
					response=true;
				else
				{
					cout << "Please enter a number between 1 and " << intPolyNumber << "." << endl << "Response:";
					choice=getValidInt();
				}
			}
			Polynomial<int> p3=intPoly[choice-1];
			p3.writeToFile();
		}
	}
	else if (doubleP)
	{
		if (doublePolyNumber>0)
		{
			int choice;
			seeAll();
			cout << "Which polynomial would you like to write to a file?" << endl << "Response:";
			choice=getValidInt();
			bool response=false;
			while (!response)
			{
				if (choice>0&&choice<=doublePolyNumber)
					response=true;
				else
				{
					cout << "Please enter a number between 1 and " << doublePolyNumber << "." << endl << "Response:";
					choice=getValidInt();
				}
			}
			Polynomial<double> p3=doublePoly[choice-1];
			p3.writeToFile();
		}
	}
	
}
//same as add but for multiply
void UI::multiply()
{
	if (intP)
	{
		if (intPolyNumber>0)
		{
			seeAll();
			int again=1;
			while (again==1)
			{
				cout << "What is the initial polynomial you would like to use for multiplication?" << endl << "Response:";
				int choice1, choice2;
				bool response=false;
				choice1=getValidInt();
				while (!response)
				{
					if (choice1>0&&choice1<=intPolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << intPolyNumber << "." << endl << "Response:";
						choice1=getValidInt();
					}
				}
				response=false;
				cout << endl << "What is the second Polynomial you would like to use? The same Polynomial can be multiplied." << endl << "Response:";
				choice2=getValidInt();
				while (!response)
				{
					if (choice2>0&&choice2<=intPolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << intPolyNumber << "." << endl << "Response:";
						choice2=getValidInt();
					}
				}
				Polynomial<int> p3=intPoly[choice1-1]*intPoly[choice2-1];
				cout << endl << intPoly[choice1-1] << " Multiplied with " << intPoly[choice2-1] << " equals: " << p3 << endl;
				cout << "Would you like to multiply more polynomials? Press 1 for yes or any other number for no." << endl << "Response:";
				again=getValidInt();
			}
		}
		else
			seeAll();
	}
	else if (doubleP)
	{
		if (doublePolyNumber>0)
		{
			seeAll();
			int again=1;
			while (again==1)
			{
				cout << "What is the initial polynomial you would like to use for multiplication?" << endl << "Response:";
				int choice1, choice2;
				bool response=false;
				choice1=getValidInt();
				while (!response)
				{
					if (choice1>0&&choice1<=doublePolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << doublePolyNumber << "." << endl << "Response:";
						choice1=getValidInt();
					}
				}
				response=false;
				cout << endl << "What is the second Polynomial you would like to use? The same Polynomial can be multiplied." << endl << "Response:";
				choice2=getValidInt();
				while (!response)
				{
					if (choice2>0&&choice2<=doublePolyNumber)
						response=true;
					else
					{
						cout << "Please enter a number between 1 and " << doublePolyNumber << "." << endl << "Response:";
						choice2=getValidInt();
					}
				}
				Polynomial<double> p3=doublePoly[choice1-1]*doublePoly[choice2-1];
				cout << endl << doublePoly[choice1-1] << " Multiplied with " << doublePoly[choice2-1] << " equals: " << p3 << endl;
				cout << "Would you like to multiply more polynomials? Press 1 for yes or any other number for no." << endl << "Response:";
				again=getValidInt();
			}
		}
		else
			seeAll();
	}
	else if (complexP)
	{
	}
}
void UI::seePoly()
{
}
void UI::seeAll()
{
	//if there are no polynomials inform the user. 
	if (intP)
	{
		if (intPolyNumber==0)
		{
			cout << "Oh no! You currently don't have any polynomials. You should go back to the main screen and select 'Create a new Polynomial.'" << endl << endl;
		}
		//If not show them all for ints
		else
		{
			cout << endl;
			for (int i=0;i<intPolyNumber;i++)
			{
				cout << "Polynomial " << i+1 << " is: ";
				printPolyInt(i+1);
			}
		}
	}
	//shows all for doubles
	else if(doubleP)
	{
		if (doublePolyNumber==0)
		{
			cout << "Oh no! You currently don't have any polynomials. You should go back to the main screen and select 'Create a new Polynomial.'" << endl << endl;
		}
		else
		{
			for (int i=0;i<doublePolyNumber;i++)
			{
				cout << "Polynomial " << i+1 << " is: ";
				printPolyDouble(i+1);
				//cout << endl;
			}
		}
	}
	else if (complexP)
	{
		if (complexPolyNumber==0)
		{
			cout << "Oh no! You currently don't have any polynomials. You should go back to the main screen and select 'Create a new Polynomial.'" << endl << endl;
		}
		else
		{
			for (int i=0;i<complexPolyNumber;i++)
			{
				cout << "Polynomial " << i+1 << " is: ";
				//printPolyComplex(i+1);
				cout << endl;
			}
		}
	}
}
bool UI::createPolyFromFile()
{
	return true;
}
void UI::showOptions()
{
	cout << "What would you like to do?" << endl << endl;
	cout << "1. See all current Polynomials" << endl << "2. Add polynomials together." << endl << "3. Multiply Polynomials together." << endl << "4. Create a new Polynomial." << endl <<"5. Write a polynomial to a file." << endl << "6. Quit." << endl << "Response:"; 
	
}
//Prints the array elements for int. Also done for double and complex
void UI::printPolyInt(const int& number)
{
	switch (number)
	{
		case 1:
			cout <<intPoly[0] << endl;
			break;
		case 2:
			cout <<intPoly[1] << endl;
			break;
		case 3:
			cout <<intPoly[2] << endl;
			break;
		case 4:
			cout <<intPoly[3] << endl;
			break;
		case 5:
			cout <<intPoly[4] << endl;
			break;
		case 6:
			cout <<intPoly[5] << endl;
			break;
		case 7:
			cout <<intPoly[6] << endl;
			break;
		case 8:
			cout <<intPoly[7] << endl;
			break;
		case 9:
			cout <<intPoly[8] << endl;
			break;
		case 10:
			cout <<intPoly[9] << endl;
			break;
		default:
			cout << "Error printing specific polynomial in printPoly function for int." << endl;
			break;
	}
}
void UI::printPolyDouble(const int& number)
{
	switch (number)
	{
		case 1:
			cout <<doublePoly[0] << endl;
			break;
		case 2:
			cout <<doublePoly[1] << endl;
			break;
		case 3:
			cout <<doublePoly[2] << endl;
			break;
		case 4:
			cout <<doublePoly[3] << endl;
			break;
		case 5:
			cout <<doublePoly[4] << endl;
			break;
		case 6:
			cout <<doublePoly[5] << endl;
			break;
		case 7:
			cout <<doublePoly[6] << endl;
			break;
		case 8:
			cout <<doublePoly[7] << endl;
			break;
		case 9:
			cout <<doublePoly[8] << endl;
			break;
		case 10:
			cout <<doublePoly[9] << endl;
			break;
		default:
			cout << "Error printing specific polynomial in printPoly function for double." << endl;
			break;
	}
}
/*
void UI::printPolyComplex(const int& number)
{
	switch (number)
	{
		case 1:
			cout <<complexPoly[0] << endl;
			break;
		case 2:
			cout <<complexPoly[1] << endl;
			break;
		case 3:
			cout <<complexPoly[2] << endl;
			break;
		case 4:
			cout <<complexPoly[3] << endl;
			break;
		case 5:
			cout <<complexPoly[4] << endl;
			break;
		case 6:
			cout <<complexPoly[5] << endl;
			break;
		case 7:
			cout <<complexPoly[6] << endl;
			break;
		case 8:
			cout <<complexPoly[7] << endl;
			break;
		case 9:
			cout <<complexPoly[8] << endl;
			break;
		case 10:
			cout <<complexPoly[9] << endl;
			break;
		default:
			cout << "Error printing specific polynomial in printPoly function for complex." << endl;
			break;
	}
}
*/
