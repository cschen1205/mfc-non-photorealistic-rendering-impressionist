#pragma once
#include "paintbrush.h"

class PaintBrushBSlantedDotted :
	public PaintBrush
{
public:
	PaintBrushBSlantedDotted(void);
	virtual ~PaintBrushBSlantedDotted(void);

	public:
	virtual int GetSteps() const { return 5; }
	virtual CString GetID() const { return _T("Backward Slanted Dotted Brush"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage *pCanvas, CDC* pDC);

protected:
	virtual void NormalPaint(int x, int y, COLORREF color, CDC* pDC);
};
