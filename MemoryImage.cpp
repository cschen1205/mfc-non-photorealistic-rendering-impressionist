#include "StdAfx.h"
#include "MemoryImage.h"
#include <comdef.h>
#include <vector>

MemoryImage::MemoryImage(void)
{
}

MemoryImage::~MemoryImage(void)
{
}

int MemoryImage::GetWidth() const
{
	if(m_imgCurrent.IsNull())
	{
		return -1;
	}

	return m_imgCurrent.GetWidth();
}

int MemoryImage::GetHeight() const
{
	if(m_imgCurrent.IsNull())
	{
		return -1;
	}

	return m_imgCurrent.GetHeight();
}

bool MemoryImage::Load(LPCTSTR pFileName)
{
	m_imgSource.Destroy();

	HRESULT hResult=m_imgSource.Load(pFileName);
	if(FAILED(hResult))
	{
		CString fmt;
		fmt.Format(_T("Failed to load Image:\n %x - %s"), hResult, _com_error(hResult).ErrorMessage());
		return false;
	}

	m_imgCurrent.Destroy();
	if(m_imgCurrent.Create(m_imgSource.GetWidth(), m_imgSource.GetHeight(), m_imgSource.GetBPP())==FALSE)
	{
		CString fmt;
		fmt.Format(_T("Failed to Create Current Image"));
		AfxMessageBox(fmt, MB_OK);
		return false;
	}

	ClearCanvas();

	return true;

}

void MemoryImage::DisplayCurrent(CDC* pDC, const CRect& drRect)
{
	if(m_imgCurrent.IsNull())
	{
		return;
	}

	UpdateBuffer(drRect);

	CDC* pBufferDC=CDC::FromHandle(m_imgBuffer.GetDC());

	PaintBufferBackground(pBufferDC, drRect);

	CRect dRect;
	GetImgAspRect(drRect, dRect);

	m_imgCurrent.StretchBlt(pBufferDC->m_hDC, dRect.left, dRect.top, dRect.Width(), dRect.Height(), SRCCOPY);

	m_imgBuffer.ReleaseDC();

	m_imgBuffer.BitBlt(pDC->m_hDC, drRect.left, drRect.top, SRCCOPY);
}

void MemoryImage::DisplaySource(CDC* pDC, const CRect& drRect)
{
	if(m_imgSource.IsNull())
	{
		return;
	}

	UpdateBuffer(drRect);

	CDC* pBufferDC=CDC::FromHandle(m_imgBuffer.GetDC());

	PaintBufferBackground(pBufferDC, drRect);

	CRect dRect;
	GetImgAspRect(drRect, dRect);

	m_imgSource.StretchBlt(pBufferDC->m_hDC, dRect.left, dRect.top, dRect.Width(), dRect.Height(), SRCCOPY);

	m_imgBuffer.ReleaseDC();

	m_imgBuffer.BitBlt(pDC->m_hDC, drRect.left, drRect.top, SRCCOPY);
}

void MemoryImage::PaintCurrent(const CPoint& ptStart, const CPoint& ptEnd, const CRect& drRect, PaintBrush* pBrush)
{

	int iImgWidth=m_imgCurrent.GetWidth();
	int iImgHeight=m_imgCurrent.GetHeight();

	int iRectWidth=drRect.Width();
	int iRectHeight=drRect.Height();

	double aspect_img=(double)iImgWidth / (double)iImgHeight;
	double aspect_dr=(double)iRectWidth / (double)iRectHeight;

	int drWidthRed=0;
	int drHeightRed=0;
	if(aspect_img < aspect_dr)
	{
		drWidthRed=static_cast<int>((iRectWidth - iRectHeight * aspect_img) / 2.0);
		iRectWidth=static_cast<int>(iRectHeight * aspect_img);
	}
	else if(aspect_img > aspect_dr)
	{
		drHeightRed=static_cast<int>((iRectHeight - iRectWidth / aspect_img)/2.0);
		iRectHeight=static_cast<int>(iRectWidth / aspect_img);
	}

	int cx=(ptEnd.x - drWidthRed)  * iImgWidth / iRectWidth;
	int cy=(ptEnd.y - drHeightRed) * iImgHeight / iRectHeight;

	int lx=(ptStart.x - drWidthRed)  * iImgWidth / iRectWidth;
	int ly=(ptStart.y - drHeightRed) * iImgHeight / iRectHeight;

	if(cx < 0 || cx > iImgWidth)
	{
		return;
	}

	if(lx < 0 || lx > iImgWidth)
	{
		return;
	}

	if(cy < 0 || cy > iImgHeight)
	{
		return;
	}

	if(ly < 0 || ly > iImgHeight)
	{
		return;
	}

	

	CDC* pDC=CDC::FromHandle(m_imgCurrent.GetDC());

	pBrush->Paint(CPoint(lx, ly), CPoint(cx, cy), this, pDC);

	m_imgCurrent.ReleaseDC();

}

bool MemoryImage::IsNull() const
{
	if(m_imgSource.IsNull())
	{
		return true;
	}

	return m_imgCurrent.IsNull();
}



COLORREF MemoryImage::SampleColor(int x, int y) const
{
	if(x < 0)
	{
		x=0;
	}
	if(x >= m_imgSource.GetWidth())
	{
		x=m_imgSource.GetWidth() -1;
	}
	if(y < 0)
	{
		y=0;
	}
	if(y >= m_imgSource.GetHeight())
	{
		y=m_imgSource.GetHeight() - 1;
	}

	return m_imgSource.GetPixel(x, y);
}


bool MemoryImage::SaveCurrent(LPCTSTR pFileName)
{
	if(FAILED(m_imgCurrent.Save(pFileName)))
	{
		return false;
	}

	return true;
}

