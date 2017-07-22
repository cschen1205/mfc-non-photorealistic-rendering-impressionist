#pragma once
#include "paintbrush.h"

class PaintBrushAdvSquare :
	public PaintBrush
{
public:
	PaintBrushAdvSquare(void);
	virtual ~PaintBrushAdvSquare(void);

public:
	virtual CString GetID() const { return _T("Square Brush (Advanced)"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);
};
