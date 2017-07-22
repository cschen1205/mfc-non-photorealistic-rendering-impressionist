#pragma once
#include "paintbrush.h"

class PaintBrushBSlantedRain :
	public PaintBrush
{
public:
	PaintBrushBSlantedRain(void);
	virtual ~PaintBrushBSlantedRain(void);

public:
	virtual int GetSteps() const { return 5; }
	virtual CString GetID() const { return _T("Backward Slanted Rain"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);

protected:
	virtual void NormalPaint(int x, int y, COLORREF color, CDC* pDC);
};
