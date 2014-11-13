// Application4.cpp: implementation of the Application4 class.
//
//////////////////////////////////////////////////////////////////////

/*
 * application test code for homework assignment 
 */

#include "stdafx.h"
#include "CS580HW.h"
#include "Application4.h"
#include "Gz.h"
#include "disp.h"
#include "rend.h"

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

Application4::Application4()
{

}

Application4::~Application4()
{
	
}





int Application4::Initialize()
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
	status |= GzNewFrameBuffer(&m_pPaperTexture, m_nWidth, m_nHeight);

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

	if (status) exit(GZ_FAILURE); 

	if (status) 
		return(GZ_FAILURE); 
	else 
		return(GZ_SUCCESS); 
}


int Application4::Render() 
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

	GzFlushDisplay2File(outfile, m_pDisplay); 	/* write out or update display to file*/
	GzFlushDisplay2FrameBuffer(m_pFrameBuffer, m_pDisplay);	// write out or update display to frame buffer


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


int Application4::Clean()
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



