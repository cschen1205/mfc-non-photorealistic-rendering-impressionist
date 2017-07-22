#include "StdAfx.h"
#include "PaintConfiguration.h"
#include "tinyxml/tinyxml.h"

PaintConfiguration::PaintConfiguration(void)
: m_iBrushType(BRUSHTYPE_OVAL)
, m_fBrushSize(2.8f)
, m_iStrokeStepSize(3)
, m_iStrokeCount(1000)
, m_iStrokesPerExecution(1000)
, m_iStrokesPerRefresh(50)
{
}

PaintConfiguration::~PaintConfiguration(void)
{
}

bool PaintConfiguration::Load(LPCTSTR pFilename)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(CT2CA(pFilename)))
	{
		CString fmt;
		fmt.Format(_T("Failed to load %s"), pFilename);
		AfxMessageBox(fmt, MB_OK);
		return false;
	}

	TiXmlElement* pRoot=doc.RootElement();
	for(TiXmlElement* pElement=pRoot->FirstChildElement(); pElement!=NULL; pElement=pElement->NextSiblingElement())
	{
		CString p(CA2CT(pElement->Value()));
		if(p!=_T("param"))
		{
			continue;
		}
		CString param_name(CA2CT(pElement->Attribute("name")));
		if(param_name==_T("brush name"))
		{
			CString param_value(CA2CT(pElement->Attribute("value")));
			if(param_value==_T("oval brush"))
			{
				m_iBrushType=BRUSHTYPE_OVAL;
			}
			else if(param_value==_T("back slanted line brush"))
			{
				
				m_iBrushType=BRUSHTYPE_BSLANTED;
			}
		}
		else if(param_name==_T("brush size"))
		{
			pElement->QueryFloatAttribute("value", &m_fBrushSize);
		}
		else if(param_name==_T("stroke step size"))
		{
			pElement->QueryIntAttribute("value", &m_iStrokeStepSize);
		}
		else if(param_name==_T("stroke count"))
		{
			pElement->QueryIntAttribute("value", &m_iStrokeCount);
		}
		else if(param_name==_T("strokes per execution"))
		{
			pElement->QueryIntAttribute("value", &m_iStrokesPerExecution);
		}
		else if(param_name==_T("strokes per refresh"))
		{
			pElement->QueryIntAttribute("value", &m_iStrokesPerRefresh);
		}
	}
	
	return true;
}

