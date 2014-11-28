// Project.cpp: implementation of the Project class.
//
//////////////////////////////////////////////////////////////////////

/*
 * application test code for project 
 */

#include "stdafx.h"
#include "CS580Project.h"
#include "Project.h"
#include "Gz.h"
#include "disp.h"
#include "rend.h"
#include "PaperTexture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define INFILE  "pot4.asc"
#define OUTFILE "output.ppm"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Project::Project()
{

}

Project::~Project()
{
	
}

int Project::Initialize()
{
/* to be filled in by the app if it sets camera params */

	GzCamera	camera;  
	int		    xRes, yRes, dispClass;	/* display parameters */ 

	GzToken		nameListShader[9]; 	/* shader attribute names */
	GzPointer   valueListShader[9];		/* shader attribute pointers */
	GzToken     nameListLights[10];		/* light info */
	GzPointer   valueListLights[10];
	int			shaderType, interpStyle;
	float		specpower;
	int		    status; 
 
	status = 0; 

	/* 
	 * Allocate memory for user input
	 */
	m_pUserInput = new GzInput;

	/* 
	 * initialize the display and the renderer 
	 */ 

	m_nWidth = 256;		// frame buffer and display width
	m_nHeight = 256;    // frame buffer and display height

	status |= GzNewFrameBuffer(&m_pFrameBuffer, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_p3DImageInRGB, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pDepthMap, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pDepthMapBlurred, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pEdgeMap, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_p3DImageBlurred, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pTexture, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pProceduralTexture, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pImageTexture, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pTextureImageMult, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pFinalImage, m_nWidth, m_nHeight);
	status |= GzNewFrameBuffer(&m_pGradient, m_nWidth, m_nHeight);
	status |= GzNewFloatArray(&m_pFF1_x, m_nWidth, m_nHeight);
	status |= GzNewFloatArray(&m_pFF1_y, m_nWidth, m_nHeight);
	status |= GzNewFloatArray(&m_pFF_x, m_nWidth, m_nHeight);
	status |= GzNewFloatArray(&m_pFF_y, m_nWidth, m_nHeight);

	status |= GzNewDisplay(&m_pDisplay, GZ_RGBAZ_DISPLAY, m_nWidth, m_nHeight);

	status |= GzGetDisplayParams(m_pDisplay, &xRes, &yRes, &dispClass); 
	 
	status |= GzInitDisplay(m_pDisplay); 
 
	status |= GzNewRender(&m_pRender, GZ_Z_BUFFER_RENDER, m_pDisplay); 

/* Translation matrix */
GzMatrix	scale = 
{ 
	3.25,	0.0,	0.0,	0.0, 
	0.0,	3.25,	0.0,	-3.25, 
	0.0,	0.0,	3.25,	3.5, 
	0.0,	0.0,	0.0,	1.0 
}; 
 
GzMatrix	rotateX = 
{ 
	1.0,	0.0,	0.0,	0.0, 
	0.0,	.7071,	.7071,	0.0, 
	0.0,	-.7071,	.7071,	0.0, 
	0.0,	0.0,	0.0,	1.0 
}; 
 
GzMatrix	rotateY = 
{ 
	.866,	0.0,	-0.5,	0.0, 
	0.0,	1.0,	0.0,	0.0, 
	0.5,	0.0,	.866,	0.0, 
	0.0,	0.0,	0.0,	1.0 
}; 

#if 0 	/* set up app-defined camera if desired, else use camera defaults */
	camera.position[X] = 13.2;      
  	camera.position[Y] = -8.7;
  	camera.position[Z] = -14.8;

  	camera.lookat[X] = 0.8;
  	camera.lookat[Y] = 0.7;
  	camera.lookat[Z] = 4.5;

  	camera.worldup[X] = -0.2;
  	camera.worldup[Y] = 1.0;
  	camera.worldup[Z] = 0.0;

	camera.FOV = 53.7;              /* degrees */

	status |= GzPutCamera(m_pRender, &camera); 
#endif 

	/* Start Renderer */
	status |= GzBeginRender(m_pRender);

	/* Light */

	/* Material property */
	GzColor specularCoefficient = { 0.3, 0.3, 0.3 };
	GzColor ambientCoefficient = { 0.1, 0.1, 0.1 };
	GzColor diffuseCoefficient = {0.7, 0.7, 0.7};

/* 
  renderer is ready for frame --- define lights and shader at start of frame 
*/

	/*
	* Tokens associated with light parameters
	*/
	nameListLights[0] = GZ_DIRECTIONAL_LIGHT;
	valueListLights[0] = (GzPointer)&light1;
	nameListLights[1] = GZ_DIRECTIONAL_LIGHT;
	valueListLights[1] = (GzPointer)&light2;
	status |= GzPutAttribute(m_pRender, 2, nameListLights, valueListLights);
	
	nameListLights[0] = GZ_AMBIENT_LIGHT;
	valueListLights[0] = (GzPointer)&ambientLight;
	status |= GzPutAttribute(m_pRender, 1, nameListLights, valueListLights);
	
	/*
	* Tokens associated with shading 
	*/
	nameListShader[0]  = GZ_DIFFUSE_COEFFICIENT;
	valueListShader[0] = (GzPointer)diffuseCoefficient;

	/* 
	* Select either GZ_COLOR or GZ_NORMALS as interpolation mode  
	*/
	nameListShader[1]  = GZ_INTERPOLATE;
	interpStyle = GZ_NORMAL;       /* Phong shading */

	valueListShader[1] = (GzPointer)&interpStyle;
	nameListShader[2]  = GZ_AMBIENT_COEFFICIENT;
	valueListShader[2] = (GzPointer)ambientCoefficient;
	nameListShader[3]  = GZ_SPECULAR_COEFFICIENT;
	valueListShader[3] = (GzPointer)specularCoefficient;
	nameListShader[4]  = GZ_DISTRIBUTION_COEFFICIENT;
	specpower = 32;
	valueListShader[4] = (GzPointer)&specpower;

	status |= GzPutAttribute(m_pRender, 5, nameListShader, valueListShader);

	//status |= GzPushMatrix(m_pRender, scale);  
	//status |= GzPushMatrix(m_pRender, rotateY); 
	//status |= GzPushMatrix(m_pRender, rotateX); 

	
	LoadProceduralTexture(m_pProceduralTexture);
	LoadImageTexture(m_pImageTexture);

	if (status) exit(GZ_FAILURE); 

	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS); 
}

