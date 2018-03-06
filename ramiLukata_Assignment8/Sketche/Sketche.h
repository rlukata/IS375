
// Sketche.h : main header file for the Sketche application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CSketcheApp:
// See Sketche.cpp for the implementation of this class
//

class CSketcheApp : public CWinApp
{
public:
	CSketcheApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSketcheApp theApp;
