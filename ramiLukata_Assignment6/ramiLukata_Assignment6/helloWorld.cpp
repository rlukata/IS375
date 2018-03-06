#ifndef UNICODE
#define UNICODE
#endif 

//#include "helloWorldWinAPI.h" --> it's throwing an unresolved external error
//because this project is based on CLR
#include <iostream>
#include "helloWorld.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace std;

int main() {

	//this statement uses the CLI library
	Console::WriteLine(L"Hello World! (through CLI)");

	//this statement uses the iostream librabry
	cout << "Hello World! (using iostream)" << endl;

	//this statement runs the form found in the project and shows it
	Application::Run(gcnew ramiLukata_Assignment6::helloWorld);

	//this statement should load the hello world through WindowsAPI
	//if you take helloWorldAPI.h and change to .cpp
	//and then load it into a new project, it will open a window with
	//title "hello world (through Windows API)"
	//loadWinAPI::loadWinAPI();
}