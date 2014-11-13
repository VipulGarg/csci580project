/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"limits"
#include	"Gz.h"
#include	"rend.h"
#include	"Geometry.h"
#include	"HelperFunc.h"
#include	"Shader.h"


int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value

	float cosVal = cos((degree * 3.14) / 180);
	float sinVal = sin((degree * 3.14) / 180);

	mat[1][1] = cosVal;
	mat[1][2] = -sinVal;
	mat[2][1] = sinVal;
	mat[2][2] = cosVal;

	return GZ_SUCCESS;
}


int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value

	float cosVal = cos((degree * 3.14) / 180);
	float sinVal = sin((degree * 3.14) / 180);

	mat[0][0] = cosVal;
	mat[0][2] = sinVal;
	mat[2][0] = -sinVal;
	mat[2][2] = cosVal;

	return GZ_SUCCESS;
}


int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value

	float cosVal = cos((degree * 3.14) / 180);
	float sinVal = sin((degree * 3.14) / 180);

	mat[0][0] = cosVal;
	mat[0][1] = -sinVal;
	mat[1][0] = sinVal;
	mat[1][1] = cosVal;

	return GZ_SUCCESS;
}


int GzTrxMat(GzCoord translate, GzMatrix mat)
{
// Create translation matrix
// Pass back the matrix using mat value

	mat[0][3] = translate[0];
	mat[1][3] = translate[1];
	mat[2][3] = translate[2];

	return GZ_SUCCESS;
}


int GzScaleMat(GzCoord scale, GzMatrix mat)
{
// Create scaling matrix
// Pass back the matrix using mat value

	mat[0][0] = scale[0];
	mat[1][1] = scale[1];
	mat[2][2] = scale[2];

	return GZ_SUCCESS;
}


//----------------------------------------------------------
// Begin main functions

int GzNewRender(GzRender **render, GzRenderClass renderClass, GzDisplay	*display)
{
/*  
- malloc a renderer struct 
- keep closed until all inits are done 
- setup Xsp and anything only done once 
- span interpolator needs pointer to display 
- check for legal class GZ_Z_BUFFER_RENDER 
- init default camera 
*/ 
	*render = new GzRender();

	switch(renderClass)
	{
	case GZ_Z_BUFFER_RENDER:
		(*render)->renderClass = renderClass;
		break;
	default:
		return GZ_FAILURE;
	}

	(*render)->display = display;
	

	// Took the default values of the camera as the one given by application
	GzCamera camera;
	camera.position[X] = DEFAULT_IM_X;
  	camera.position[Y] = DEFAULT_IM_Y;
  	camera.position[Z] = DEFAULT_IM_Z;

  	camera.lookat[X] = 0.0;
  	camera.lookat[Y] = 0.0;
  	camera.lookat[Z] = 0.0;

  	camera.worldup[X] = 0;
  	camera.worldup[Y] = 1.0;
  	camera.worldup[Z] = 0.0;

	camera.FOV = DEFAULT_FOV;              /* degrees */

	(*render)->camera = camera;

	GzMatrix mat =  { 
						display->xres / 2,	0.0,	0.0,	display->xres / 2, 
						0.0,	-display->yres / 2,	0.0,	display->yres / 2, 
						0.0,	0.0,	INT_MAX * tan((camera.FOV * (3.14 / 180)) / 2),	0.0, 
						0.0,	0.0,	0.0,	1.0 
					};

	memcpy((*render)->Xsp, mat, sizeof(GzMatrix));

	GzMatrix identity =	{ 
							1.0,	0.0,	0.0,	0.0, 
							0.0,	1.0,	0.0,	0.0, 
							0.0,	0.0,	1.0,	0.0, 
							0.0,	0.0,	0.0,	1.0 
						};
	memcpy((*render)->Xcum, identity, sizeof(GzMatrix));
	memcpy((*render)->XcumNorm, identity, sizeof(GzMatrix));

	GzColor ka = DEFAULT_AMBIENT;
	(*render)->Ka[0] = ka[0];
	(*render)->Ka[1] = ka[1];
	(*render)->Ka[2] = ka[2];

	
	GzColor kd = DEFAULT_DIFFUSE;
	(*render)->Kd[0] = kd[0];
	(*render)->Kd[1] = kd[1];
	(*render)->Kd[2] = kd[2];

	
	GzColor ks = DEFAULT_SPECULAR;
	(*render)->Ks[0] = ks[0];
	(*render)->Ks[1] = ks[1];
	(*render)->Ks[2] = ks[2];

	(*render)->spec = DEFAULT_SPEC;

	(*render)->ambientlight.color[0] = 0;
	(*render)->ambientlight.color[1] = 0;
	(*render)->ambientlight.color[2] = 0;

	(*render)->numlights = 0;
	(*render)->interp_mode = 0;
	(*render)->matlevel = 0;
	(*render)->open = 1;

	return GZ_SUCCESS;

}