void Project::BlurGradientMap(unsigned char *gradmap, unsigned char *gradmapBlurred)
{
	float filter[5][5] = {
							1, 2, 4, 2, 1,
							2, 4, 8, 4, 2,
							4, 8, 16, 8, 4,
							2, 4, 8, 4, 2,
							1, 2, 4, 2, 1,
						 };
	float mag = 256.0;
	unsigned char* extendedGradmap;
	GzNewFrameBuffer(&extendedGradmap, m_nWidth + 5, m_nHeight + 5);
	for (int y = 0; y < m_nHeight + 10; ++y)
	{
		for (int x = 0; x < m_nWidth + 10; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			extendedGradmap[framebufferIndex] = 0;
		}
	}

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex1 = 3 * (x + 5) + ((y + 5) * m_nWidth * 3);
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			extendedGradmap[framebufferIndex1] = gradmap[framebufferIndex];
		}
	}

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex1 = 3 * (x + 5) + ((y + 5) * m_nWidth * 3);
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (x == 0 || x == m_nWidth - 1 ||
				y == 0 || y == m_nHeight - 1)
			{
				gradmapBlurred[framebufferIndex] = 255;
				gradmapBlurred[framebufferIndex + 1] = 255;
				gradmapBlurred[framebufferIndex + 2] = 255;
				continue;
			}
			float sum = 0;
			for (int j = -2; j < 3; ++j)
			{
				for (int i = -2; i < 3; ++i)
				{
					int fIndex = 3 * (x + 5 + i) + ((y + 5 + j) * m_nWidth * 3);
					sum += (extendedGradmap[fIndex] * filter[i + 2][j + 2]);
				}
			}
			float val = ((int) (sum / mag));
			gradmapBlurred[framebufferIndex] = val;
			gradmapBlurred[framebufferIndex + 1] = val;
			gradmapBlurred[framebufferIndex + 2] = val;
		}
	}

}


