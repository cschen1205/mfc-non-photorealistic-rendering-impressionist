#include "StdAfx.h"
#include "PaintBrushTexture.h"
#include <comdef.h>
#include "MemoryImage.h"

PaintBrushTexture::PaintBrushTexture(void) : m_cbsize(-1)
{
	HRESULT hResult=m_imgTexture.Load(_T("brush_texture.bmp"));
	if(FAILED(hResult))
	{
		CString fmt;
		fmt.Format(_T("Failed to load texture: \n%x - %s"), hResult, _com_error(hResult));
		AfxMessageBox(fmt, MB_OK);
		return;
	}

	AdditionalResize();
}

PaintBrushTexture::~PaintBrushTexture(void)
{

}

void PaintBrushTexture::AdditionalResize()
{
	ASSERT(!m_imgTexture.IsNull());

	if(!m_pixels.empty() && m_bsize == m_cbsize)
	{
		return;
	}

	m_pixels.clear();

	double aspect=(double)m_imgTexture.GetWidth() / (double)m_imgTexture.GetHeight();

	int bwidth=m_bsize;
	int bheight=static_cast<int>(m_bsize * aspect);

	if(bheight < 1)
	{
		bheight=1;
	}

	CImage imgBuffer;
	imgBuffer.Create(bwidth, bheight, m_imgTexture.GetBPP());

	CDC* pDC=CDC::FromHandle(imgBuffer.GetDC());

	m_imgTexture.StretchBlt(pDC->m_hDC, 0, 0, bwidth, bheight, SRCCOPY);

	imgBuffer.ReleaseDC();

	for(int x=0; x < bwidth; x++)
	{
		for(int y=0; y < bheight; y++)
		{
			COLORREF color=imgBuffer.GetPixel(x, y);
			if(color != 0x000000)
			{
				m_pixels.push_back(std::make_pair<int, int>(x, y));
			}
		}
	}

	m_tCenter.x=bwidth / 2;
	m_tCenter.y=bheight / 2;

	imgBuffer.Destroy();

	m_cbsize=m_bsize;
}

void PaintBrushTexture::Paint(CPoint &ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	ASSERT(!pCanvas->IsNull());

	int x=static_cast<int>((ptStart.x + ptEnd.x) / 2.0);
	int y=static_cast<int>((ptStart.y + ptEnd.y) / 2.0);

	///*
	x=Jitter(x);
	y=Jitter(y);
	//*/

	COLORREF color=pCanvas->SampleColor(x, y);

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

		COLORREF color=pCanvas->SampleColor(x, y);

		std::list<std::pair<int, int> >::iterator pos;
		for(pos=m_pixels.begin(); pos!=m_pixels.end(); ++pos)
		{
			int pxx=pos->first;
			int pyy=pos->second;

			int xx=x+pxx-m_tCenter.x;
			int yy=y+pyy-m_tCenter.y;

			if(xx < 0 || xx >= canvas_width || yy < 0 || yy >= canvas_height)
			{
				continue;
			}

			pDC->SetPixel(xx, yy, color);
		}
	}

	

}
