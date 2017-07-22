#pragma once
#include "paintbrush.h"

class PaintBrushEmboss :
	public PaintBrush
{
public:
	PaintBrushEmboss(void);
	virtual ~PaintBrushEmboss(void);

public:
	virtual int GetSteps() const { return 20; }
	virtual CString GetID() const { return _T("Emboss Brush"); }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);
};
