#include "StdAfx.h"
#include "PaintBrushEmboss.h"
#include "MemoryImage.h"

PaintBrushEmboss::PaintBrushEmboss(void)
{
}

PaintBrushEmboss::~PaintBrushEmboss(void)
{
}

void PaintBrushEmboss::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	int canvas_width=pCanvas->GetWidth();
	int canvas_height=pCanvas->GetHeight();

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

		if(x < 0)
		{
			x=0;
		}
		else if(x >= canvas_width)
		{
			x=canvas_width-1;
		}

		if(y < 0)
		{
			y=0;
		}
		else if(y >= canvas_height)
		{
			y=canvas_height-1;
		}

		int x1=x-1;
		if(x1 < 0)
		{
			x1=0;
		}

		COLORREF color=pCanvas->SampleColor(x, y);
		COLORREF color1=pCanvas->SampleColor(x1, y);

		const int T=128;

		int r=GetRValue(color) - GetRValue(color1) + T;
		int g=GetGValue(color) - GetGValue(color1) + T;
		int b=GetBValue(color) - GetBValue(color1) + T;

		pDC->SetPixel(x, y, RGB(r, g, b));
	}
	

	


}
