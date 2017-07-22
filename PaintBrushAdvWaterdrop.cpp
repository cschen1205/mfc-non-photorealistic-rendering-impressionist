#include "StdAfx.h"
#include "PaintBrushAdvWaterdrop.h"
#include "MemoryImage.h"

PaintBrushAdvWaterdrop::PaintBrushAdvWaterdrop(void)
{
}

PaintBrushAdvWaterdrop::~PaintBrushAdvWaterdrop(void)
{
}

void PaintBrushAdvWaterdrop::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage*pCanvas, CDC* pDC)
{
	int x=static_cast<int>((ptStart.x+ptEnd.x) / 2.0);
	int y=static_cast<int>((ptStart.y+ptEnd.y) / 2.0);
	COLORREF color=pCanvas->SampleColor(x, y);

	CBrush pBrush;
	pBrush.CreateSolidBrush(color);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);

	CBrush* pOldBrush=pDC->SelectObject(&pBrush);
	CPen* pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(x, y - m_advLen / 2);
	pDC->LineTo(x - m_bsize2, y + m_advLen / 2);

	pDC->MoveTo(x, y - m_advLen / 2);
	pDC->LineTo(x + m_bsize2, y + m_advLen / 2);

	pDC->Ellipse(x - m_bsize2, y + m_advLen / 2 - m_bsize2, x + m_bsize2, y + m_advLen / 2 + m_bsize2);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
	pBrush.DeleteObject();
}
