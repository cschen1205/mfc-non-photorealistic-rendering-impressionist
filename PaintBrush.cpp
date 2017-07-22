#include "StdAfx.h"
#include "PaintBrush.h"
#include <cstdlib>
#include <cmath>
#include "MemoryImage.h"

PaintBrush::PaintBrush(void)
: m_bsize(5)
, m_bsize2(2)
, m_jsize(3)
, m_jsize2(1)
, m_size(1)
, m_advLen(6)
{
}

PaintBrush::~PaintBrush(void)
{
}

int PaintBrush::Jitter(int val) const
{
	return val + (rand() % m_jsize) - m_jsize2;
}

void PaintBrush::SetSize(double size)
{
	m_size=size;
	double diam =4.0 * pow(1.41, size);
	m_bsize2=static_cast<int>(diam / 2.0);
	m_bsize= 2 * m_bsize2 + 1;
	m_advLen=m_bsize+2;
	m_jsize2=static_cast<int>(2.0 * diam / 2.0);
	m_jsize= 2 * m_jsize2 + 1;

	AdditionalResize();
}

void PaintBrush::NormalPaint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	int lx=ptStart.x;
	int ly=ptStart.y;

	int cx=ptEnd.x;
	int cy=ptEnd.y;

	int nsteps=this->GetSteps();

	for(int i=0; i<nsteps; i++)
	{
		int px=(lx * (nsteps - i) + cx * i) / nsteps;
		int py=(ly * (nsteps - i) + cy * i) / nsteps;
		int x=this->Jitter(px);
		int y=this->Jitter(py);

		COLORREF color=pCanvas->SampleColor(x, y);

		NormalPaint(x, y, color, pDC);
	}
}