void Project::BlurGradientMap9(unsigned char *gradmap, unsigned char *gradmapBlurred)
{
	float filter[9][9] = {
							1, 2, 4, 8, 16, 8, 4, 2, 1,
							2, 4, 8, 16, 32, 16, 8, 4, 2,
							4, 8, 16, 32, 64, 32, 16, 8, 4,
							8, 16, 32, 64, 128, 64, 32, 16, 8,
							16, 32, 64, 128, 256, 128, 64, 32, 16,
							8, 16, 32, 64, 128, 64, 32, 16, 8,
							4, 8, 16, 32, 64, 32, 16, 8, 4,
							2, 4, 8, 16, 32, 16, 8, 4, 2,
							1, 2, 4, 8, 16, 8, 4, 2, 1,
						 };
	float mag = 256.0 * 256.0;
	unsigned char* extendedGradmap;
	GzNewFrameBuffer(&extendedGradmap, m_nWidth + 8, m_nHeight + 8);
	for (int y = 0; y < m_nHeight + 4; ++y)
	{
		for (int x = 0; x < m_nWidth + 4; ++x)
		{
			int framebufferIndex = 3 * x + (y * (m_nWidth + 4) * 3);
			extendedGradmap[framebufferIndex] = 0;
		}
	}

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex1 = 3 * (x + 4) + ((y + 4) * (m_nWidth + 4) * 3);
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			extendedGradmap[framebufferIndex1] = gradmap[framebufferIndex];
		}
	}

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex1 = 3 * (x + 4) + ((y + 4) * (m_nWidth + 4) * 3);
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (x == 0 || x == m_nWidth - 1 ||
				y == 0 || y == m_nHeight - 1)
			{
				gradmapBlurred[framebufferIndex] = 255;
				gradmapBlurred[framebufferIndex + 1] = 255;
				gradmapBlurred[framebufferIndex + 2] = 255;
				continue;
			}
			float sum = 0;
			for (int j = -4; j < 5; ++j)
			{
				for (int i = -4; i < 5; ++i)
				{
					int fIndex = 3 * (x + 4 + i) + ((y + 4 + j) * (m_nWidth + 4) * 3);
					sum += (extendedGradmap[fIndex] * filter[i + 4][j + 4]);
				}
			}
			float val = ((int) (sum / mag));
			gradmapBlurred[framebufferIndex] = val;
			gradmapBlurred[framebufferIndex + 1] = val;
			gradmapBlurred[framebufferIndex + 2] = val;
		}
	}

}


void Project::LoadProceduralTexture(unsigned char* texture)
{
	generatePaperTexture(texture);
}


void Project::BlurDepthMap(unsigned char *depthmap, unsigned char *depthmapBlurred)
{
	GzMatrix3 filter =  {
							1, 2, 1,
							2, 4, 2,
							1, 2, 1,
						};

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (x == 0 || x == m_nWidth - 1 ||
				y == 0 || y == m_nHeight - 1)
			{
				depthmapBlurred[framebufferIndex] = 255;
				depthmapBlurred[framebufferIndex + 1] = 255;
				depthmapBlurred[framebufferIndex + 2] = 255;
				continue;
			}
			float sum = 0;
			for (int j = -1; j < 2; ++j)
			{
				for (int i = -1; i < 2; ++i)
				{
					int fIndex = 3 * (x + i) + ((y + j) * m_nWidth * 3);
					sum += (depthmap[fIndex] * filter[i + 1][j + 1]);
				}
			}
			depthmapBlurred[framebufferIndex] = ((int) (sum / 16.0));
			depthmapBlurred[framebufferIndex + 1] = ((int) (sum / 16.0));
			depthmapBlurred[framebufferIndex + 2] = ((int) (sum / 16.0));
		}
	}
}


