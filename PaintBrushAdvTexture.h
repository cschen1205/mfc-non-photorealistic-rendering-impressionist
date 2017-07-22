#pragma once
#include "paintbrush.h"
#include <vector>
#include <list>

class PaintBrushAdvTexture :
	public PaintBrush
{
public:
	PaintBrushAdvTexture(void);
	virtual ~PaintBrushAdvTexture(void);

public:
	virtual CString GetID() const { return _T("Texture Brush (Advanced)"); }

protected:
	virtual void AdditionalResize();

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);

protected:
	CImage m_imgTexture;
	std::list<std::pair<int, int> > m_pixels;
	int m_cbsize;
	CPoint m_tCenter;
};
