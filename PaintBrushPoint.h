#pragma once
#include "paintbrush.h"

class PaintBrushPoint :
	public PaintBrush
{
public:
	PaintBrushPoint(void);
	virtual ~PaintBrushPoint(void);

	public:
	virtual int GetSteps() const { return 10; }
	virtual CString GetID() const { return _T("Point Brush"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pImage, CDC* pDC);
	virtual void NormalPaint(int x, int y, COLORREF color, CDC* pDC);
};
