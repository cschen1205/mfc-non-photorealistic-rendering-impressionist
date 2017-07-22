#include "StdAfx.h"
#include "PaintBrushAdvTexture.h"
#include <comdef.h>
#include "MemoryImage.h"
#include <cmath>

PaintBrushAdvTexture::PaintBrushAdvTexture(void) : m_cbsize(-1)
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

PaintBrushAdvTexture::~PaintBrushAdvTexture(void)
{
}


void PaintBrushAdvTexture::AdditionalResize()
{
	ASSERT(!m_imgTexture.IsNull());

	if(!m_pixels.empty() && m_bsize == m_cbsize)
	{
		return;
	}

	m_pixels.clear();

	double aspect=(double)m_imgTexture.GetWidth() / (double)m_imgTexture.GetHeight();

	int bwidth=m_bsize;
	int bheight=static_cast<int>(m_bsize / aspect);

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


void PaintBrushAdvTexture::Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)
{
	int x=static_cast<int>((ptStart.x+ptEnd.x) / 2.0);
	int y=static_cast<int>((ptStart.y+ptEnd.y) / 2.0);
	COLORREF color=pCanvas->SampleColor(x, y);

	CPoint dir=pCanvas->GetDirection(x, y);
	int canvas_width=pCanvas->GetWidth();
	int canvas_height=pCanvas->GetHeight();

	float vx = -static_cast<float>(dir.y) / 255.0f;
	float vy = static_cast<float>(dir.x) / 255.0f;

	float l= sqrt(vx * vx + vy * vy);

	float ang = acos(vx / l);

	std::list<std::pair<int, int> >::iterator pos;
	for(pos=m_pixels.begin(); pos!=m_pixels.end(); ++pos)
	{
		float pxx= static_cast<float>(pos->first - m_tCenter.x);
		float pyy= static_cast<float>(pos->second - m_tCenter.y);

		float pl= sqrt(pxx * pxx + pyy * pyy);

		float angl=acos(pxx / pl);

		float dangl=angl + ang;

		int xx=x + static_cast<int>(pl * cos(dangl));
		int yy=y + static_cast<int>(pl * sin(dangl));

		if(xx < 0 || xx >= canvas_width || yy < 0 || yy >= canvas_height)
		{
			continue;
		}

		pDC->SetPixel(xx, yy, color);
	}

	
}