//  Based on an example from Bobobobo's Weblog 
// at: http://bobobobo.wordpress.com/2009/07/11/working-with-odbc-from-c/
// Modified for Visual C++ 2013 using CLI, by Erik Fretheim

#include <sqltypes.h>

using namespace System;

// link with odbc32.lib
#pragma comment( lib, "odbc32.lib" )

class CSketcheDoc
{
protected:
	// If we get an error message, print it.  Selectable whether we print success or not.
	// Selectable whether we error out or not.  Could handle the error differently.
	BOOL CHECK(SQLRETURN rc, System::String^ msg, bool printSucceededMsg = false, bool quit = true);
	
	// Find the status code.
	void status(SQLSMALLINT handleType, SQLHANDLE theHandle, int line);

public:
	void loadDB(SQLVARCHAR* query);

};