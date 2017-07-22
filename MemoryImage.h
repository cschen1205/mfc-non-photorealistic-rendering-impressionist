#pragma once
#include "afx.h"

#include <vector>
#include "PixelData.h"
#include "PaintBrush.h"

class MemoryImage :
	public CObject
{
public:
	MemoryImage(void);
	virtual ~MemoryImage(void);

public:
	bool Load(LPCTSTR pFileName);
	void DisplayCurrent(CDC* pDC, const CRect& drRect);
	void DisplaySource(CDC* pDC, const CRect& drRect);
	bool IsNull() const;

public:
	void PaintCurrent(const CPoint& ptStart, const CPoint& ptEnd, const CRect& drRect, PaintBrush* pBrush);
	void TranslateCanvasPosition2ViewPosition(const CRect& rtClientRect, const CPoint& ptCanvasPosition, CPoint& ptViewPosition);
	void TranslateViewPosition2CanvasPosition(const CRect& rtClientRect, CPoint& ptCanvasPosition, const CPoint& ptViewPosition);

public:
	COLORREF SampleColor(int x, int y) const;
	CPoint GetDirection(int x, int y);

public:
	int GetWidth() const;
	int GetHeight() const;

protected:
	CImage m_imgSource;
	CImage m_imgCurrent;
	CImage m_imgBuffer;

public:
	bool SaveCurrent(LPCTSTR pFileName);
protected:
	void GetImgAspRect(const CRect& rtSrc, CRect& rtDest);
	int GetLuminance(COLORREF color);
public:
	void ClearCanvas(void);
protected:
	void PaintBufferBackground(CDC* pDC, const CRect& drRect);
	void UpdateBuffer(const CRect& drRect);
};
