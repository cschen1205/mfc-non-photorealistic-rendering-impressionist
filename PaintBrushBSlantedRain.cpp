#include "StdAfx.h"
#include "PaintBrushBSlantedRain.h"
#include "MemoryImage.h"

PaintBrushBSlantedRain::PaintBrushBSlantedRain(void)
{
}

PaintBrushBSlantedRain::~PaintBrushBSlantedRain(void)
{
}

void PaintBrushBSlantedRain::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	PaintBrush::NormalPaint(ptStart, ptEnd, pCanvas, pDC);
}

void PaintBrushBSlantedRain::NormalPaint(int x, int y, COLORREF color, CDC* pDC)
{
	int nmarks=1 + (m_bsize * m_bsize) / 200;

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);

	CPen* pOldPen=pDC->SelectObject(&pen);

	for(int m=0; m<nmarks; m++)
	{
		int rx=Jitter(x);
		int ry=Jitter(y);
		pDC->MoveTo(rx-1, ry+1);
		pDC->LineTo(rx+1, ry-1);
	}

	pDC->SelectObject(pOldPen);

	pen.DeleteObject();
}
