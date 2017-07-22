#pragma once
#include "afx.h"
#include <fstream>
#include <iostream>

class CMainFrame;
class CImpressionistPaintView;
class CImpressionistPaintDoc;

class Display :
	public CObject
{
public:
	static Display& Instance();
	~Display(void);

private:
	Display(void);
	Display(const Display& rhs) { }
	Display& operator=(const Display& rhs) { return *this; }

public:
	void SetMainFrame(CMainFrame* pMainFrm);
	void SetView(CImpressionistPaintView* pView);
	void SetDoc(CImpressionistPaintDoc* pDoc);

public:
	void InvalidateView(BOOL bErased=TRUE);

private:
	CMainFrame* m_pMainFrm;
	CImpressionistPaintView* m_pView;
	CImpressionistPaintDoc* m_pDoc;

private:
	std::ofstream m_outfile;
	static bool m_bInstanceFlag;
	static Display* m_pInstance;
public:
	void GetClientRect(CRect& drRect);
};

#define gDisplay Display::Instance()
