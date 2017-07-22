#include "StdAfx.h"
#include "PaintBrushAdvCircle.h"
#include "MemoryImage.h"
#include <cmath>

PaintBrushAdvCircle::PaintBrushAdvCircle(void)
{
}

PaintBrushAdvCircle::~PaintBrushAdvCircle(void)
{
}

void PaintBrushAdvCircle::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage*pCanvas, CDC* pDC)
{
	int x=static_cast<int>((ptStart.x+ptEnd.x) / 2.0);
	int y=static_cast<int>((ptStart.y+ptEnd.y) / 2.0);
	COLORREF color=pCanvas->SampleColor(x, y);

	CPoint dir=pCanvas->GetDirection(x, y);

	float vx = - static_cast<float>(dir.y) / 255.0f;
	float vy = static_cast<float>(dir.x) / 255.0f;

	float l= sqrt(vx * vx + vy * vy);

	vx /= l;
	vy /= l;

	int vxl=static_cast<int>(vx * m_advLen);
	int vyl=static_cast<int>(vy * m_advLen);
	int vxb=static_cast<int>(vx * m_bsize / 2);
	int vyb=static_cast<int>(vy * m_bsize / 2);

	int sx = x - vxl;
	int sy = y - vyl;
	int ex = x + vxl;
	int ey = y + vyl;

	CBrush pBrush;
	pBrush.CreateSolidBrush(color);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, color);

	CBrush* pOldBrush=pDC->SelectObject(&pBrush);
	CPen* pOldPen=pDC->SelectObject(&pen);

	pDC->Ellipse(sx-m_bsize2, sy-m_bsize2, sx+m_bsize2, sy+m_bsize2);
	pDC->Ellipse(ex-m_bsize2, ey-m_bsize2, ex+m_bsize2, ey+m_bsize2);

	pDC->MoveTo(sx - vyb, sy + vxb);
	pDC->LineTo(ex - vyb, ey + vxb);

	pDC->MoveTo(sx+vyb, sy - vxb);
	pDC->LineTo(ex + vyb, ey - vxb);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
	pBrush.DeleteObject();
}

