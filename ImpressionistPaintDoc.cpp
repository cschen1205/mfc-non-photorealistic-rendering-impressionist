// ImpressionistPaintDoc.cpp : implementation of the CImpressionistPaintDoc class
//

#include "stdafx.h"
#include "ImpressionistPaint.h"

#include "ImpressionistPaintDoc.h"

#include "PaintBrushOval.h"
#include "DialogSetBrushSize.h"
#include "Display.h"
#include "DlgIPConfig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImpressionistPaintDoc

IMPLEMENT_DYNCREATE(CImpressionistPaintDoc, CDocument)

BEGIN_MESSAGE_MAP(CImpressionistPaintDoc, CDocument)
	
	ON_UPDATE_COMMAND_UI(ID_IMPRESSIONIST_SAVEIMAGE, &CImpressionistPaintDoc::OnUpdateImpressionistSaveimage)
	ON_COMMAND(ID_IMPRESSIONIST_SAVEIMAGE, &CImpressionistPaintDoc::OnImpressionistSaveimage)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_OVALBRUSH, &CImpressionistPaintDoc::OnUpdateBrushOvalbrush)
	ON_COMMAND(ID_BRUSH_OVALBRUSH, &CImpressionistPaintDoc::OnBrushOvalbrush)
	ON_COMMAND(ID_BRUSH_BRUSHSIZE, &CImpressionistPaintDoc::OnBrushBrushsize)
	ON_COMMAND(ID_BRUSH_BACKWARDSLANTEDBRUSH, &CImpressionistPaintDoc::OnBrushBackwardslantedbrush)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_BACKWARDSLANTEDBRUSH, &CImpressionistPaintDoc::OnUpdateBrushBackwardslantedbrush)
	ON_COMMAND(ID_BRUSH_BACKWARDSLANTEDRAIN, &CImpressionistPaintDoc::OnBrushBackwardslantedrain)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_BACKWARDSLANTEDRAIN, &CImpressionistPaintDoc::OnUpdateBrushBackwardslantedrain)
	ON_COMMAND(ID_BRUSH_POINTBRUSH, &CImpressionistPaintDoc::OnBrushPointbrush)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_POINTBRUSH, &CImpressionistPaintDoc::OnUpdateBrushPointbrush)
	ON_COMMAND(ID_BRUSH_BACKWARDSLANTEDDOTTED, &CImpressionistPaintDoc::OnBrushBackwardslanteddotted)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_BACKWARDSLANTEDDOTTED, &CImpressionistPaintDoc::OnUpdateBrushBackwardslanteddotted)
	ON_COMMAND(ID_BRUSH_CIRCLEBRUSH, &CImpressionistPaintDoc::OnBrushCirclebrush)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_CIRCLEBRUSH, &CImpressionistPaintDoc::OnUpdateBrushCirclebrush)
	ON_COMMAND(ID_BRUSH_SQUAREBRUSH, &CImpressionistPaintDoc::OnBrushSquarebrush)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_SQUAREBRUSH, &CImpressionistPaintDoc::OnUpdateBrushSquarebrush)
	ON_COMMAND(ID_BRUSH_WATERDROP, &CImpressionistPaintDoc::OnBrushWaterdrop)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_WATERDROP, &CImpressionistPaintDoc::OnUpdateBrushWaterdrop)
	ON_COMMAND(ID_BRUSH_TEXTUREBRUSH, &CImpressionistPaintDoc::OnBrushTexturebrush)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_TEXTUREBRUSH, &CImpressionistPaintDoc::OnUpdateBrushTexturebrush)
	ON_COMMAND(ID_BRUSH_EMBOSSBRUSH, &CImpressionistPaintDoc::OnBrushEmbossbrush)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_EMBOSSBRUSH, &CImpressionistPaintDoc::OnUpdateBrushEmbossbrush)
	ON_COMMAND(ID_BRUSH_TEXTUREBRUSH32800, &CImpressionistPaintDoc::OnBrushTexturebrush32800)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_TEXTUREBRUSH32800, &CImpressionistPaintDoc::OnUpdateBrushTexturebrush32800)
	ON_COMMAND(ID_BRUSH_SLANTEDLINE, &CImpressionistPaintDoc::OnBrushSlantedline)
	ON_UPDATE_COMMAND_UI(ID_BRUSH_SLANTEDLINE, &CImpressionistPaintDoc::OnUpdateBrushSlantedline)
	ON_COMMAND(ID_IMPRESSIONIST_CLEARCANVAS, &CImpressionistPaintDoc::OnImpressionistClearcanvas)
	ON_UPDATE_COMMAND_UI(ID_IMPRESSIONIST_CLEARCANVAS, &CImpressionistPaintDoc::OnUpdateImpressionistClearcanvas)
	ON_COMMAND(ID_IMPRESSIONIST_BATCH, &CImpressionistPaintDoc::OnImpressionistBatch)
	ON_COMMAND(ID_IMPRESSIONIST_EXECUTE, &CImpressionistPaintDoc::OnImpressionistExecute)
	ON_UPDATE_COMMAND_UI(ID_IMPRESSIONIST_EXECUTE, &CImpressionistPaintDoc::OnUpdateImpressionistExecute)
	ON_COMMAND(ID_IMPRESSIONIST_BATCHRUN, &CImpressionistPaintDoc::OnImpressionistBatchrun)
	ON_UPDATE_COMMAND_UI(ID_IMPRESSIONIST_BATCHRUN, &CImpressionistPaintDoc::OnUpdateImpressionistBatchrun)
