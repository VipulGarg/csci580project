// Application4.h: interface for the Application4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_APPLICATION4_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_)
#define AFX_APPLICATION3_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Application.h"

#define	INDEX(x,y)	(x + (y * m_nWidth))	/* simplify fbuf indexing */

class Application4 : public Application  
{
public:
	Application4();
	virtual ~Application4();
	
	int	Initialize();
	virtual int Render(); 
	int Clean();
	void CopyFrameBufferToArrayInRGB(unsigned unsigned char* framebuffer, unsigned char *rgbArray);
	void CreateDepthMap(GzDisplay* display, unsigned char* depthmap);
	void CopyToFrameBuffer(unsigned char* framebuffer, unsigned char* array);
	void BlurDepthMap(unsigned char *depthmap, unsigned char *depthmapBlurred);
	void GetEdgeMap(unsigned char *depthmapBlurred, unsigned char *edgeMap);
	void ApplyGaussianBlur(unsigned char *framebuffer, unsigned char* output);
	void GenerateTexture(unsigned char *texture);
	void LoadTexture(unsigned char *texture);
	void MultiplyImageWithTexture(unsigned char* imagebuffer, unsigned char* texturebuffer, unsigned char *output);
	void AddEdgeMap(unsigned char* imagebuffer, unsigned char* edgemap, unsigned char *output);
};

#endif // !defined(AFX_APPLICATION4_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_)