void Project::GetEdgeMap(unsigned char *depthmapBlurred, unsigned char *edgeMap,
							  float* ffx, float* ffy, unsigned char* gradient)
{
	GzMatrix3 filterX =  {
							-1, -2, -1,
							 0,  0,  0,
							 1,  2,  1,
						 };
	GzMatrix3 filterY =  {
							1, 0, -1,
							2, 0, -2,
							1, 0, -1,
						 };

	float threshold = 200;

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (x == 0 || x == m_nWidth - 1 ||
				y == 0 || y == m_nHeight - 1)
			{
				edgeMap[framebufferIndex] = 255;
				edgeMap[framebufferIndex + 1] = 255;
				edgeMap[framebufferIndex + 2] = 255;
				ffx[framebufferIndex] = 0;
				ffy[framebufferIndex] = 0;
				gradient[framebufferIndex] = 0;
				continue;
			}
			float gradX = 0;
			float gradY = 0;
			for (int j = -1; j < 2; ++j)
			{
				for (int i = -1; i < 2; ++i)
				{
					int fIndex = 3 * (x + i) + ((y + j) * m_nWidth * 3);
					gradX += (depthmapBlurred[fIndex] * filterX[i + 1][j + 1]);
					gradY += (depthmapBlurred[fIndex] * filterY[i + 1][j + 1]);
				}
			}
			float gradMag = sqrt(gradX * gradX + gradY * gradY);
			ffx[framebufferIndex] = -gradY;
			ffy[framebufferIndex] = gradX;
			float val;
			if (gradMag < m_fthreshold)
				val = 255;
			else
				val = 0;
			if (gradMag > 255)
				gradient[framebufferIndex] = 255;
			else
				gradient[framebufferIndex] = gradMag;
			edgeMap[framebufferIndex] = val;
			edgeMap[framebufferIndex + 1] = val;
			edgeMap[framebufferIndex + 2] = val;
		}
	}
}


void Project::FindForceField(float* ffx_1, float* ffy_1, unsigned char* gradient, float* ffx, float* ffy)
{
	unsigned char* blurredGradient;
	GzNewFrameBuffer(&blurredGradient, m_nWidth, m_nHeight);
	BlurDepthMap(gradient, blurredGradient);

	GzMatrix3 filterX =  {
							-1, -2, -1,
							 0,  0,  0,
							 1,  2,  1,
						 };
	GzMatrix3 filterY =  {
							1, 0, -1,
							2, 0, -2,
							1, 0, -1,
						 };

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (x == 0 || x == m_nWidth - 1 ||
				y == 0 || y == m_nHeight - 1)
			{
				ffx[framebufferIndex] = 0;
				ffy[framebufferIndex] = 0;
				continue;
			}
			float gradX = 0;
			float gradY = 0;
			for (int j = -1; j < 2; ++j)
			{
				for (int i = -1; i < 2; ++i)
				{
					int fIndex = 3 * (x + i) + ((y + j) * m_nWidth * 3);
					gradX += (blurredGradient[fIndex] * filterX[i + 1][j + 1]);
					gradY += (blurredGradient[fIndex] * filterY[i + 1][j + 1]);
				}
			}
			ffx[framebufferIndex] = ffx_1[framebufferIndex] + gradY;
			ffy[framebufferIndex] = ffy_1[framebufferIndex] - gradX;
		}
	}

}



void Project::CopyFrameBufferToArrayInRGB(unsigned char* framebuffer, unsigned char *rgbArray)
{
	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			rgbArray[framebufferIndex] = framebuffer[framebufferIndex + 2];
			rgbArray[framebufferIndex + 1] = framebuffer[framebufferIndex + 1];
			rgbArray[framebufferIndex + 2] = framebuffer[framebufferIndex];
		}
	}
}


void Project::CopyToFrameBuffer(unsigned char* framebuffer, unsigned char* arraybuffer)
{
	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			framebuffer[framebufferIndex] = arraybuffer[framebufferIndex];
			framebuffer[framebufferIndex + 1] = arraybuffer[framebufferIndex + 1];
			framebuffer[framebufferIndex + 2] = arraybuffer[framebufferIndex + 2];
		}
	}
}


void Project::CreateDepthMap(GzDisplay* display, unsigned char* depthmap)
{
	int maxZ = 0;
	int minZ = INT_MAX;
	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			GzIntensity r,g,b,a;
			GzDepth z;
			GzGetDisplay(display, x, y, &r, &g, &b, &a, &z);
			maxZ = max(z, maxZ);
			minZ = min(z, minZ);
		}
	}

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			GzIntensity r,g,b,a;
			GzDepth z;
			GzGetDisplay(display, x, y, &r, &g, &b, &a, &z);
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			int zval = (int) (((float) (z - minZ) / ((float) (maxZ - minZ))) * 255.0);
			depthmap[framebufferIndex] = zval;
			depthmap[framebufferIndex + 1] = zval;
			depthmap[framebufferIndex + 2] = zval;
		}
	}
}

