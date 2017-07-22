#include "StdAfx.h"
#include "PaintBrushBSlanted.h"
#include "MemoryImage.h"

PaintBrushBSlanted::PaintBrushBSlanted(void)
{
}

PaintBrushBSlanted::~PaintBrushBSlanted(void)
{
}

void PaintBrushBSlanted::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage*pCanvas, CDC* pDC)
{
	PaintBrush::NormalPaint(ptStart, ptEnd, pCanvas, pDC);
}

void PaintBrushBSlanted::NormalPaint(int x, int y, COLORREF color, CDC* pDC)
{
	CPoint ptStart(x-m_bsize2, y+m_bsize2);
	CPoint ptEnd(x+m_bsize2, y-m_bsize2);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);

	CPen* pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}

