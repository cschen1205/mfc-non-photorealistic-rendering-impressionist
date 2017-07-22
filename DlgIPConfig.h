#pragma once
#include "afxwin.h"

class PaintConfiguration;

// CDlgIPConfig dialog

class CDlgIPConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgIPConfig)

public:
	CDlgIPConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgIPConfig();

// Dialog Data
	enum { IDD = IDD_DLGIPCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_fBrushSize;
	int m_iStrokeStepSize;
	int m_iStrokeCount;
	int m_iStrokesPerExecution;
	int m_iStrokesPerRefresh;
	BOOL m_bRedraw;
	PaintConfiguration* m_pConfig;
};
