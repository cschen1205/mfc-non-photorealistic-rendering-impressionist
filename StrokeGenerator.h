#pragma once
#include "afx.h"
#include <list>
#include "BrushToolkit.h"

class Stroke;
class MemoryImage;
class PaintConfiguration;

class StrokeGenerator :
	public CObject
{
public:
	StrokeGenerator(void);
	~StrokeGenerator(void);
	
public:
	void DispatchStrokes(MemoryImage* pCanvas, PaintConfiguration*  pConfig, PaintBrush* pBrush=NULL);
	int GetRemainedStrokes() const { return m_iRemainedStrokes; }
	void SetRemainedStrokes(int iVal) { m_iRemainedStrokes=iVal; }
	int GetDeadStrokes() const { return m_iDeadStrokes; }

protected:
	int m_iRemainedStrokes;
	int m_iDeadStrokes;
public:
	void Reset(PaintConfiguration* pConfig);
	bool IsNull(void) const;

public:
	BrushToolkit m_brushes;

protected:
	PaintBrush* GetBrushByConfiguration(PaintConfiguration* pConfig);
};

