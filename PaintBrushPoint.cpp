#include "StdAfx.h"
#include "PaintBrushPoint.h"
#include "MemoryImage.h"

PaintBrushPoint::PaintBrushPoint(void)
{
}

PaintBrushPoint::~PaintBrushPoint(void)
{
}

void PaintBrushPoint::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	PaintBrush::NormalPaint(ptStart, ptEnd, pCanvas, pDC);
}

void PaintBrushPoint::NormalPaint(int x, int y, COLORREF color, CDC* pDC)
{
	/*
	CBrush pBrush;
	pBrush.CreateSolidBrush(color);

	CBrush* pOldBrush=pDC->SelectObject(&pBrush);
	*/

	pDC->SetPixel(x, y, color);

	/*
	pDC->SelectObject(pOldBrush);

	pBrush.DeleteObject();
	*/
}

