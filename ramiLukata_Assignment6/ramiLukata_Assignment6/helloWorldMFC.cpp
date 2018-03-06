/*************************************************************
* File: helloWorld.cpp
*************************************************************/

// include application framework windows class definitions:
/*#include 
include "helloMFC.h"
#pragma once
#include <afx.h>
#include <afxwin.h>   // MFC core and standard components

MyApp::MyApp()
{
	LPCWSTR str = TEXT("Hello world");
	// Create Window with Title Bar
	Create(0,                       // default CFrameWnd class
		str,              // window title
		WS_OVERLAPPEDWINDOW,     // full-featured window
		CRect(100, 100,          // initial position and
		600, 400));       // frame size


	pHello = new CStatic();      // create a static control

	pHello->Create(              // create Windows control
		str, // text
		WS_CHILD | WS_VISIBLE | WS_BORDER  // window styles
		| SS_CENTER,                 // static object styles
		CRect(50, 50, 450, 150),   // window coordinates
		this);                      // context
}

/****************************************
* destructor frees resources
***************************************
MyApp::~MyApp()
{
	delete *pHello;          // only object owned by window 
}

/*************************************************
* Derive our application class CHelloApp based on
* CWinApp
* 1- Overwrite InitInstance() method
* 2- Make main frame window visiable
* 3- Make the main frame window visiable
*************************************************
class CHelloWorldApp : public CWinApp
{
public:
	virtual BOOL InitInstance()   // override default method
	{
		m_pMainWnd = new MyApp();    // instantiate MyApp
		m_pMainWnd->ShowWindow(m_nCmdShow); // make frame visible
		m_pMainWnd->UpdateWindow();           // refresh frame window

		return true;                          // report success
	}

} helloWorldApp;*/