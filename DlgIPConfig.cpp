// DlgIPConfig.cpp : implementation file
//

#include "stdafx.h"
#include "ImpressionistPaint.h"
#include "DlgIPConfig.h"
#include "PaintConfiguration.h"

// CDlgIPConfig dialog

IMPLEMENT_DYNAMIC(CDlgIPConfig, CDialog)

CDlgIPConfig::CDlgIPConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPConfig::IDD, pParent)
	, m_fBrushSize(0)
	, m_iStrokeStepSize(0)
	, m_iStrokeCount(0)
	, m_iStrokesPerExecution(0)
	, m_iStrokesPerRefresh(0)
	, m_bRedraw(FALSE)
	, m_pConfig(NULL)
{

}

CDlgIPConfig::~CDlgIPConfig()
{
}

void CDlgIPConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BRUSHSIZE, m_fBrushSize);
	DDV_MinMaxFloat(pDX, m_fBrushSize, 0.01f, 1000);
	DDX_Text(pDX, IDC_EDIT_STROKESTEPSIZE, m_iStrokeStepSize);
	DDV_MinMaxInt(pDX, m_iStrokeStepSize, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_STROKECOUNT, m_iStrokeCount);
	DDV_MinMaxInt(pDX, m_iStrokeCount, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_STROKESPEREXECUTION, m_iStrokesPerExecution);
	DDV_MinMaxInt(pDX, m_iStrokesPerExecution, 1, 1000000);
	DDX_Text(pDX, IDC_EDIT_STROKESPERREFRESH, m_iStrokesPerRefresh);
	DDV_MinMaxInt(pDX, m_iStrokesPerRefresh, 1, 1000000);
	DDX_Check(pDX, IDC_CHECK_REDRAW, m_bRedraw);
}


BEGIN_MESSAGE_MAP(CDlgIPConfig, CDialog)
	
END_MESSAGE_MAP()