void Project::AddEdgeMap(unsigned char* imagebuffer, unsigned char* edgemap, unsigned char *output)
{
	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			for (int k = 0; k < 3; ++k)
			{
				float imageColor = ((float) imagebuffer[framebufferIndex + k]) / 255.0;
				float edgeColor = ((float) edgemap[framebufferIndex + k]) / 255.0;
				output[framebufferIndex + k] = (imageColor * edgeColor) * 255.0;
			}
		}
	}
}


float AreaOfTriangle(int a_x, int a_y, int b_x, int b_y, int c_x, int c_y)
{
	float area = abs(0.5 * (a_x * (b_y - c_y) + b_x * (c_y - a_y) + c_x * (a_y - b_y)));
	return area;
}


int Project::DrawLine(unsigned char* framebuffer, unsigned char* edgemap, int x1, int y1,
						   int x2, int y2, int r, int g, int b)
{
	const bool steep = (abs(y2 - y1) > abs(x2 - x1));
	if(steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if(x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = abs(y2 - y1);
 
	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;
 
	const int maxX = (int)x2;
	
	int numParticles = 0;
	for(int x=(int)x1; x<=maxX; x++)
	{
		numParticles++;
		if(steep)
		{
			int framebufferIndex = 3 * y + (x * m_nWidth * 3);
			edgemap[framebufferIndex] = 255;
			framebuffer[framebufferIndex] = b;
			framebuffer[framebufferIndex + 1] = g;
			framebuffer[framebufferIndex + 2] = r;
			//SetPixel(y,x, color);
		}
		else
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			edgemap[framebufferIndex] = 255;
			framebuffer[framebufferIndex] = b;
			framebuffer[framebufferIndex + 1] = g;
			framebuffer[framebufferIndex + 2] = r;
		}

		error -= dy;
		if(error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
	return numParticles;
}


void Project::DrawForceField(unsigned char* depthMap, float* ffx, float* ffy)
{
	for (int y = 0; y < m_nHeight; y += 4)
	{
		for (int x = 0; x < m_nWidth; x += 4)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			float xval = ffx[framebufferIndex];
			float yval = ffy[framebufferIndex];
			float mag = sqrt(xval * xval + yval * yval);
			if (mag == 0)
				continue;
			xval /= mag;
			yval /= mag;
			float slope = yval / xval;
			float angle = atan2(yval, xval);
			if (angle < 0)
			 angle  = 3.14 - angle;
			float newX = x + 2 * cos(angle);
			float newY = y + 2 * sin(angle);
			if (newX < 0)
				newX = 0;
			if (newX > 255)
				newX = 255;
			if (newY < 0)
				newY = 0;
			if (newY > 255)
				newY = 255;
			//DrawLine(depthMap, x, y, newX, newY, 255, 0 , 0);
		}
	}

}


void Project::DrawLooseStrokes(unsigned char* edgemap, float* ffx, float* ffy, unsigned char* output)
{
	int numEdgePoints = 0;
	for (int y = 0; y < m_nHeight; y++)
	{
		for (int x = 0; x < m_nWidth; x++)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (edgemap[framebufferIndex] == 0)
				numEdgePoints++;
		}
	}

	int numParticles = 0.7 * numEdgePoints;
	int distanceInPixels = 2;
	int maxStrokes = 5;
	int num = 0;
	while(num < numParticles)
	{
		int x = rand() % m_nWidth;
		int y = rand() % m_nHeight;
		int numStrokes = 0;
		while (numStrokes < maxStrokes)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (edgemap[framebufferIndex] == 0)
			{
				float xval = ffx[framebufferIndex];
				float yval = ffy[framebufferIndex];
				float mag = sqrt(xval * xval + yval * yval);
				if (mag == 0)
					break;
				xval /= mag;
				yval /= mag;
				float angle = atan2(yval, xval);
				if (angle < 0)
				 angle  = 3.14 - angle;
				float newX = x + m_idistanceInPixels * sin(angle);
				float newY = y + m_idistanceInPixels * cos(angle);
				if (newX < 0)
					newX = 0;
				if (newX > m_nWidth - 1)
					newX = m_nWidth - 1;
				if (newY < 0)
					newY = 0;
				if (newY > m_nHeight - 1)
					newY = m_nHeight - 1;
				num += DrawLine(output, edgemap, x, y, newX, newY, 0, 0, 0);
				numStrokes++;
				x = newX;
				y = newY;
			}
			else
				break;
		}
		
	}
	int h=1;

	for (int y = 0; y < m_nHeight; y++)
	{
		for (int x = 0; x < m_nWidth; x++)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			if (edgemap[framebufferIndex] == 0)
			{
				for (int k = 0; k < 3; ++k)
				{
					output[framebufferIndex + k] = 0;
				}
			}
		}
	}
}

