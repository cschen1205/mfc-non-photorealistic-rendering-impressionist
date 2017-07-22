#pragma once
#include "afx.h"

class PaintConfiguration :
	public CObject
{
public:
	PaintConfiguration(void);
	~PaintConfiguration(void);

public:
	bool Load(LPCTSTR pFilename);

public:
	int GetBrushType() const { return m_iBrushType; }
	float GetBrushSize() const { return m_fBrushSize; }
	int GetStrokeStepSize() const { return m_iStrokeStepSize; }
	int GetStrokeCount() const { return m_iStrokeCount; }
	int GetStrokesPerExecution() const { return m_iStrokesPerExecution; }
	int GetStrokesPerRefresh() const { return m_iStrokesPerRefresh; }

public:
	void SetBrushType(int iVal) { m_iBrushType=iVal; }
	void SetBrushSize(float fVal) { m_fBrushSize=fVal; }
	void SetStrokeStepSize(int iVal) { m_iStrokeStepSize=iVal; }
	void SetStrokeCount(int iVal) { m_iStrokeCount=iVal; }
	void SetStrokesPerExecution(int iVal) { m_iStrokesPerExecution=iVal; }
	void SetStrokesPerRefresh(int iVal) { m_iStrokesPerRefresh=iVal; }

public:
	static const int BRUSHTYPE_OVAL=0;
	static const int BRUSHTYPE_BSLANTED=1;

private:
	int m_iBrushType;
	float m_fBrushSize;
	int m_iStrokeStepSize;
	int m_iStrokeCount;
	int m_iStrokesPerExecution;
	int m_iStrokesPerRefresh;
};
