#include "StdAfx.h"
#include "Display.h"
#include "MainFrm.h"
#include "ImpressionistPaintView.h"
#include "ImpressionistPaintDoc.h"

bool Display::m_bInstanceFlag=false;
Display* Display::m_pInstance=NULL;

Display::Display(void)
{
	m_outfile.open("debug.txt");
}

Display::~Display(void)
{
	m_outfile.close();
}

Display& Display::Instance()
{
	if(m_bInstanceFlag==false)
	{
		m_pInstance=new Display();
		m_bInstanceFlag=true;
	}
	return *m_pInstance;
}

void Display::SetMainFrame(CMainFrame* pMainFrm)
{
	m_pMainFrm=pMainFrm;
}

void Display::SetView(CImpressionistPaintView *pView)
{
	m_pView=pView;
}

void Display::SetDoc(CImpressionistPaintDoc *pDoc)
{
	m_pDoc=pDoc;
}

void Display::InvalidateView(BOOL bErased)
{
	m_pView->Invalidate(bErased);
	m_pView->UpdateWindow();
}

void Display::GetClientRect(CRect& drRect)
{
	m_pView->GetClientRect(&drRect);
}