END_MESSAGE_MAP()


// CImpressionistPaintDoc construction/destruction

CImpressionistPaintDoc::CImpressionistPaintDoc()
: m_bRedrawCanvas(FALSE)
{
	// TODO: add one-time construction code here
	gDisplay.SetDoc(this);

	m_bIsCurrentDisplayed=true;

	m_pBrush=&(m_generator.m_brushes.m_pbOval);

	m_configuration.Load(_T("ImpressionistPaintConfig.xml"));

	m_generator.Reset(&m_configuration);
}

CImpressionistPaintDoc::~CImpressionistPaintDoc()
{
}

BOOL CImpressionistPaintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CImpressionistPaintDoc serialization

void CImpressionistPaintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CImpressionistPaintDoc diagnostics

#ifdef _DEBUG
void CImpressionistPaintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImpressionistPaintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImpressionistPaintDoc commands

void CImpressionistPaintDoc::Display(CDC* pDC, const CRect& drRect)
{

	if(!m_imgMemory.IsNull())
	{
		if(m_bIsCurrentDisplayed)
		{
			m_imgMemory.DisplayCurrent(pDC, drRect);
		}
		else
		{
			m_imgMemory.DisplaySource(pDC, drRect);
		}
	}
}

bool CImpressionistPaintDoc::LoadSourceImage(LPCTSTR pFileName)
{
	if(!m_imgMemory.Load(pFileName))
	{
		return false;
	}
	m_generator.Reset(&m_configuration);

	return true;
}

void CImpressionistPaintDoc::OnLeftMouseDragged(const CPoint& ptStart, const CPoint& ptEnd, const CRect& drRect)
{
	if(!m_imgMemory.IsNull())
	{
		if(m_bIsCurrentDisplayed)
		{
			m_imgMemory.PaintCurrent(ptStart, ptEnd, drRect, m_pBrush);
		}
	}
}

void CImpressionistPaintDoc::OnUpdateImpressionistSaveimage(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_imgMemory.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CImpressionistPaintDoc::OnImpressionistSaveimage()
{
	// TODO: Add your command handler code here
	CFileDialog fDialog(FALSE,
		_T("bmp"),
		_T("result"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Bitmap File (*.bmp)|*.bmp|Jpeg File (*.jpg)|*.jpg|Gif File (*.gif)|*.gif|PNG File (*.png)|*.png|Tiff File (*.tif)|*.tif|"),
		NULL);

	if(fDialog.DoModal() != IDOK)
	{
		return;
	}

	m_imgMemory.SaveCurrent(fDialog.GetPathName());
}


void CImpressionistPaintDoc::OnUpdateBrushOvalbrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbOval))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushOvalbrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbOval);
}

void CImpressionistPaintDoc::OnBrushBrushsize()
{
	// TODO: Add your command handler code here
	CDialogSetBrushSize dlg;
	dlg.m_pBrush=m_pBrush;

	if(dlg.DoModal() == IDOK)
	{
	}
}

void CImpressionistPaintDoc::OnBrushBackwardslantedbrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbBSlanted);
}

void CImpressionistPaintDoc::OnUpdateBrushBackwardslantedbrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbBSlanted))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushBackwardslantedrain()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbBSlantedRain);
}

void CImpressionistPaintDoc::OnUpdateBrushBackwardslantedrain(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbBSlantedRain))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushPointbrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbPoint);
}

void CImpressionistPaintDoc::OnUpdateBrushPointbrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbPoint))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushBackwardslanteddotted()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbBSlantedDotted);
}

void CImpressionistPaintDoc::OnUpdateBrushBackwardslanteddotted(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbBSlantedDotted))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnImageDisplaycanvas()
{
	// TODO: Add your command handler code here
	m_bIsCurrentDisplayed=true;
}

void CImpressionistPaintDoc::OnUpdateImageDisplaycanvas(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_imgMemory.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}

	if(m_bIsCurrentDisplayed)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnImageDisplaysource()
{
	// TODO: Add your command handler code here
	m_bIsCurrentDisplayed=false;
}

