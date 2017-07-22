#pragma once
#include "afx.h"
#include "Vec2f.h"

class MemoryImage;
class PaintConfiguration;
class PaintBrush;

class Stroke :
	public CObject
{
public:
	Stroke(void);
	~Stroke(void);

public:
	void Start(MemoryImage* pCanvas, PaintConfiguration*  pConfig, PaintBrush* pBrush);
protected:
	void Update(void);

protected:
	int m_iStrokeStepSize;

public:
	void SetFromConfiguration(PaintConfiguration* pConfig);

private:
	bool m_bDead;
protected:
	void Kill() { m_bDead=true; }

protected:
	MemoryImage* m_pCanvas;
	PaintConfiguration* m_pConfig;
	PaintBrush* m_pBrush;

public:
	void SetBrush(PaintBrush* pBrush);

public:
	virtual void Mark(void);
	virtual void Move(void);
	virtual void AdditionalStartup();
	virtual bool Continue();

protected:
	Vec2f m_position;
	Vec2f m_prev_position;

protected:
	bool IsOutsideCanvas(void);
};
