// ImpressionistPaintView.cpp : implementation of the CImpressionistPaintView class
//

#include "stdafx.h"
#include "ImpressionistPaint.h"

#include "ImpressionistPaintDoc.h"
#include "ImpressionistPaintView.h"
#include "Display.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImpressionistPaintView

IMPLEMENT_DYNCREATE(CImpressionistPaintView, CView)

BEGIN_MESSAGE_MAP(CImpressionistPaintView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_IMPRESSIONIST_LOADIMAGE, &CImpressionistPaintView::OnImpressionistLoadimage)
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_IMAGE_DISPLAYCANVAS, &CImpressionistPaintView::OnImageDisplaycanvas)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DISPLAYCANVAS, &CImpressionistPaintView::OnUpdateImageDisplaycanvas)
	ON_COMMAND(ID_IMAGE_DISPLAYSOURCE, &CImpressionistPaintView::OnImageDisplaysource)
	ON_UPDATE_COMMAND_UI(ID_IMAGE_DISPLAYSOURCE, &CImpressionistPaintView::OnUpdateImageDisplaysource)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CImpressionistPaintView construction/destruction

CImpressionistPaintView::CImpressionistPaintView()
: m_bLeftMouseDown(FALSE)
, m_ptLeftDownPos(0)
, m_bPaintBackground(TRUE)
{
	// TODO: add construction code here
	gDisplay.SetView(this);
}

CImpressionistPaintView::~CImpressionistPaintView()
{
}

BOOL CImpressionistPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CImpressionistPaintView drawing

void CImpressionistPaintView::OnDraw(CDC* pDC)
{
	CImpressionistPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect drRect;
	GetClientRect(&drRect);

	pDoc->Display(pDC, drRect);

	

}


// CImpressionistPaintView printing

BOOL CImpressionistPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImpressionistPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImpressionistPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CImpressionistPaintView diagnostics

#ifdef _DEBUG
void CImpressionistPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CImpressionistPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImpressionistPaintDoc* CImpressionistPaintView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImpressionistPaintDoc)));
	return (CImpressionistPaintDoc*)m_pDocument;
}
#endif //_DEBUG


// CImpressionistPaintView message handlers

void CImpressionistPaintView::OnImpressionistLoadimage()
{
	// TODO: Add your command handler code here
	CImpressionistPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFileDialog fDialog(TRUE,
		_T("bmp"),
		_T("source.bmp"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Bitmap File (*.bmp)|*.bmp|Jpeg File (*.jpg)|*.jpg|Gif File (*.gif)|*.gif|PNG File (*.png)|*.png|All Files (*.*)|*.*||"),
		NULL);

	if(fDialog.DoModal() != IDOK)
	{
		return;
	}

	pDoc->LoadSourceImage(fDialog.GetPathName());

	Invalidate();
	UpdateWindow();
}

void CImpressionistPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_bLeftMouseDown==TRUE || GetCapture()==this)
	{
		CImpressionistPaintDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc!=NULL)
		{
			CRect drRect;
			GetClientRect(&drRect);
		
			pDoc->OnLeftMouseDragged(m_ptLeftDownPos, point, drRect);
			m_ptLeftDownPos=point;

			Invalidate(FALSE);
			//UpdateWindow();
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CImpressionistPaintView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);
}

void CImpressionistPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bLeftMouseDown=TRUE;
	m_ptLeftDownPos=point;
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

void CImpressionistPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bLeftMouseDown=FALSE;
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


void CImpressionistPaintView::OnImageDisplaycanvas()
{
	// TODO: Add your command handler code here
	CImpressionistPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc==NULL)
	{
		return;
	}

	pDoc->OnImageDisplaycanvas();

	Invalidate(FALSE);
	UpdateWindow();
}

void CImpressionistPaintView::OnUpdateImageDisplaycanvas(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CImpressionistPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc==NULL)
	{
		return;
	}

	pDoc->OnUpdateImageDisplaycanvas(pCmdUI);
}

void CImpressionistPaintView::OnImageDisplaysource()
{
	// TODO: Add your command handler code here
	CImpressionistPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc==NULL)
	{
		return;
	}

	pDoc->OnImageDisplaysource();

	Invalidate(FALSE);
	UpdateWindow();
}

void CImpressionistPaintView::OnUpdateImageDisplaysource(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CImpressionistPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc==NULL)
	{
		return;
	}

	pDoc->OnUpdateImageDisplaysource(pCmdUI);
}

void CImpressionistPaintView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if(nChar == VK_RETURN)
	{
		CImpressionistPaintDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc==NULL)
		{
			return;
		}

		pDoc->OnImpressionistBatchrun();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