void MemoryImage::GetImgAspRect(const CRect& drRect, CRect& dRect)
{
		int iImgWidth=m_imgCurrent.GetWidth();
	int iImgHeight=m_imgCurrent.GetHeight();

	int iRectWidth=drRect.Width();
	int iRectHeight=drRect.Height();

	double aspect_img=(double)iImgWidth / (double)iImgHeight;
	double aspect_dr=(double)iRectWidth / (double)iRectHeight;

	int drWidthRed=0;
	int drHeightRed=0;
	if(aspect_img < aspect_dr)
	{
		drWidthRed=static_cast<int>((iRectWidth - iRectHeight * aspect_img) / 2.0);
		iRectWidth=static_cast<int>(iRectHeight * aspect_img);
	}
	else if(aspect_img > aspect_dr)
	{
		drHeightRed=static_cast<int>((iRectHeight - iRectWidth / aspect_img)/2.0);
		iRectHeight=static_cast<int>(iRectWidth / aspect_img);
	}

	dRect.left=drWidthRed;
	dRect.top=drHeightRed;
	dRect.bottom=dRect.top+iRectHeight;
	dRect.right=dRect.left+iRectWidth;
}

void MemoryImage::TranslateCanvasPosition2ViewPosition(const CRect& rtClientRect, const CPoint& ptCanvasPosition, CPoint& ptViewPosition)
{
	ASSERT(!m_imgSource.IsNull());

	CRect rtCanvasRect;
	GetImgAspRect(rtClientRect, rtCanvasRect);

	ptViewPosition.x = static_cast<int>((float)ptCanvasPosition.x / (float)m_imgSource.GetWidth() * (float)rtCanvasRect.Width() + rtCanvasRect.left);
	ptViewPosition.y = static_cast<int>((float)ptCanvasPosition.y / (float)m_imgSource.GetHeight() * (float)rtCanvasRect.Height() + rtCanvasRect.top);
}

void MemoryImage::TranslateViewPosition2CanvasPosition(const CRect& rtClientRect, CPoint& ptCanvasPosition, const CPoint& ptViewPosition)
{
	ASSERT(!m_imgSource.IsNull());

	CRect rtCanvasRect;
	GetImgAspRect(rtClientRect, rtCanvasRect);

	ptCanvasPosition.x = static_cast<int>((float)(ptViewPosition.x - rtCanvasRect.left) / (float)rtCanvasRect.Width() * (float)m_imgSource.GetWidth());
	ptCanvasPosition.y = static_cast<int>((float)(ptViewPosition.y - rtCanvasRect.top) / (float)rtCanvasRect.Height() * (float)m_imgSource.GetHeight());
}

int MemoryImage::GetLuminance(COLORREF color)
{
	return static_cast<int>(0.3f * GetRValue(color) + 0.59f * GetGValue(color) + 0.11f * GetBValue(color));
}

CPoint MemoryImage::GetDirection(int x, int y)
{
	int height=m_imgSource.GetHeight();
	int width=m_imgSource.GetWidth();

	std::vector<std::vector<int> > pixel;
	for(int i=0; i<3; i++)
	{
		std::vector<int> row;
		for(int j=0; j<3; j++)
		{
			row.push_back(0);
		}
		pixel.push_back(row);
	}

	for(int i=0; i<pixel.size(); i++)
	{
		int yy=y+i-1;

		if(yy < 0)
		{
			continue;
		}
		else if(yy >= height)
		{
			break;
		}

		for(int j=0; j<pixel[i].size(); j++)
		{
			int xx=x+j-1;
			if(xx < 0)
			{
				continue;
			}
			else if(xx >= width)
			{
				break;
			}

			pixel[i][j]=GetLuminance(SampleColor(xx, yy));
		}
	}

	int vx= - pixel[0][0] + pixel[0][2]
			- 2 * pixel[1][0] + 2 * pixel[1][2]
			- pixel[2][0] + pixel[2][2];
	int vy= - pixel[0][0] + pixel[2][0]
			- 2 * pixel[0][1] + 2 * pixel[2][1]
			- pixel[0][2] + pixel[2][2];

	return CPoint(vx, vy);
}


void MemoryImage::ClearCanvas(void)
{
	CDC* pDC=CDC::FromHandle(m_imgCurrent.GetDC());

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));

	CPen* pOldPen=pDC->SelectObject(&pen);
	CBrush* pOldBrush=pDC->SelectObject(&brush);

	pDC->Rectangle(0, 0, m_imgCurrent.GetWidth(), m_imgCurrent.GetHeight());

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

	pen.DeleteObject();
	brush.DeleteObject();

	m_imgCurrent.ReleaseDC();
}

void MemoryImage::PaintBufferBackground(CDC* pDC, const CRect& drRect)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(125, 125, 125));

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(125, 125, 125));

	CBrush* pOldBrush=pDC->SelectObject(&brush);
	CPen* pOldPen=pDC->SelectObject(&pen);

	pDC->Rectangle(&drRect);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	pen.DeleteObject();
	brush.DeleteObject();
}

void MemoryImage::UpdateBuffer(const CRect& drRect)
{
	if(m_imgBuffer.IsNull())
	{
		m_imgBuffer.Create(drRect.Width(), drRect.Height(), m_imgSource.GetBPP());
	}
	else if(m_imgBuffer.GetWidth() != drRect.Width() || m_imgBuffer.GetHeight() != drRect.Height())
	{
		m_imgBuffer.Destroy();
		m_imgBuffer.Create(drRect.Width(), drRect.Height(), m_imgSource.GetBPP());
	}
}
