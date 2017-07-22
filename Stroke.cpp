#include "StdAfx.h"
#include "Stroke.h"
#include "MemoryImage.h"
#include "PaintConfiguration.h"
#include "PaintBrush.h"
#include "Display.h"
#include "RandomGenerator.h"

Stroke::Stroke(void)
: m_pCanvas(NULL)
, m_pConfig(NULL)
, m_bDead(true)
, m_pBrush(NULL)
{
}

Stroke::~Stroke(void)
{
}

void Stroke::Start(MemoryImage* pCanvas, PaintConfiguration*  pConfig, PaintBrush* pBrush)
{
	m_pCanvas=pCanvas;
	m_pConfig=pConfig;
	m_pBrush=pBrush;
	SetFromConfiguration(pConfig);

	m_bDead=false;

	AdditionalStartup();

	while(!m_bDead)
	{
		Update();
	}
}

void Stroke::SetFromConfiguration(PaintConfiguration* pConfig)
{
	m_iStrokeStepSize=pConfig->GetStrokeStepSize();
}

void Stroke::Update(void)
{
	if(m_bDead)
	{
		return;
	}

	if(Continue())
	{
		Mark();
		Move();
	}
}

void Stroke::Mark(void)
{
	CPoint ptStart(static_cast<int>(m_prev_position.GetX()), static_cast<int>(m_prev_position.GetY()));
	CPoint ptEnd(static_cast<int>(m_position.GetX()), static_cast<int>(m_position.GetY()));

	CRect drRect;
	gDisplay.GetClientRect(drRect);

	m_pCanvas->PaintCurrent(ptStart, ptEnd, drRect, m_pBrush);
}

void Stroke::Move(void)
{
	const float PI=3.1415926f;
	float fStepSize=static_cast<float>(m_iStrokeStepSize);

	m_prev_position=m_position;

	float rad=PI * RandomEngine->NextFloat();
	Vec2f v(fStepSize * cos(rad), fStepSize * sin(rad));
	m_position+=v;
}

void Stroke::SetBrush(PaintBrush* pBrush)
{
	m_pBrush=pBrush;
}

bool Stroke::IsOutsideCanvas(void)
{
	int canvas_width=m_pCanvas->GetWidth();
	int canvas_height=m_pCanvas->GetHeight();

	int x=static_cast<int>(m_position.GetX());
	int y=static_cast<int>(m_position.GetY());

	CRect rtClientRect;
	gDisplay.GetClientRect(rtClientRect);

	CPoint ptViewPosition(x, y);
	CPoint ptCanvasPosition;
	m_pCanvas->TranslateViewPosition2CanvasPosition(rtClientRect, ptCanvasPosition, ptViewPosition);

	if(ptCanvasPosition.x < 0 || ptCanvasPosition.x>=canvas_width || ptCanvasPosition.y < 0 || ptCanvasPosition.y>= canvas_height)
	{
		return true;
	}

	return false;
}

void Stroke::AdditionalStartup()
{
	float canvas_width=static_cast<float>(m_pCanvas->GetWidth());
	float canvas_height=static_cast<float>(m_pCanvas->GetHeight());

	CPoint ptCanvasOrigin(static_cast<int>(canvas_width * RandomEngine->NextFloat()), static_cast<int>(canvas_height * RandomEngine->NextFloat()));

	CRect rtClientRect;
	gDisplay.GetClientRect(rtClientRect);

	CPoint ptViewPosition;
	m_pCanvas->TranslateCanvasPosition2ViewPosition(rtClientRect, ptCanvasOrigin, ptViewPosition);

	m_position.SetX(static_cast<float>(ptViewPosition.x));
	m_position.SetY(static_cast<float>(ptViewPosition.y));

	m_prev_position=m_position;
}

bool Stroke::Continue()
{
	if(IsOutsideCanvas())
	{
		Kill();
		return false;
	}

	return true;
}