void Project::LoadImageTexture(unsigned char *texture)
{
	FILE* fd = fopen ("papertexture.ppm", "rb");
	if (fd == NULL)
	{
		fprintf (stderr, "texture file not found\n");
		exit(-1);
	}

	GzColor	*image;
	int xs, ys;
	unsigned char pixel[3];
	unsigned char dummy;
	char foo[8];
	int i, j;

	fscanf (fd, "%s %d %d %c", foo, &xs, &ys, &dummy);
	image = (GzColor*)malloc(sizeof(GzColor)*(xs+1)*(ys+1));
	if (image == NULL)
	{
		exit(-1);
	}

	for (i = 0; i < xs*ys; i++) {	/* create array of GzColor values */
		fread(pixel, sizeof(pixel), 1, fd);
		image[i][RED] = (float)((int)pixel[RED]);
		image[i][GREEN] = (float)((int)pixel[GREEN]);
		image[i][BLUE] = (float)((int)pixel[BLUE]);
	}

	fclose(fd);

	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			int i = x + (y * xs);
			texture[framebufferIndex + 0] = image[i][BLUE];
			texture[framebufferIndex + 1] = image[i][GREEN];
			texture[framebufferIndex + 2] = image[i][RED];
		}
	}
}

void Project::ApplyGaussianBlur(unsigned char *framebuffer, unsigned char* output, int filterSize)
{
	//Start Build Gaussian Filter
	float pi = 3.1415;
	float zg2 = 5.5 * 5.5;
	float e = 2.7182;
	int middle = filterSize / 2;
	float sum = 0;
	float *Gussian_Filter = new float[filterSize * filterSize];
	for (int y = 0; y < filterSize; y++)
	{
		for (int x = 0; x < filterSize; x++)
		{
			float exponent = - ((x - middle) * (x - middle) + (y - middle) * (y - middle)) / (2.0f * zg2);
			int index = y * filterSize + x;
			Gussian_Filter[index] = pow(e, exponent) / (2.0f * pi * zg2);
			sum += Gussian_Filter[index];
		}
	}
	//End Build Gaussian Filter

	int result=0;
	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{

			if (filterSize/2 <= y && y < m_nHeight - filterSize/2 && filterSize/2 <= x && x < m_nWidth - filterSize/2)
			{
				float tempSumBlue = 0;
				float tempSumGreen = 0;
				float tempSumRed = 0;
				int fbufIndex =  3*x + (y * m_nWidth*3);
				for (int i = 0; i < filterSize; i++)
				{
					for (int j = 0; j < filterSize; j++)
					{
						int disI = i - filterSize/2;
						int disJ = j - filterSize/2;
						int fbuf_index = ((x+disJ)*3+((y+disI)*m_nWidth*3));
						tempSumBlue += Gussian_Filter[i * filterSize + j] * framebuffer[fbuf_index + 2];
						tempSumGreen += Gussian_Filter[i * filterSize + j] * framebuffer[fbuf_index + 1];
						tempSumRed += Gussian_Filter[i * filterSize + j] * framebuffer[fbuf_index + 0];
					}
				}
				output[fbufIndex + 2] = tempSumBlue / sum;
				output[fbufIndex + 1] = tempSumGreen / sum;
				output[fbufIndex + 0] = tempSumRed / sum;
			}
			else
			{
				float tempSumBlue = 0;
				float tempSumGreen = 0;
				float tempSumRed = 0;
				int fbufIndex = x*3 + y * m_nWidth*3;
				float sum_rigid = 0;
				for (int i = 0; i < filterSize; i++)
				{
					for (int j = 0; j < filterSize; j++)
					{
						int disI = i - filterSize/2;
						int disJ = j - filterSize/2;
						if (0 <= y+disI && y+disI < m_nHeight && 0 <= x+disJ && x+disJ < m_nWidth)
						{
							int fbuf_index = ((x+disJ)*3+((y+disI)*m_nWidth)*3);
							tempSumBlue += Gussian_Filter[i * filterSize + j] * framebuffer[fbuf_index + 2];
							tempSumGreen += Gussian_Filter[i * filterSize + j] * framebuffer[fbuf_index + 1];
							tempSumRed += Gussian_Filter[i * filterSize + j] * framebuffer[fbuf_index + 0];
							sum_rigid += Gussian_Filter[i * filterSize + j];
						}
					}
				}
				output[fbufIndex + 2] = tempSumBlue / sum_rigid;
				output[fbufIndex + 1] = tempSumGreen / sum_rigid;
				output[fbufIndex + 0] = tempSumRed / sum_rigid;
			}
		}
	}
}



