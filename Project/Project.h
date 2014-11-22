// Project.h: interface for the Project class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_)
#define AFX_PROJECT_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Application.h"

#define	INDEX(x,y)	(x + (y * m_nWidth))	/* simplify fbuf indexing */

class Project : public Application  
{
public:
	Project();
	virtual ~Project();
	
	int	Initialize();
	virtual int Render(); 
	int Clean();
	void CopyFrameBufferToArrayInRGB(unsigned unsigned char* framebuffer, unsigned char *rgbArray);
	void CreateDepthMap(GzDisplay* display, unsigned char* depthmap);
	void CopyToFrameBuffer(unsigned char* framebuffer, unsigned char* array);
	void BlurDepthMap(unsigned char *depthmap, unsigned char *depthmapBlurred);
	void GetEdgeMap(unsigned char *depthmapBlurred, unsigned char *edgeMap, float* ffx, float* ffy, unsigned char* gradient);
	void ApplyGaussianBlur(unsigned char *framebuffer, unsigned char* output, int filterSize);
	void GenerateTexture(unsigned char *texture);
	void LoadTexture(unsigned char *texture);
	void LoadPaperTexture(unsigned char*texture);
	void MultiplyImageWithTexture(unsigned char* imagebuffer, unsigned char* texturebuffer, unsigned char *output);
	void AddEdgeMap(unsigned char* imagebuffer, unsigned char* edgemap, unsigned char *output);
	void FindForceField(float* ffx_1, float* ffy_1, unsigned char* gradient, float* ffx, float* ffy);
	int DrawLine(unsigned char* framebuffer, unsigned char* edgemap, int x1, int y1, int x2, int y2, int r, int g, int b);
	void DrawForceField(unsigned char* depthMap, float* ffx, float* ffy);
	void DrawLooseStrokes(unsigned char* edgemap, float* ffx, float* ffy, unsigned char* output);
	void BlurGradientMap(unsigned char *gradmap, unsigned char *gradmapBlurred);
	void BlurGradientMap9(unsigned char *gradmap, unsigned char *gradmapBlurred);
};

#endif // !defined(AFX_PROJECT_H__43A7FA9C_6CD6_4A79_9567_2354BFEFAFFB__INCLUDED_)
