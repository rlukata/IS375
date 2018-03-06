// ramiLukata_Assignment2.cpp : main project file.

#include "stdafx.h"
#include <stdio.h>


using namespace std;
using namespace System;

/*
Integer that returns the amount of non-alphabetical characters ignoring white spaces
*/
int non_letters(String ^ incomingString) {
	int numberOfNonLetters = 0;
	for each (Char c in incomingString) {
		if (Char::IsWhiteSpace(c)) continue;
		else if (!Char::IsLetter(c)) numberOfNonLetters++;
	}
	return numberOfNonLetters;
}


/*
Integer that returns the amount of upper case letters ignoring white spaces
*/
int upperCase(String ^ incomingString) {
	int numberOfUpperCase = 0;
	for each (Char c in incomingString) {
		if (Char::IsWhiteSpace(c)) continue;
		else if (Char::IsUpper(c)) numberOfUpperCase++;
	}
	return numberOfUpperCase;
}

/*
Integer that returns the amount of lower case letters ignoring white spaces
*/
int lowerCase(String ^ incomingString) {
	int numberOfLowerCase = 0;
	for each (Char c in incomingString) {
		if (Char::IsWhiteSpace(c)) continue;
		else if (Char::IsLower(c)) numberOfLowerCase++;
	}
	return numberOfLowerCase;
}

/*
Bool that splits the string in two integers (disregards decimal), and compares
the first character and the last one. Then iterates in reverse order making the
same comparison. If no differences are found, it's a palyndrome and returns true.
*/
bool isPalindrome(String ^ incomingString) {
	int lengths = incomingString->Length;
	int halflength = lengths / 2;
	for (int i = 0; i <= (halflength); i++) {
		if (incomingString[i] != incomingString[lengths - 1]) return false;
		else lengths--;
	}
	return true;
}

/*
Test to show the functionality of the functions.
*/
int main(array<System::String ^> ^args) {

	//declaration of String^ variables
	//gncew refers to the new garbage collector for memory
	String ^ letterString = gcnew String("This is a string! And has ");
	String ^ numberString = gcnew String("This is a string with numbers: 1234567890. It has ");
	String ^ palindromeString = gcnew String("madam");
	String ^ palindromeString2 = gcnew String("nun");
	String ^ palindromeString3 = gcnew String("racecar");
	String ^ palindromeString4 = gcnew String("adrian");

	Console::WriteLine(letterString + letterString->Length + " chars.");
	Console::WriteLine(numberString + numberString->Length + " chars.");

	//counting the number of digits on each predefined string
	Console::WriteLine(letterString + non_letters(letterString) + " non-alphabetic characters");
	Console::WriteLine(numberString + non_letters(numberString) + " non-alphabetic characters");

	//counting number of upper case letters on each predefined string
	Console::WriteLine(letterString + upperCase(letterString) + " upper-case letters");
	Console::WriteLine(numberString + upperCase(numberString) + " upper-case letters");

	//counting the number of lower case letters on each predefined string
	Console::WriteLine(letterString + lowerCase(letterString) + " lower-case letters");
	Console::WriteLine(numberString + lowerCase(numberString) + " lower-case letters");

	//counting the number of lower case letters on each predefined string
	Console::WriteLine("Is " + palindromeString + " palindrome? " + isPalindrome(palindromeString));
	Console::WriteLine("Is " + palindromeString2 + " palindrome? " + isPalindrome(palindromeString2));
	Console::WriteLine("Is " + palindromeString3 + " palindrome? " + isPalindrome(palindromeString3));
	Console::WriteLine("Is " + palindromeString4 + " palindrome? " + isPalindrome(palindromeString4));

	getchar();
    return 0;
}
