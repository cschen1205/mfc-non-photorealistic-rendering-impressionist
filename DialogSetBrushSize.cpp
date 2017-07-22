// DialogSetBrushSize.cpp : implementation file
//

#include "stdafx.h"
#include "ImpressionistPaint.h"
#include "DialogSetBrushSize.h"


// CDialogSetBrushSize dialog

IMPLEMENT_DYNAMIC(CDialogSetBrushSize, CDialog)

CDialogSetBrushSize::CDialogSetBrushSize(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSetBrushSize::IDD, pParent)
	, m_pBrush(NULL)
{

}

CDialogSetBrushSize::~CDialogSetBrushSize()
{
}

void CDialogSetBrushSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDERBRUSHSIZE, m_sldBrushSize);
	DDX_Control(pDX, IDC_EDITBRUSHSIZE, m_txtBrushSize);
	DDX_Control(pDX, IDC_STATICFRAME, m_lblFrame);
}


BEGIN_MESSAGE_MAP(CDialogSetBrushSize, CDialog)
	ON_WM_ACTIVATE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &CDialogSetBrushSize::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialogSetBrushSize message handlers

BOOL CDialogSetBrushSize::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_sldBrushSize.SetRange(0, 1000);
	m_sldBrushSize.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

//INT_PTR CDialogSetBrushSize::DoModal()
//{
//	// TODO: Add your specialized code here and/or call the base class
//	
//
//	return CDialog::DoModal();
//}

void CDialogSetBrushSize::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	double dBrushSize=m_pBrush->GetSize();
	int pos=static_cast<int>((dBrushSize / 100.0) * 1000);
	m_sldBrushSize.SetPos(pos);

	CString fmt;
	fmt.Format(_T("%f"), dBrushSize);
	m_txtBrushSize.SetWindowTextW(fmt);

	m_lblFrame.SetWindowTextW(m_pBrush->GetID());
}

void CDialogSetBrushSize::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	int pos=m_sldBrushSize.GetPos();
	double dBrushSize=(double)pos / 1000.0 * 100.0;

	CString fmt;
	fmt.Format(_T("%f"), dBrushSize);
	m_txtBrushSize.SetWindowTextW(fmt);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDialogSetBrushSize::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	int pos=m_sldBrushSize.GetPos();
	if(pos == 0)
	{
		AfxMessageBox(_T("Brush Size cannot be zero"));
		return;
	}

	double dBrushSize=(double)pos / 1000.0 * 100.0;
	m_pBrush->SetSize(dBrushSize);

	OnOK();
}
