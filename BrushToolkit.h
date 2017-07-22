#pragma once
#include "afx.h"

#include "PaintBrushOval.h"
#include "PaintBrushBSlanted.h"
#include "PaintBrushBSlantedRain.h"
#include "PaintBrushPoint.h"
#include "PaintBrushBSlantedDotted.h"
#include "PaintBrushAdvCircle.h"
#include "PaintBrushAdvSquare.h"
#include "PaintBrushAdvWaterdrop.h"
#include "PaintBrushTexture.h"
#include "PaintBrushEmboss.h"
#include "PaintBrushAdvTexture.h"
#include "PaintBrushAdvSlanted.h"

class BrushToolkit :
	public CObject
{
public:
	BrushToolkit(void);
	~BrushToolkit(void);

public:
	PaintBrushOval m_pbOval;
	PaintBrushBSlanted m_pbBSlanted;
	PaintBrushBSlantedRain m_pbBSlantedRain;
	PaintBrushPoint m_pbPoint;
	PaintBrushBSlantedDotted m_pbBSlantedDotted;
	PaintBrushAdvCircle m_pbAdvCircle;
	PaintBrushAdvSquare m_pbAdvSquare;
	PaintBrushAdvWaterdrop m_pbAdvWaterdrop;
	PaintBrushTexture m_pbTexture;
	PaintBrushEmboss m_pbEmboss;
	PaintBrushAdvTexture m_pbAdvTexture;
	PaintBrushAdvSlanted m_pbAdvSlanted;
};
