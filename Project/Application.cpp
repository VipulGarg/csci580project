// Application.cpp: implementation of the Application class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CS580Project.h"
#include "Application.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Application::Application()
{
	m_pDisplay = NULL;		// the display
	m_pRender = NULL;		// the renderer
	m_pUserInput = NULL;
	m_pFrameBuffer = NULL;
	m_p3DImageInRGB = NULL;
	m_pDepthMap = NULL;
	m_pDepthMapBlurred = NULL;
	m_pEdgeMap = NULL;
	m_p3DImageBlurred = NULL;
	m_pTexture = NULL;
	m_pProceduralTexture = NULL;
	m_pImageTexture = NULL;
	m_pTextureImageMult = NULL;
	m_pFinalImage = NULL;
	m_pFF1_x = NULL;
	m_pFF1_y = NULL;
	m_pGradient = NULL;
	m_pFF_x = NULL;
	m_pFF_y = NULL;
}

Application::~Application()
{
	if(m_pFrameBuffer != NULL)
		delete m_pFrameBuffer;
}

