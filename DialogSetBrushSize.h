#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "PaintBrush.h"


// CDialogSetBrushSize dialog

class CDialogSetBrushSize : public CDialog
{
	DECLARE_DYNAMIC(CDialogSetBrushSize)

public:
	CDialogSetBrushSize(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogSetBrushSize();

// Dialog Data
	enum { IDD = IDD_DLGBRUSHSIZE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_sldBrushSize;
	PaintBrush* m_pBrush;
	virtual BOOL OnInitDialog();
//	virtual INT_PTR DoModal();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	CEdit m_txtBrushSize;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedOk();
	CStatic m_lblFrame;
};