int GzFreeRender(GzRender *render)
{
/* 
-free all renderer resources
*/
	if (!render->open)
		return GZ_FAILURE;

	
	delete[] render->camera.position;
	delete[] render->camera.worldup;
	delete[] render->camera.lookat;
	delete[] render->camera.Xiw;
	delete[] render->camera.Xpi;
	
	for (int i = 0; i < render->matlevel; ++i)
	{
		delete[] render->Ximage[i];
	}

	delete[] render;

	return GZ_SUCCESS;
}


int GzBeginRender(GzRender *render)
{
/*  
- set up for start of each frame - clear frame buffer 
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms if it want to.
*/
	GzPushMatrix(render, render->Xsp);

	GzMatrix	Xpi =	{
								1.0,	0.0,			0.0,				0.0,
								0.0,	1.0,			0.0,				0.0,
								0.0,	0.0,			1.0,				0.0,
								0.0,	0.0,	tan((render->camera.FOV * (3.14 / 180)) / 2),	1.0
						};
	memcpy(render->camera.Xpi, Xpi, sizeof(GzMatrix));
	GzPushMatrix(render, Xpi);

	Vector3D zC(render->camera.position[0], render->camera.position[1], render->camera.position[2],
				render->camera.lookat[0], render->camera.lookat[1], render->camera.lookat[2]);
	zC.normalizeVector();

	Vector3D up(render->camera.worldup[0], render->camera.worldup[1], render->camera.worldup[2]);
	up.normalizeVector();

	float upDotzC = up.x * zC.x + up.y * zC.y + up.z * zC.z;

	Vector3D yC(up.x - upDotzC * zC.x, up.y - upDotzC * zC.y, up.z - upDotzC * zC.z);
	yC.normalizeVector();

	float x,y,z;
	CrossProduct(yC, zC, x, y, z);
	Vector3D xC(x, y, z);
	xC.normalizeVector();

	float xCDotC = xC.x * render->camera.position[0] + xC.y * render->camera.position[1] + xC.z * render->camera.position[2];
	float yCDotC = yC.x * render->camera.position[0] + yC.y * render->camera.position[1] + yC.z * render->camera.position[2];
	float zCDotC = zC.x * render->camera.position[0] + zC.y * render->camera.position[1] + zC.z * render->camera.position[2];

	GzMatrix	Xiw =	{
								xC.x,	xC.y,	xC.z,	-xCDotC,
								yC.x,	yC.y,	yC.z,	-yCDotC,
								zC.x,	zC.y,	zC.z,	-zCDotC,
								0.0,	0.0,	 0.0,	 1.0
						};

	memcpy(render->camera.Xiw, Xiw, sizeof(GzMatrix));
	GzPushMatrix(render, Xiw);

	return GZ_SUCCESS;
}


int GzPutCamera(GzRender *render, GzCamera *camera)
{
/*
- overwrite renderer camera structure with new camera definition
*/
	if (!render->open)
		return GZ_FAILURE;

	render->camera = *camera;
	render->Xsp[2][2] = INT_MAX * tan((render->camera.FOV * (3.14 / 180)) / 2);

	return GZ_SUCCESS;	
}


int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	if (!render->open)
		return GZ_FAILURE;

	if (render->matlevel == MATLEVELS)
		return GZ_FAILURE;

	memcpy(render->Ximage[render->matlevel], matrix, sizeof(GzMatrix));

	// Add to the cumulative matrix
	GzMatrix mat;
	MultiplyTwoMatrices(render->Xcum, matrix, mat);
	memcpy(render->Xcum, mat, sizeof(GzMatrix));


	if (render->matlevel == 0 || render->matlevel == 1)
	{
		GzMatrix identity =	{ 
							1.0,	0.0,	0.0,	0.0, 
							0.0,	1.0,	0.0,	0.0, 
							0.0,	0.0,	1.0,	0.0, 
							0.0,	0.0,	0.0,	1.0 
							};
		memcpy(render->Xnorm[render->matlevel], identity, sizeof(GzMatrix));
	}
	else
	{
		// Remove translation
		matrix[0][3] = 0;
		matrix[1][3] = 0;
		matrix[2][3] = 0;

		// make it unitary
		float k = (sqrt(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1] + matrix[0][2] * matrix[0][2]));
		if (k != 0)
		{
			for (int i = 0; i < 3; ++i)
			{
				for(int j = 0; j < 3; ++j)
				{
					matrix[i][j] = matrix[i][j] / k;
				}
			}
		}
		memcpy(render->Xnorm[render->matlevel], matrix, sizeof(GzMatrix));
	}

	MultiplyTwoMatrices(render->XcumNorm, render->Xnorm[render->matlevel], mat);
	memcpy(render->XcumNorm, mat, sizeof(GzMatrix));
	render->matlevel++;
	return GZ_SUCCESS;
}


