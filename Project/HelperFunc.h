#include "Gz.h"

void MultiplyTwoMatrices(GzMatrix mat1, GzMatrix mat2, GzMatrix mat)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			float sum = 0;
			for (int k = 0; k < 4; ++k)
			{
				sum += mat1[i][k] * mat2[k][j];
			}
			mat[i][j] = sum;
		}
	}
}


void MultiplyMatrixAndHomCord(GzMatrix mat, GzHomCoord homCoord, GzCoord &returnCoord)
{
	GzHomCoord val;

	for (int i = 0; i < 4; ++i)
	{
		float sum = 0;
		for (int j = 0; j < 4; ++j)
		{
			sum += mat[i][j] * homCoord[j];
		}
		val[i] = sum;
	}

	for (int i = 0; i < 3; ++i)
	{
		returnCoord[i] = val[i] / val[3];
	}
}


GzCoord* TransformVertices(GzCoord* vertexList, GzMatrix mat)
{
	GzCoord *xFormedList = new GzCoord[3];

	for (int i = 0; i < 3; ++i)
	{
		GzHomCoord coord;
		for (int j = 0; j < 3; ++j)
		{
			coord[j] = vertexList[i][j];
		}
		coord[3] = 1;

		MultiplyMatrixAndHomCord(mat, coord, xFormedList[i]);
	}

	return xFormedList;
}


