#pragma once
#include "paintbrush.h"

class PaintBrushAdvSlanted :
	public PaintBrush
{
public:
	PaintBrushAdvSlanted(void);
	virtual ~PaintBrushAdvSlanted(void);

public:
	virtual CString GetID() const { return _T("Slanted Line (Advanced)"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);
};