void CImpressionistPaintDoc::OnUpdateImageDisplaysource(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_imgMemory.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}

	if(m_bIsCurrentDisplayed)
	{
		pCmdUI->SetCheck(FALSE);
	}
	else
	{
		pCmdUI->SetCheck(TRUE);
	}
}

void CImpressionistPaintDoc::OnBrushCirclebrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbAdvCircle);
}

void CImpressionistPaintDoc::OnUpdateBrushCirclebrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbAdvCircle))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushSquarebrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbAdvSquare);
}

void CImpressionistPaintDoc::OnUpdateBrushSquarebrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbAdvSquare))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushWaterdrop()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbAdvWaterdrop);
}

void CImpressionistPaintDoc::OnUpdateBrushWaterdrop(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbAdvWaterdrop))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushTexturebrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbTexture);
}

void CImpressionistPaintDoc::OnUpdateBrushTexturebrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbTexture))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushEmbossbrush()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbEmboss);
}

void CImpressionistPaintDoc::OnUpdateBrushEmbossbrush(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbEmboss))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushTexturebrush32800()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbAdvTexture);
}

void CImpressionistPaintDoc::OnUpdateBrushTexturebrush32800(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbAdvTexture))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnBrushSlantedline()
{
	// TODO: Add your command handler code here
	m_pBrush=&(m_generator.m_brushes.m_pbAdvSlanted);
}

void CImpressionistPaintDoc::OnUpdateBrushSlantedline(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_pBrush == &(m_generator.m_brushes.m_pbAdvSlanted))
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CImpressionistPaintDoc::OnImpressionistClearcanvas()
{
	// TODO: Add your command handler code here
	if(m_imgMemory.IsNull())
	{
		return;
	}
	else
	{
		m_imgMemory.ClearCanvas();
		gDisplay.InvalidateView(FALSE);
	}
}

void CImpressionistPaintDoc::OnUpdateImpressionistClearcanvas(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_imgMemory.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(m_bIsCurrentDisplayed)
		{
			pCmdUI->Enable(TRUE);
		}
		else
		{
			pCmdUI->Enable(FALSE);
		}
	}
}

void CImpressionistPaintDoc::OnImpressionistBatch()
{
	// TODO: Add your command handler code here
	CDlgIPConfig dlg;
	
	dlg.m_iStrokeCount=m_configuration.GetStrokeCount();
	dlg.m_iStrokesPerExecution=m_configuration.GetStrokesPerExecution();
	dlg.m_iStrokesPerRefresh=m_configuration.GetStrokesPerRefresh();
	dlg.m_iStrokeStepSize=m_configuration.GetStrokeStepSize();

	dlg.m_bRedraw=m_bRedrawCanvas;

	dlg.m_fBrushSize=m_configuration.GetBrushSize();

	dlg.m_pConfig=&m_configuration;

	if(dlg.DoModal() == IDOK)
	{
		m_bRedrawCanvas=dlg.m_bRedraw;

		m_configuration.SetStrokeCount(dlg.m_iStrokeCount);
		m_configuration.SetStrokesPerExecution(dlg.m_iStrokesPerExecution);
		m_configuration.SetStrokesPerRefresh(dlg.m_iStrokesPerRefresh);
		m_configuration.SetStrokeStepSize(dlg.m_iStrokeStepSize);

		m_configuration.SetBrushSize(dlg.m_fBrushSize);

		m_generator.Reset(&m_configuration);
		if(m_bRedrawCanvas)
		{
			m_imgMemory.ClearCanvas();
			gDisplay.InvalidateView(FALSE);
		}
	}
	dlg.m_pConfig=NULL;
}

void CImpressionistPaintDoc::OnImpressionistExecute()
{
	// TODO: Add your command handler code here
	m_generator.DispatchStrokes(&m_imgMemory, &m_configuration, m_pBrush);
}

void CImpressionistPaintDoc::OnUpdateImpressionistExecute(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_imgMemory.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(m_generator.IsNull())
		{
			pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
	}
	
}

void CImpressionistPaintDoc::OnImpressionistBatchrun()
{
	// TODO: Add your command handler code here
	if(m_generator.IsNull())
	{
		m_generator.Reset(&m_configuration);
		m_generator.DispatchStrokes(&m_imgMemory, &m_configuration, m_pBrush);
	}
}

void CImpressionistPaintDoc::OnUpdateImpressionistBatchrun(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(m_imgMemory.IsNull())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		if(m_generator.IsNull())
		{
			pCmdUI->Enable(TRUE);
		}
		else
		{
			pCmdUI->Enable(FALSE);
		}
	}
}