int GzPopMatrix(GzRender *render)
{
/*
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	if (!render->open)
		return GZ_FAILURE;

	if (render->matlevel == 0)
		return GZ_FAILURE;

	render->matlevel--;

	// Recalculate the current cumulative matrix
	GzMatrix	matMult =	{ 
							1.0,	0.0,	0.0,	0.0, 
							0.0,	1.0,	0.0,	0.0, 
							0.0,	0.0,	1.0,	0.0, 
							0.0,	0.0,	0.0,	1.0 
						};
	GzMatrix mat;
	for (int i = 0; i < render->matlevel; ++i)
	{
		MultiplyTwoMatrices(matMult, render->Ximage[i], mat);
		memcpy(matMult, mat, sizeof(GzMatrix));
	}
	memcpy(render->Xcum, matMult, sizeof(GzMatrix));


	GzMatrix matMult1 =	{ 
							1.0,	0.0,	0.0,	0.0, 
							0.0,	1.0,	0.0,	0.0, 
							0.0,	0.0,	1.0,	0.0, 
							0.0,	0.0,	0.0,	1.0 
						};
	GzMatrix mat1;
	for (int i = 0; i < render->matlevel; ++i)
	{
		MultiplyTwoMatrices(matMult1, render->Xnorm[i], mat1);
		memcpy(matMult1, mat1, sizeof(GzMatrix));
	}
	memcpy(render->XcumNorm, matMult1, sizeof(GzMatrix));

	return GZ_SUCCESS;
}


int GzPutLight(GzRender	*render, GzLight light, int lightIndex)
{
	if (!render->open)
		return GZ_FAILURE;

	render->lights[lightIndex].direction[0] = light.direction[0];
	render->lights[lightIndex].direction[1] = light.direction[1];
	render->lights[lightIndex].direction[2] = light.direction[2];
	render->lights[lightIndex].color[0] = light.color[0];
	render->lights[lightIndex].color[1] = light.color[1];
	render->lights[lightIndex].color[2] = light.color[2];

	return GZ_SUCCESS;
}


int GzPutAttribute(GzRender	*render, int numAttributes, GzToken	*nameList, 
	GzPointer	*valueList) /* void** valuelist */
{
/*
- set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
- later set shaders, interpolaters, texture maps, and lights
*/
	if (!render->open)
		return GZ_FAILURE;

	for (int i = 0; i < numAttributes; ++i)
	{
		switch(nameList[i])
		{
		case GZ_RGB_COLOR:
			render->flatcolor[0] = ((float*) valueList[i])[0];
			render->flatcolor[1] = ((float*) valueList[i])[1];
			render->flatcolor[2] = ((float*) valueList[i])[2];
			break;

		case GZ_INTERPOLATE:
			render->interp_mode = ((int*) valueList[i])[0];
			break;

		case GZ_DIRECTIONAL_LIGHT:
			if (render->numlights == MAX_LIGHTS)
				break;

			render->lights[render->numlights].direction[0] = ((float*) valueList[i])[0];
			render->lights[render->numlights].direction[1] = ((float*) valueList[i])[1];
			render->lights[render->numlights].direction[2] = ((float*) valueList[i])[2];

			render->lights[render->numlights].color[0] = ((float*) valueList[i])[3];
			render->lights[render->numlights].color[1] = ((float*) valueList[i])[4];
			render->lights[render->numlights].color[2] = ((float*) valueList[i])[5];

			render->numlights++;
			break;

		case GZ_AMBIENT_LIGHT:

			render->ambientlight.color[0] = ((float*) valueList[i])[3];
			render->ambientlight.color[1] = ((float*) valueList[i])[4];
			render->ambientlight.color[2] = ((float*) valueList[i])[5];
			break;

		case GZ_AMBIENT_COEFFICIENT:

			render->Ka[0] = ((float*) valueList[i])[0];
			render->Ka[1] = ((float*) valueList[i])[1];
			render->Ka[2] = ((float*) valueList[i])[2];
			break;

		case GZ_DIFFUSE_COEFFICIENT:

			render->Kd[0] = ((float*) valueList[i])[0];
			render->Kd[1] = ((float*) valueList[i])[1];
			render->Kd[2] = ((float*) valueList[i])[2];
			break;

		case GZ_SPECULAR_COEFFICIENT:

			render->Ks[0] = ((float*) valueList[i])[0];
			render->Ks[1] = ((float*) valueList[i])[1];
			render->Ks[2] = ((float*) valueList[i])[2];
			break;

		case GZ_DISTRIBUTION_COEFFICIENT:

			render->spec = ((float*) valueList[i])[0];
			break;

		default:
			return GZ_FAILURE;
		}
	}
	
	return GZ_SUCCESS;
}

/* NOT part of API - just for general assistance */

short	ctoi(float color)		/* convert float color to GzIntensity short */
{
  return(short)((int)(color * ((1 << 12) - 1)));
}


int GzPutTriangle(GzRender	*render, int numParts, GzToken *nameList, 
				  GzPointer	*valueList)
/* numParts : how many names and values */
{
/*  
- pass in a triangle description with tokens and values corresponding to 
      GZ_POSITION:3 vert positions in model space 
- Xform positions of verts  
- Clip - just discard any triangle with verts behind view plane 
       - test for triangles with all three verts off-screen 
- invoke triangle rasterizer  
*/ 

	GzCoord* vertexList;
	GzCoord* normalList;

	for (int i = 0; i < numParts; ++i)
	{
		if (nameList[i] == GZ_NULL_TOKEN)
		{
			continue;
		}
		else if (nameList[i] == GZ_POSITION)
		{
			GzCoord* oldVertexList = (GzCoord*) valueList[i];
			vertexList = TransformVertices(oldVertexList, render->Xcum);
		}
		else if (nameList[i] == GZ_NORMAL)
		{
			GzCoord* oldNormalList = (GzCoord*) valueList[i];
			normalList = TransformVertices(oldNormalList, render->XcumNorm);
		}
		else
		{
			return GZ_FAILURE;
		}
	}

	Rectangle2D rect2D;
	GetMinBoundingBoxFromTriangle(vertexList, rect2D);

	Vector3D vec1(vertexList[0][0], vertexList[0][1] ,vertexList[0][2],
				vertexList[1][0], vertexList[1][1] ,vertexList[1][2]);
	Vector3D vec2(vertexList[1][0], vertexList[1][1] ,vertexList[1][2],
				vertexList[2][0], vertexList[2][1] ,vertexList[2][2]);

	float a, b, c, d;
	CrossProduct(vec1, vec2, a, b, c);
	d = - (a * vertexList[0][0] + b * vertexList[0][1] + c * vertexList[0][2]);
	Plane3D plane(a, b, c, d);

	Line2D line1(vertexList[0][0], vertexList[0][1],
					vertexList[1][0], vertexList[1][1]);
	Line2D line2(vertexList[1][0], vertexList[1][1],
					vertexList[2][0], vertexList[2][1]);
	Line2D line3(vertexList[2][0], vertexList[2][1],
					vertexList[0][0], vertexList[0][1]);

	for (int j = 0; j < (int) ceil(rect2D.height); ++j)
	{
		for (int i = 0; i < (int) ceil(rect2D.width); ++i)
		{
			int x = (int) ceil(rect2D.topLeft.x) + i;
			int y = (int) ceil(rect2D.topLeft.y) + j;

			float value1 = line1.ValuePoint(x, y);
			float value2 = line2.ValuePoint(x, y);
			float value3 = line3.ValuePoint(x, y);

			if ((value1 < 0 && value2 < 0 && value3 < 0) ||
				(value1 > 0 && value2 > 0 && value3 > 0) ||
				(value1 == 0 || value2 == 0 || value3 == 0))
			{
				if (x==131 && y ==21)
				{
					int g=1;
				}
				float z = plane.GetZ(x, y);
				GzCoord point;
				point[0] = x;
				point[1] = y;
				point[2] = z;
				GzColor color;
				ComputeColorBasedOnShadingModel(render, vertexList, normalList, point, color);
				GzPutDisplay(render->display, x, y, ctoi(color[0]), ctoi(color[1]), ctoi(color[2]), 1.0, z);
			}
		}
	}

	return GZ_SUCCESS;
}
