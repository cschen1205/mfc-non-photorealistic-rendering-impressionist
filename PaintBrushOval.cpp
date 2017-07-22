#include "StdAfx.h"
#include "PaintBrushOval.h"
#include <cmath>
#include "MemoryImage.h"

PaintBrushOval::PaintBrushOval(void)
{
}

PaintBrushOval::~PaintBrushOval(void)
{
}

void PaintBrushOval::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	PaintBrush::NormalPaint(ptStart, ptEnd, pCanvas, pDC);
}

void PaintBrushOval::NormalPaint(int x, int y, COLORREF color, CDC* pDC)
{
	CBrush pBrush;
	pBrush.CreateSolidBrush(color);

	CBrush* pOldBrush=pDC->SelectObject(&pBrush);
	CPen* pOldPen=(CPen*)pDC->SelectStockObject(NULL_PEN);

	pDC->Ellipse(x-m_bsize2, y-m_bsize2, x+m_bsize2, y+m_bsize2);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pBrush.DeleteObject();
}
