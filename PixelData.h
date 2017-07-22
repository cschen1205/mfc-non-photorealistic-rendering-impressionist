#pragma once
#include "afx.h"

class PixelData :
	public CObject
{
public:
	PixelData(void);
	virtual ~PixelData(void);

public:
	PixelData(const PixelData& rhs);
	PixelData& operator=(const PixelData& rhs);
	bool operator==(const PixelData& rhs) const;

private:
	int m_vColor[4];
};
