// PaperTexture.h: implementation of the PaperTexture class.
//
//////////////////////////////////////////////////////////////////////

//---------------------D&L-----------------------
#ifndef _PaperTexture_H_
#define _PaperTexture_H_

#include <math.h>
#include <float.h>
#include <stdlib.h>

struct color
{
	//v[0]=red, v[1]=green, v[2]=blue
	unsigned char v[3];	
	color(unsigned char r, unsigned char g, unsigned char b)
	{
		v[0]=r;
		v[1]=g;
		v[2]=b;
	}
};

/********************************************SIZE DEFINITIONS***/
const unsigned hgrid = 256,//x dimension of the grid (can be anything >= 1)
			   vgrid = hgrid;//y dimension of the grid (can be anything >= 1 (hgrid and vgrid can differ); I only do this to make a square image)

/*********************************************SEED DEFINITION***/
int permutation[256];

/*****************************************FUNCTION PROTOTYPES***/
int ranInt();
float random(int x, int y, int z);
color lerp(color c1, color c2, float value);//LERP = Linear intERPolation

void fillMap(float map[][vgrid], float &min, float &max);// this is the algorithm part (the interesting part)
void printMap(unsigned char* pPaperTexture, float map[][vgrid], float min, float max);//bitmap part

float smoothedNoise(float x,float y);

float smoothedNoise_euclideanSquared(float x,float y);
float smoothedNoise_manhattan(float x,float y);
float smoothedNoise_chebychev(float x,float y);
float smoothedNoise_quadratic(float x,float y);

float euclideanSquared(float x1, float y1, float x2, float y2);
float manhattan(float x1, float y1, float x2, float y2);
float chebychev(float x1, float y1, float x2, float y2);
float quadratic(float x1, float y1, float x2, float y2);

void generatePaperTexture(unsigned char* pPaperTexture);

color lerp(color c1, color c2, float value)
{
	color tcolor(0,0,0);
	
	for (int g=0;g<3;g++)
	{
		if (c1.v[g]>c2.v[g])
		{
			tcolor.v[g]=c2.v[g]+(unsigned char)(float(c1.v[g]-c2.v[g])*value);
		}
		else
		{
			tcolor.v[g]=c1.v[g]+(unsigned char)(float(c2.v[g]-c1.v[g])*value);
		}

		if (tcolor.v[g] < 0)
		{
			tcolor.v[g] = 0;
		}

		if (tcolor.v[g] > 255)
		{
			tcolor.v[g] = 255;
		}
	}
	return (tcolor);
}

void fillMap(float map[][vgrid], float &min, float &max)
{
	//set up some variables
	int	i,//iterator
		x,y,//location variables
		octaves = 8;//octaves (levels of detail or number of passes)
	
	float gain = 1.0f, //modifier for the amplitude
		  lacunarity = 2.0f, //modifier for the frequency
		  total, frequency, amplitude, offset; //used for calculations
	
	min=10000.0f;
	max=0.0f;//for averaging
	
	//get started
	for (x = 0; x < hgrid; ++x)
	{
		for (y = 0; y < vgrid; ++y)
		{
			//for each pixel, get the value
			total = 0.0f;
			frequency = 1.0f/(float)hgrid;
			amplitude = 1.0f;
			
			for (i = 0; i < octaves; ++i)
			{
				offset = (float)i * 7.0f;//this is just to add variance between layers

				total += smoothedNoise_euclideanSquared((float)x * frequency + offset, (float)y * frequency + offset) * amplitude;
				total += smoothedNoise_chebychev((float)x * frequency + offset, (float)y * frequency + offset) * amplitude;
				
				frequency *= lacunarity;
				amplitude *= gain;
			}
			
			//now that we have the value, put it in
			map[x][y] = total;
			
			//just do some minor calculations while we're here anyway
			if (total<min)
				min = total;
			if (total>max)
				max = total;
		}
	}
}

float random(int x, int y, int z)
{
	int r1 = permutation[(x + permutation[(y + permutation[z & 255]) & 255]) & 255];
	return((float)r1/256.0f);
}

int ranInt()
{
	int r;
	r=rand();
    return (r&255);
}

