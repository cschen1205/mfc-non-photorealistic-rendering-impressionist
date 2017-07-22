#pragma once
#include "paintbrush.h"

class PaintBrushAdvCircle :
	public PaintBrush
{
public:
	PaintBrushAdvCircle(void);
	virtual ~PaintBrushAdvCircle(void);

public:
	virtual CString GetID() const { return _T("Circle Brush (Advanced)"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage*pCanvas, CDC* pDC);
};