void Project::MultiplyImageWithTexture(unsigned char* imagebuffer, unsigned char* texturebuffer, unsigned char *output)
{
	for (int y = 0; y < m_nHeight; ++y)
	{
		for (int x = 0; x < m_nWidth; ++x)
		{
			int framebufferIndex = 3 * x + (y * m_nWidth * 3);
			for (int k = 0; k < 3; ++k)
			{
				float imageColor = ((float) imagebuffer[framebufferIndex + k]) / 255.0;
				float textureColor = ((float) texturebuffer[framebufferIndex + k]) / 255.0;
				output[framebufferIndex + k] = (imageColor * textureColor) * 255.0;
			}
		}
	}
}


int Project::Render() 
{
	GzToken		nameListTriangle[2]; 	/* vertex attribute names */
	GzPointer	valueListTriangle[2]; 	/* vertex attribute pointers */
	GzCoord		vertexList[3];	/* vertex position coordinates */ 
	GzCoord		normalList[3];	/* vertex normals */
	int			status; 

	objParser.getNumOfVertices();


	/* Initialize Display */
	status |= GzInitDisplay(m_pDisplay); 
	
	/* 
	* Tokens associated with triangle vertex values 
	*/ 
	nameListTriangle[0] = GZ_POSITION; 
	nameListTriangle[1] = GZ_NORMAL; 
	 
	// I/O File open

	FILE *outfile;
	if( (outfile  = fopen( OUTFILE , "wb" )) == NULL )
	{
         AfxMessageBox( "The output file was not opened\n" );
		 return GZ_FAILURE;
	}

	/* 
	* Walk through the list of triangles, set color 
	* and render each triangle 
	*/ 
	for (int i = 0; i < objParser.getNumOfFaces(); ++i)
	{
		Face face = objParser.getFace(i + 1);
		vector<Face::FaceVertex> faceVertices = face.faceVertices;
		for (int j = 0; j < faceVertices.size(); ++j)
		{
			Face::FaceVertex faceVertex = faceVertices[j];
			Vertex vertex = objParser.getVertex(faceVertex.v);
			VertexNormal vertexNormal = objParser.getVertexNormal(faceVertex.vn);
			vertexList[j][0] = vertex.x;
			vertexList[j][1] = vertex.y;
			vertexList[j][2] = vertex.z;
			normalList[j][0] = vertexNormal.x;
			normalList[j][1] = vertexNormal.y;
			normalList[j][2] = vertexNormal.z;
		}
		valueListTriangle[0] = (GzPointer)vertexList;
		valueListTriangle[1] = (GzPointer)normalList;
		GzPutTriangle(m_pRender, 2, nameListTriangle, valueListTriangle);
	}

	//GzFlushDisplay2File(outfile, m_pDisplay); 	/* write out or update display to file*/
	GzFlushDisplay2FrameBuffer(m_pFrameBuffer, m_pDisplay);	// write out or update display to frame buffer

	switch(currRenderFunc)
	{
	case 1:
		{
			CreateDepthMap(m_pDisplay, m_pDepthMap);
			BlurDepthMap(m_pDepthMap, m_pDepthMapBlurred);
			CopyToFrameBuffer(m_pFrameBuffer, m_pDepthMapBlurred);
			break;
		}

	case 2:
		{
			CreateDepthMap(m_pDisplay, m_pDepthMap);
			BlurDepthMap(m_pDepthMap, m_pDepthMapBlurred);
			GetEdgeMap(m_pDepthMapBlurred, m_pEdgeMap, m_pFF1_x, m_pFF1_y, m_pGradient);
			CopyToFrameBuffer(m_pFrameBuffer, m_pEdgeMap);
			break;
		}

	case 3:
		{
			ApplyGaussianBlur(m_pFrameBuffer, m_p3DImageBlurred, m_ifilterLength);
			CopyToFrameBuffer(m_pFrameBuffer, m_p3DImageBlurred);
			break;
		}

	case 4:
		{
			ApplyGaussianBlur(m_pFrameBuffer, m_p3DImageBlurred, m_ifilterLength);
			MultiplyImageWithTexture(m_p3DImageBlurred, m_pProceduralTexture, m_pTextureImageMult);
			CopyToFrameBuffer(m_pFrameBuffer, m_pTextureImageMult);
			break;
		}

	case 5:
		{
			ApplyGaussianBlur(m_pFrameBuffer, m_p3DImageBlurred, m_ifilterLength);
			MultiplyImageWithTexture(m_p3DImageBlurred, m_pImageTexture, m_pTextureImageMult);
			CopyToFrameBuffer(m_pFrameBuffer, m_pTextureImageMult);
			break;
		}

	case 6:
		{
			CreateDepthMap(m_pDisplay, m_pDepthMap);
			BlurDepthMap(m_pDepthMap, m_pDepthMapBlurred);
			GetEdgeMap(m_pDepthMapBlurred, m_pEdgeMap, m_pFF1_x, m_pFF1_y, m_pGradient);
			FindForceField(m_pFF1_x, m_pFF1_y, m_pGradient, m_pFF_x, m_pFF_y);
			unsigned char* output;
			GzNewFrameBuffer(&output, m_nWidth, m_nHeight);
			DrawLooseStrokes(m_pEdgeMap, m_pFF_x, m_pFF_y, output);
			CopyToFrameBuffer(m_pFrameBuffer, output);
			break;
		}

	case 7:
		{
			CreateDepthMap(m_pDisplay, m_pDepthMap);
			BlurDepthMap(m_pDepthMap, m_pDepthMapBlurred);
			GetEdgeMap(m_pDepthMapBlurred, m_pEdgeMap, m_pFF1_x, m_pFF1_y, m_pGradient);
			ApplyGaussianBlur(m_pFrameBuffer, m_p3DImageBlurred, m_ifilterLength);
			if (lastTexture == 1)
				CopyToFrameBuffer(m_pTexture, m_pImageTexture);
			else
				CopyToFrameBuffer(m_pTexture, m_pProceduralTexture);
			MultiplyImageWithTexture(m_p3DImageBlurred, m_pTexture, m_pTextureImageMult);
			FindForceField(m_pFF1_x, m_pFF1_y, m_pGradient, m_pFF_x, m_pFF_y);
			DrawLooseStrokes(m_pEdgeMap, m_pFF_x, m_pFF_y, m_pTextureImageMult);
			CopyToFrameBuffer(m_pFrameBuffer, m_pTextureImageMult);
			break;
		}
	default:
		break;
	}


	//CreateDepthMap(m_pDisplay, m_pDepthMap);
	//BlurDepthMap(m_pDepthMap, m_pDepthMapBlurred);
	//GetEdgeMap(m_pDepthMapBlurred, m_pEdgeMap, m_pFF1_x, m_pFF1_y, m_pGradient);
	//ApplyGaussianBlur(m_pFrameBuffer, m_p3DImageBlurred, 9);
	//MultiplyImageWithTexture(m_p3DImageBlurred, m_pPaperTexture, m_pTextureImageMult);
	//
	//FindForceField(m_pFF1_x, m_pFF1_y, m_pGradient, m_pFF_x, m_pFF_y);
	//unsigned char* output;
	//GzNewFrameBuffer(&output, m_nWidth, m_nHeight);
	////DrawLine(line, 1, 230, 200, 210, 0, 0, 0);
	////DrawForceField(m_pDepthMap, m_pFF_x, m_pFF_y);
	//DrawLooseStrokes(m_pEdgeMap, m_pFF_x, m_pFF_y, m_pTextureImageMult);
	//CopyToFrameBuffer(m_pFrameBuffer, m_pTextureImageMult);

	/* 
	 * Close file
	 */

	if( fclose( outfile ) )
      AfxMessageBox( "The output file was not closed\n" );
 
	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS); 
}


int Project::Clean()
{
	/* 
	 * Clean up and exit 
	 */ 
	int	status = 0; 

	status |= GzFreeRender(m_pRender); 
	status |= GzFreeDisplay(m_pDisplay);
	
	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS);
}