float smoothedNoise(float x, float y)
{
	int	int_x = (int)x,
		int_y = (int)y,
		i,j, tempx,tempy;

	float	frac_x = x - (float)int_x,
			frac_y = y - (float)int_y,
			points[3][3][2],
			temp_dis,
			distance1,distance2;
	
	//get the point inside the current square, and the point inside the 8 surrounding squares
	for (i = 0;i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			tempx = int_x + i - 1;
			tempy = int_y + j - 1;
			points[i][j][0] = tempx + random(tempx, tempy, 1);
			points[i][j][1] = tempy + random(tempx, tempy, 2);
		}
	}
	
	//get the distance to the closest point from x, y
	distance1 = distance2 = FLT_MAX;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = manhattan(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = chebychev(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = quadratic(x,y,points[i][j][0],points[i][j][1]);
			
			
			if (temp_dis < distance1)
			{
				if (distance1 < distance2)
				{
					distance2 = distance1;
				}
				distance1 = temp_dis;
			}
			else if (temp_dis < distance2)
			{
				distance2 = temp_dis;
			}
		}
	}
	return (1.0f - distance1);//this just inverts it
	//return (distance2);
}

float smoothedNoise_euclideanSquared(float x,float y)
{
	int	int_x = (int)x,
		int_y = (int)y,
		i,j, tempx,tempy;

	float	frac_x = x - (float)int_x,
			frac_y = y - (float)int_y,
			points[3][3][2],
			temp_dis,
			distance1,distance2;
	
	//get the point inside the current square, and the point inside the 8 surrounding squares
	for (i = 0;i<3;++i)
	{
		for (j = 0; j < 3; ++j)
		{
			tempx = int_x + i - 1;
			tempy = int_y + j - 1;
			points[i][j][0] = tempx + random(tempx, tempy, 1);
			points[i][j][1] = tempy + random(tempx, tempy, 2);
		}
	}
	
	//get the distance to the closest point from x, y
	distance1 = distance2 = FLT_MAX;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = manhattan(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = chebychev(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = quadratic(x,y,points[i][j][0],points[i][j][1]);
			
			
			if (temp_dis < distance1)
			{
				if (distance1 < distance2)
				{
					distance2 = distance1;
				}
				distance1 = temp_dis;
			}
			else if (temp_dis < distance2)
			{
				distance2 = temp_dis;
			}
		}
	}
	return (1.0f - distance1);//this just inverts it
	//return (distance2);
}

float smoothedNoise_manhattan(float x,float y)
{
	int	int_x = (int)x,
		int_y = (int)y,
		i,j, tempx,tempy;

	float	frac_x = x - (float)int_x,
			frac_y = y - (float)int_y,
			points[3][3][2],
			temp_dis,
			distance1,distance2;
	
	//get the point inside the current square, and the point inside the 8 surrounding squares
	for (i = 0;i<3;++i)
	{
		for (j = 0; j < 3; ++j)
		{
			tempx = int_x + i - 1;
			tempy = int_y + j - 1;
			points[i][j][0] = tempx + random(tempx, tempy, 1);
			points[i][j][1] = tempy + random(tempx, tempy, 2);
		}
	}
	
	//get the distance to the closest point from x, y
	distance1 = distance2 = FLT_MAX;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			temp_dis = manhattan(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = chebychev(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = quadratic(x,y,points[i][j][0],points[i][j][1]);
			
			
			if (temp_dis < distance1)
			{
				if (distance1 < distance2)
				{
					distance2 = distance1;
				}
				distance1 = temp_dis;
			}
			else if (temp_dis < distance2)
			{
				distance2 = temp_dis;
			}
		}
	}
	return (1.0f - distance1);//this just inverts it
	//return (distance2);
}
float smoothedNoise_chebychev(float x,float y)
{
	int	int_x = (int)x,
		int_y = (int)y,
		i,j, tempx,tempy;

	float	frac_x = x - (float)int_x,
			frac_y = y - (float)int_y,
			points[3][3][2],
			temp_dis,
			distance1,distance2;
	
	//get the point inside the current square, and the point inside the 8 surrounding squares
	for (i = 0;i<3;++i)
	{
		for (j = 0; j < 3; ++j)
		{
			tempx = int_x + i - 1;
			tempy = int_y + j - 1;
			points[i][j][0] = tempx + random(tempx, tempy, 1);
			points[i][j][1] = tempy + random(tempx, tempy, 2);
		}
	}
	
	//get the distance to the closest point from x, y
	distance1 = distance2 = FLT_MAX;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = manhattan(x,y,points[i][j][0],points[i][j][1]);
			temp_dis = chebychev(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = quadratic(x,y,points[i][j][0],points[i][j][1]);
			
			
			if (temp_dis < distance1)
			{
				if (distance1 < distance2)
				{
					distance2 = distance1;
				}
				distance1 = temp_dis;
			}
			else if (temp_dis < distance2)
			{
				distance2 = temp_dis;
			}
		}
	}
	return (1.0f - distance1);//this just inverts it
	//return (distance2);
}

