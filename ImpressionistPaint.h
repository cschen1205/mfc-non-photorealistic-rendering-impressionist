// ImpressionistPaint.h : main header file for the ImpressionistPaint application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImpressionistPaintApp:
// See ImpressionistPaint.cpp for the implementation of this class
//

class CImpressionistPaintApp : public CWinApp
{
public:
	CImpressionistPaintApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImpressionistPaintApp theApp;