#include "StdAfx.h"
#include "PixelData.h"

PixelData::PixelData(void)
{
	m_vColor[0]=0;
	m_vColor[1]=0;
	m_vColor[2]=0;
	m_vColor[3]=0;
}

PixelData::~PixelData(void)
{
}

PixelData::PixelData(const PixelData& rhs)
{
	m_vColor[0]=rhs.m_vColor[0];
	m_vColor[1]=rhs.m_vColor[1];
	m_vColor[2]=rhs.m_vColor[2];
	m_vColor[3]=rhs.m_vColor[3];
}

PixelData& PixelData::operator=(const PixelData& rhs)
{
	m_vColor[0]=rhs.m_vColor[0];
	m_vColor[1]=rhs.m_vColor[1];
	m_vColor[2]=rhs.m_vColor[2];
	m_vColor[3]=rhs.m_vColor[3];

	return *this;
}

bool PixelData::operator==(const PixelData& rhs) const
{
	for(int i=0; i<4; i++)
	{
		if(m_vColor[i] != rhs.m_vColor[i])
		{
			return false;
		}
	}
	return true;
}