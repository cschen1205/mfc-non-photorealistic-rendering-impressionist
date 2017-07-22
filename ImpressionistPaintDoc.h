// ImpressionistPaintDoc.h : interface of the CImpressionistPaintDoc class
//


#pragma once
#include "MemoryImage.h"
#include "PaintBrush.h"
#include "PaintConfiguration.h"
#include "StrokeGenerator.h"

class CImpressionistPaintDoc : public CDocument
{
protected: // create from serialization only
	CImpressionistPaintDoc();
	DECLARE_DYNCREATE(CImpressionistPaintDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CImpressionistPaintDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	
	PaintBrush* m_pBrush;

	StrokeGenerator m_generator;
	PaintConfiguration m_configuration;

	bool m_bIsCurrentDisplayed;
	BOOL m_bRedrawCanvas;

protected:
	MemoryImage m_imgMemory;
public:
	void Display(CDC* pDC, const CRect& drRect);
	bool LoadSourceImage(LPCTSTR pFileName);
	void OnLeftMouseDragged(const CPoint& ptStart, const CPoint& ptEnd, const CRect& drRect);
	void OnImageDisplaycanvas();
	void OnUpdateImageDisplaycanvas(CCmdUI *pCmdUI);
	void OnImageDisplaysource();
	void OnUpdateImageDisplaysource(CCmdUI *pCmdUI);

	afx_msg void OnUpdateImpressionistSaveimage(CCmdUI *pCmdUI);
	afx_msg void OnImpressionistSaveimage();
	afx_msg void OnUpdateBrushOvalbrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushOvalbrush();
	afx_msg void OnBrushBrushsize();
	afx_msg void OnBrushBackwardslantedbrush();
	afx_msg void OnUpdateBrushBackwardslantedbrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushBackwardslantedrain();
	afx_msg void OnUpdateBrushBackwardslantedrain(CCmdUI *pCmdUI);
	afx_msg void OnBrushPointbrush();
	afx_msg void OnUpdateBrushPointbrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushBackwardslanteddotted();
	afx_msg void OnUpdateBrushBackwardslanteddotted(CCmdUI *pCmdUI);
	afx_msg void OnBrushCirclebrush();
	afx_msg void OnUpdateBrushCirclebrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushSquarebrush();
	afx_msg void OnUpdateBrushSquarebrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushWaterdrop();
	afx_msg void OnUpdateBrushWaterdrop(CCmdUI *pCmdUI);
	afx_msg void OnBrushTexturebrush();
	afx_msg void OnUpdateBrushTexturebrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushEmbossbrush();
	afx_msg void OnUpdateBrushEmbossbrush(CCmdUI *pCmdUI);
	afx_msg void OnBrushTexturebrush32800();
	afx_msg void OnUpdateBrushTexturebrush32800(CCmdUI *pCmdUI);
	afx_msg void OnBrushSlantedline();
	afx_msg void OnUpdateBrushSlantedline(CCmdUI *pCmdUI);
	afx_msg void OnImpressionistClearcanvas();
	afx_msg void OnUpdateImpressionistClearcanvas(CCmdUI *pCmdUI);
	afx_msg void OnImpressionistBatch();
	afx_msg void OnImpressionistExecute();
	afx_msg void OnUpdateImpressionistExecute(CCmdUI *pCmdUI);
	afx_msg void OnImpressionistBatchrun();
	afx_msg void OnUpdateImpressionistBatchrun(CCmdUI *pCmdUI);
};


