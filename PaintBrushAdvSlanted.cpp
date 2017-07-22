#include "StdAfx.h"
#include "PaintBrushAdvSlanted.h"
#include "MemoryImage.h"
#include <cmath>

PaintBrushAdvSlanted::PaintBrushAdvSlanted(void)
{
}

PaintBrushAdvSlanted::~PaintBrushAdvSlanted(void)
{
}

void PaintBrushAdvSlanted::Paint(CPoint &ptStart, CPoint &ptEnd, MemoryImage *pCanvas, CDC *pDC)
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

	int vxb[2];
	int vyb[2];

	vxb[0]=static_cast<int>(vx * m_bsize / 2);
	vyb[0]=static_cast<int>(vy * m_bsize / 2);

	vxb[1]=static_cast<int>(vx * m_bsize / 4);
	vyb[1]=static_cast<int>(vy * m_bsize / 4);

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

	for(int i=0; i<2; i++)
	{
		pDC->MoveTo(sx - vyb[i], sy + vxb[i]);
		pDC->LineTo(ex - vyb[i], ey + vxb[i]);

		pDC->MoveTo(sx+vyb[i], sy - vxb[i]);
		pDC->LineTo(ex + vyb[i], ey - vxb[i]);
	}
	pDC->MoveTo(sx, sy);
	pDC->LineTo(ex, ey);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
	pBrush.DeleteObject();
}