float smoothedNoise_quadratic(float x,float y)
{
	int	int_x = (int)x,
		int_y = (int)y,
		i,j, tempx,tempy;

	float	frac_x = x - (float)int_x,
			frac_y = y - (float)int_y,
			points[3][3][2],
			temp_dis,
			distance1,distance2;
	
	//get the point inside the current square, and the point inside the 8 surrounding squares
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			tempx = int_x + i - 1;
			tempy = int_y + j - 1;
			points[i][j][0] = tempx + random(tempx, tempy, 1);
			points[i][j][1] = tempy + random(tempx, tempy, 2);
		}
	}
	
	//get the distance to the closest point from x, y
	distance1 = distance2 = FLT_MAX;
	
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 3; ++j)
		{
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = manhattan(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = chebychev(x,y,points[i][j][0],points[i][j][1]);
			//temp_dis = euclideanSquared(x,y,points[i][j][0],points[i][j][1]);
			temp_dis = quadratic(x,y,points[i][j][0],points[i][j][1]);
			
			
			if (temp_dis < distance1)
			{
				if (distance1 < distance2)
				{
					distance2 = distance1;
				}
				distance1 = temp_dis;
			}
			else if (temp_dis < distance2)
			{
				distance2 = temp_dis;
			}
		}
	}
	return (1.0f - distance1);//this just inverts it
	//return (distance2);
}

void printMap(unsigned char* pPaperTexture, float map[][vgrid], float min, float max)
{
//set up some variables
	float diff = max-min,
		  flood=0.0f,//flood level
		  mount=0.0f;//mountain level
	
	flood*=diff;
	mount*=diff;
	
	int i,j,k;
	
	//these can be changed for interesting results
	color //black(160,180,180),white(200,230,230);
		  black(0,20,20),white(70,90,90);
		
	//3.2 put in the elements of the array
	color newcolor(0,0,0);
	
	for (i = (vgrid-1); i >= 0; i--)
	{//bitmaps start with the bottom row, and work their way up...
		for (j = 0; j < hgrid; j++)
		{//...but still go left to right
			map[j][i] -= min;
			
			//uncomment the line below to make it black 'n' white
			newcolor = lerp(black,white,map[j][i]/diff);
			
			pPaperTexture[(j*vgrid + i) * 3] = (char(newcolor.v[2]));//blue
			pPaperTexture[(j*vgrid + i) * 3 + 1] = (char(newcolor.v[1]));//green
			pPaperTexture[(j*vgrid + i) * 3 + 2] = (char(newcolor.v[0]));//red
		}
	}
}

float euclideanSquared(float x1, float y1, float x2, float y2)
{
	float	dif_x = x1-x2,
			dif_y = y1-y2;

	return (dif_x * dif_x + dif_y * dif_y);
}

float manhattan(float x1, float y1, float x2, float y2)
{
	float	dif_x = x1 - x2,
			dif_y = y1 - y2;

	return (fabs(dif_x) + fabs(dif_y));
}

float chebychev(float x1, float y1, float x2, float y2)
{
	float	dif_x = fabs(x1 - x2),
			dif_y = fabs(y1 - y2);

	if (dif_x < dif_y)
		return (dif_x);
	else
		return (dif_y);

}

float quadratic(float x1, float y1, float x2, float y2)
{
	float	dif_x = x1 - x2,
			dif_y = y1 - y2;

	return (dif_x * dif_x + dif_x * dif_y + dif_y * dif_y);
}

void generatePaperTexture(unsigned char* pPaperTexture)
{
	int i,j,k;

	for (i = 0; i < 256; ++i)
		permutation[i]=i;

	for (i = 0; i < 256; ++i)
	{
		j=permutation[i];
		k=ranInt();
		permutation[i]=permutation[k];
		permutation[k]=j;
	}

	float map[hgrid][vgrid];//make the empty array
	
	float min,max;

	//now that the blank map is set up, unblank it
	fillMap(map, min, max);
	
	//now that we have an interesting map, create a .BMP file
	printMap(pPaperTexture, map, min, max);
	
}
#endif
//---------------------L&D-----------------------