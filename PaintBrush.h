#pragma once
#include "afx.h"

class MemoryImage;

class PaintBrush :
	public CObject
{
public:
	PaintBrush(void);
	virtual ~PaintBrush(void);

public:
	virtual int GetSteps() const { return 5; }
	virtual CString GetID() const=0;

public:
	int GetBrushSize() const { return m_bsize; }
	int GetBrushSizeHalf() const { return m_bsize2; }
	int Jitter(int x) const;
	void SetSize(double size);
	double GetSize() const { return m_size; }

public:
	virtual void Paint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC)=0;

protected:
	void NormalPaint(CPoint& ptStart, CPoint& ptEnd, MemoryImage* pCanvas, CDC* pDC);
	virtual void NormalPaint(int x, int y, COLORREF color, CDC* pDC) { }

protected:
	virtual void AdditionalResize() { }

protected:
	int m_advLen;

protected:
	double m_size;

protected:
	int m_bsize;
	int m_bsize2;

	int m_jsize;
	int m_jsize2;
};
