#pragma once
#include "paintbrush.h"
#include <list>
#include <vector>

class PaintBrushTexture :
	public PaintBrush
{
public:
	PaintBrushTexture(void);
	virtual ~PaintBrushTexture(void);

public:
	virtual CString GetID() const { return _T("Texture Brush"); }

public:
	virtual void Paint(CPoint &ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);

private:
	virtual void AdditionalResize();

private:
	std::list<std::pair<int, int> > m_pixels;
	CImage m_imgTexture;
	int m_cbsize;
	CPoint m_tCenter;
};
