/*   CS580 HW   */
#include    "stdafx.h"  
#include	"Gz.h"
#include	"disp.h"


int GzNewFrameBuffer(unsigned char** framebuffer, int width, int height)
{
/* create a framebuffer:
 -- allocate memory for framebuffer : (sizeof)GzPixel x width x height
 -- pass back pointer 
*/
	if (width < 0 || width > MAXXRES)
		return GZ_FAILURE;

	if (height < 0 || height > MAXYRES)
		return GZ_FAILURE;

	*framebuffer = new unsigned char[(sizeof(GzPixel)) * width * height];

	return GZ_SUCCESS;
}


int GzNewFloatArray(float** framebuffer, int width, int height)
{
/* create a framebuffer:
 -- allocate memory for framebuffer : (sizeof)GzPixel x width x height
 -- pass back pointer 
*/
	if (width < 0 || width > MAXXRES)
		return GZ_FAILURE;

	if (height < 0 || height > MAXYRES)
		return GZ_FAILURE;

	*framebuffer = new float[3 * width * height];

	return GZ_SUCCESS;
}


int GzNewDisplay(GzDisplay	**display, GzDisplayClass dispClass, int xRes, int yRes)
{

/* create a display:
  -- allocate memory for indicated class and resolution
  -- pass back pointer to GzDisplay object in display
*/

	// Check for correct range for xRes and yRes
	if (xRes < 0 || xRes > MAXXRES)
		return GZ_FAILURE;

	if (yRes < 0 || yRes > MAXYRES)
		return GZ_FAILURE;
	
	// Check for correct type of display class
	switch (dispClass)
	{
	case GZ_RGBAZ_DISPLAY:
		break;

	default:
		return GZ_FAILURE;
	}

	*display = new GzDisplay();
	(*display)->fbuf = new GzPixel[xRes * yRes];
	(*display)->xres = xRes;
	(*display)->yres = xRes;
	(*display)->dispClass = dispClass;
	(*display)->open = 1;

	return GZ_SUCCESS;
}


int GzFreeDisplay(GzDisplay	*display)
{
/* clean up, free memory */
	if (!display->open)
		return GZ_FAILURE;

	delete[] display->fbuf;
	delete[] display;
	return GZ_SUCCESS;
}


int GzGetDisplayParams(GzDisplay *display, int *xRes, int *yRes, GzDisplayClass	*dispClass)
{
/* pass back values for an open display */
	if (!display->open)
		return GZ_FAILURE;

	*xRes = display->xres;
	*yRes = display->yres;
	*dispClass = display->dispClass;

	return GZ_SUCCESS;
}


int GzInitDisplay(GzDisplay	*display)
{
/* set everything to some default values - start a new frame */
	if (!display->open)
		return GZ_FAILURE;

	for (int y = 0; y < display->yres; ++y)
	{
		for (int x = 0; x < display->xres; ++x)
		{
			int index = ARRAY(x,y);
			display->fbuf[index].alpha = 1;
			display->fbuf[index].red = 255 << 4;
			display->fbuf[index].green = 255 << 4;
			display->fbuf[index].blue = 255 << 4;
			display->fbuf[index].z = INT_MAX;
		}
	}
	return GZ_SUCCESS;
}


void static GzClampValues(GzIntensity& val)
{
	if (val < 0)
		val = 0;

	if (val > 4095)
		val = 4095;
}


int GzPutDisplay(GzDisplay *display, int i, int j, GzIntensity r, GzIntensity g, GzIntensity b, GzIntensity a, GzDepth z)
{
/* write pixel values into the display */
	if (!display->open)
		return GZ_FAILURE;

	if (i < 0 || i >= display->xres || j < 0 || j >= display->yres)
		return GZ_FAILURE;

	GzClampValues(r);
	GzClampValues(g);
	GzClampValues(b);
	GzClampValues(a);

	int index = ARRAY(i,j);
	if  (z > display->fbuf[index].z)
		return GZ_FAILURE;

	display->fbuf[index].alpha = a;
	display->fbuf[index].red = r;
	display->fbuf[index].green = g;
	display->fbuf[index].blue = b;
	display->fbuf[index].z = z;

	return GZ_SUCCESS;
}


int GzGetDisplay(GzDisplay *display, int i, int j, GzIntensity *r, GzIntensity *g, GzIntensity *b, GzIntensity *a, GzDepth *z)
{
	/* pass back pixel value in the display */
	/* check display class to see what vars are valid */
	if (!display->open)
		return GZ_FAILURE;

	if (i >= display->xres || j >= display->yres)
		return GZ_FAILURE;

	

	switch (display->dispClass)
	{
	case(GZ_RGBAZ_DISPLAY):
	{
		int index = ARRAY(i,j);
		*r = display->fbuf[index].red;
		*g = display->fbuf[index].green;
		*b = display->fbuf[index].blue;
		*a = display->fbuf[index].alpha;
		*z = display->fbuf[index].z;
		break;
	}

	default:
		return GZ_FAILURE;
	}

	return GZ_SUCCESS;
}


int GzFlushDisplay2File(FILE* outfile, GzDisplay *display)
{

	/* write pixels to ppm file based on display class -- "P6 %d %d 255\r" */
	if (!display->open)
		return GZ_FAILURE;

	fprintf(outfile, "P6 %d %d 255\r", display->xres, display->yres);
	for (int y = 0; y < display->yres; ++y)
	{
		for (int x = 0; x < display->xres; ++x)
		{
			unsigned char c[1];
			int index = ARRAY(x,y);
			c[0] = display->fbuf[index].red >> 4;
			fwrite(c, 1, 1, outfile);
			c[0] = display->fbuf[index].green >> 4;
			fwrite(c, 1, 1, outfile);
			c[0] = display->fbuf[index].blue >> 4;
			fwrite(c, 1, 1, outfile);
		}
	}

	return GZ_SUCCESS;
}


int GzFlushDisplay2FrameBuffer(unsigned char* framebuffer, GzDisplay *display)
{

	/* write pixels to framebuffer: 
		- Put the pixels into the frame buffer
		- Caution: store the pixel to the frame buffer as the order of blue, green, and red 
		- Not red, green, and blue !!!
	*/
	if (!display->open)
		return GZ_FAILURE;

	for (int y = 0; y < display->yres; ++y)
	{
		for (int x = 0; x < display->xres; ++x)
		{
			if (x == 4 && y == 4)
			{
				int g = 1;
			}
			int fbufIndex = ARRAY(x,y);
			int framebufferIndex = 3 * x + (y * display->xres * 3);
			framebuffer[framebufferIndex] = display->fbuf[fbufIndex].blue >> 4;
			framebuffer[framebufferIndex + 1] = display->fbuf[fbufIndex].green >> 4;
			framebuffer[framebufferIndex + 2] = display->fbuf[fbufIndex].red >> 4;
		}
	}

	return GZ_SUCCESS;
}
