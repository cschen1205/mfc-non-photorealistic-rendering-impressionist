#pragma once
#include "paintbrush.h"

class PaintBrushAdvWaterdrop :
	public PaintBrush
{
public:
	PaintBrushAdvWaterdrop(void);
	virtual ~PaintBrushAdvWaterdrop(void);

public:
	virtual CString GetID() const { return _T("Waterdrop Brush (Advanced)"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);
};
