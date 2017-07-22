#include "StdAfx.h"
#include "BrushToolkit.h"

BrushToolkit::BrushToolkit(void)
{
	m_pbOval.SetSize(2);
	m_pbBSlanted.SetSize(2);
	m_pbBSlantedRain.SetSize(2);
	m_pbPoint.SetSize(2);
	m_pbBSlantedDotted.SetSize(2);
	m_pbAdvCircle.SetSize(2);
	m_pbAdvSquare.SetSize(2);
	m_pbAdvWaterdrop.SetSize(2);
	m_pbTexture.SetSize(2);
	m_pbEmboss.SetSize(2);
	m_pbAdvTexture.SetSize(2);
	m_pbAdvSlanted.SetSize(2);
}

BrushToolkit::~BrushToolkit(void)
{
}
