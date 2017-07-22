// ImpressionistPaintView.h : interface of the CImpressionistPaintView class
//


#pragma once
#include "atltypes.h"


class CImpressionistPaintView : public CView
{
protected: // create from serialization only
	CImpressionistPaintView();
	DECLARE_DYNCREATE(CImpressionistPaintView)

// Attributes
public:
	CImpressionistPaintDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CImpressionistPaintView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImpressionistLoadimage();
protected:
	BOOL m_bLeftMouseDown;
	BOOL m_bPaintBackground;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	CPoint m_ptLeftDownPos;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnImageDisplaycanvas();
	afx_msg void OnUpdateImageDisplaycanvas(CCmdUI *pCmdUI);
	afx_msg void OnImageDisplaysource();
	afx_msg void OnUpdateImageDisplaysource(CCmdUI *pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in ImpressionistPaintView.cpp
inline CImpressionistPaintDoc* CImpressionistPaintView::GetDocument() const
   { return reinterpret_cast<CImpressionistPaintDoc*>(m_pDocument); }
#endif

