#include "StdAfx.h"
#include "StrokeGenerator.h"
#include "Stroke.h"
#include "MemoryImage.h"
#include "PaintConfiguration.h"
#include "Display.h"

StrokeGenerator::StrokeGenerator(void)
: m_iRemainedStrokes(0)
{
}

StrokeGenerator::~StrokeGenerator(void)
{
}

void StrokeGenerator::DispatchStrokes(MemoryImage* pCanvas, PaintConfiguration*  pConfig, PaintBrush* pBrush)
{
	if(m_iRemainedStrokes <= 0)
	{
		return;
	}

	int iStrokesPerExecution=pConfig->GetStrokesPerExecution();
	int iStrokesPerRefresh=pConfig->GetStrokesPerRefresh();

	if(pBrush==NULL)
	{
		pBrush=GetBrushByConfiguration(pConfig);
	}

	float fBrushSize=pConfig->GetBrushSize();
	pBrush->SetSize(fBrushSize);

	for(int i=0; i<iStrokesPerExecution; i++)
	{
		Stroke st;
		st.Start(pCanvas, pConfig, pBrush);

		m_iRemainedStrokes --;
		m_iDeadStrokes++;
		if(m_iDeadStrokes % iStrokesPerRefresh == 0)
		{
			gDisplay.InvalidateView(FALSE);
		}
		if(m_iRemainedStrokes <=0)
		{
			break;
		}
	}
}

void StrokeGenerator::Reset(PaintConfiguration* pConfig)
{
	m_iRemainedStrokes=pConfig->GetStrokeCount();
	m_iDeadStrokes=0;
}

bool StrokeGenerator::IsNull(void) const
{
	return m_iRemainedStrokes <=0 ;
}

PaintBrush* StrokeGenerator::GetBrushByConfiguration(PaintConfiguration* pConfig)
{
	PaintBrush* pBrush=NULL;

	int iBrushType=pConfig->GetBrushType();
	switch(iBrushType)
	{
	case PaintConfiguration::BRUSHTYPE_OVAL:
		pBrush=&(m_brushes.m_pbOval);
		break;
	case PaintConfiguration::BRUSHTYPE_BSLANTED:
		pBrush=&(m_brushes.m_pbBSlanted);
		break;
	}

	return pBrush;
}

