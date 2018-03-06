// ramiLukata_Assignment1.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "iostream"

using namespace std;

/*
initial code setup by Visual Studio 2013
*/
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

/*
double function that takes two double values and returns their product
*/
double multiply(double a, double b) {
	return (a * b);
}

/*
double function that takes two double values and returns their division
throws error message if the denominator is 0
*/
double division(double a, double b) {
	if (b == 0) {
		throw "Division by zero condition!";
	}
	return (a / b);
}

/*
double function that takes two double values and returns their substraction
*/
double substract(double a, double b) {
	return (a - b);
}

/*
double function that takes two double values and returns their addition
*/
double addition(double a, double b) {
	return (a + b);
}

/*
Main
*/
int main() {
	cout << "Welcome to Rami's basic calculator. This program takes two inputs," << endl;
	cout << "and computes a result based on the available operators. If the input starts" << endl;
	cout << "with numbers, it will read the first set and ignore the rest of the data." << endl << endl;
	bool stop = false;
	while (!stop) {
		double input1 = 0.0;
		double input2 = 0.0;
		double result;
		char operation;
		char finish = 'n';
		// try catch block catches when input1 or input2 do not contain a double value
		try {
			cout << "Input the first number: ";
			if (cin >> input1) {
				//ignores and clears any data after the first set of numbers
				// for exmaple: entry 99=33242 should only reads the first two characters
				cin.ignore(10000, '\n');
				cout << "Your first input is:" << input1 << endl;
				cout << "Input the second number: ";
				if (cin >> input2) {
					//ignores and clears any data after the first set of numbers
					// for exmaple: entry 99=33242 should only reads the first two characters
					cin.ignore(10000, '\n');
					cout << "Your second input is:" << input2 << endl;
					cout << "Choose operator: x, /, -, +: ";
					cin >> operation;
					//iteration that reads operator, and calls the function according to the user entry
					//if the entry is not valid, the program will restart
					if (operation == 'x') cout << "Your operation returned: " << (result = multiply(input1, input2)) << endl;
					else if (operation == '/') cout << "Your operation returned: " << (result = division(input1, input2)) << endl;
					else if (operation == '-') cout << "Your operation returned: " << (result = substract(input1, input2)) << endl;
					else if (operation == '+') cout << "Your operation returned: " << (result = addition(input1, input2)) << endl;
					else cout << "Operator not valid." << endl;
				}
				else {
					throw "Not a number";
				}
			}
			else {
				throw "Not a number";
			}
		}
		catch (const char* msg) {
			cout << msg << endl;
		}
		//clear cin from any error flags
		//ignore cin buffer to clear memory, otherwise finish adopts bad value
		cin.clear();
		cin.ignore(10000, '\n');
		//restart program
		cout << "Continue? Type the character 'y' to continue: ";
		cin >> finish;
		if (finish == 'y') stop = false;
		else stop = true;
	};
	return 0;
}