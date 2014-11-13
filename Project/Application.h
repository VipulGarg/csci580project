// Application.h: interface for the Application class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATION_H__3387B79A_B69F_491D_B782_81D9CAFAAB0F__INCLUDED_)
#define AFX_APPLICATION_H__3387B79A_B69F_491D_B782_81D9CAFAAB0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Gz.h"
#include "disp.h"
#include "rend.h"

class Application  
{
public:
	Application();
	virtual ~Application();
	
public:
	GzDisplay* m_pDisplay;		// the display
	GzRender*  m_pRender;		// the renderer
	GzInput*   m_pUserInput;
	unsigned char* m_pFrameBuffer;	// Frame Buffer
	unsigned char* m_p3DImageInRGB;
	unsigned char* m_pDepthMap;
	unsigned char* m_pDepthMapBlurred;
	unsigned char* m_pEdgeMap;
	unsigned char* m_p3DImageBlurred;
	unsigned char* m_pPaperTexture;
	unsigned char* m_pTextureImageMult;
	unsigned char* m_pFinalImage;
	/*char* m_p3DImageBlurred;
	float* m_pGradientX;
	float* m_pGradientY;
	float* m_pGradientMag;
	char* m_pEdgeMap;
	float* m_pforceField;
	char* m_pPaperTexture;*/
	int   m_nWidth;			// width of Frame Buffer
	int   m_nHeight;		// height of Frame Buffer

	virtual int Render()=0; // Pass user input data and call renderer
};

#endif // !defined(AFX_APPLICATION_H__3387B79A_B69F_491D_B782_81D9CAFAAB0F__INCLUDED_)
