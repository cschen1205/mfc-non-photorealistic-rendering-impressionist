#pragma once
#include "paintbrush.h"

class PaintBrushOval :
	public PaintBrush
{
public:
	PaintBrushOval(void);
	virtual ~PaintBrushOval(void);

public:
	virtual int GetSteps() const { return 5; }
	virtual CString GetID() const { return _T("Oval Brush"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage*pCanvas, CDC* pDC);

public:
	virtual void NormalPaint(int x, int y, COLORREF color, CDC* pDC);
};
