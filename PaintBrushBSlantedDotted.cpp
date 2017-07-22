#include "StdAfx.h"
#include "PaintBrushBSlantedDotted.h"
#include <cstdlib>
#include "MemoryImage.h"

PaintBrushBSlantedDotted::PaintBrushBSlantedDotted(void)
{
}

PaintBrushBSlantedDotted::~PaintBrushBSlantedDotted(void)
{
}

void PaintBrushBSlantedDotted::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	PaintBrush::NormalPaint(ptStart, ptEnd, pCanvas, pDC);
}

void PaintBrushBSlantedDotted::NormalPaint(int x, int y, COLORREF color, CDC* pDC)
{
	/*
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);

	CPen* pOldPen=pDC->SelectObject(&pen);
	*/

	int nmarks=2 + m_bsize / 3;
	int px=x-m_bsize2;
	int py=y+m_bsize2;

	for(int m=0; m<nmarks; m++)
	{
		int del=(rand() % m_bsize);
		x=px + del;
		y=py - del;
		pDC->SetPixel(x, y, color);
	}

	/*
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	*/
}
