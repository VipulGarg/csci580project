#include "gz.h"
#include "rend.h"
#include <math.h>

void NormalizeGzCoord(GzCoord cord)
{
	float mag = sqrt(cord[0] * cord[0] + cord[1] * cord[1] + cord[2] * cord[2]);
	cord[0] = cord[0] / mag;
	cord[1] = cord[1] / mag;
	cord[2] = cord[2] / mag;
}

void ComputeColor(GzRender* render, GzCoord normal, GzColor color)
{
	GzCoord E;
	E[0] = 0;
	E[1] = 0;
	E[2] = -1;

	NormalizeGzCoord(E);
	NormalizeGzCoord(normal);

	color[0] = 0;
	color[1] = 0;
	color[2] = 0;;

	float ndote = normal[0] * E[0] + normal[1] * E[1] + normal[2] * E[2];

	for (int i = 0; i < render->numlights; ++i)
	{
		float ndotl = normal[0] * render->lights[i].direction[0] + 
						normal[1] * render->lights[i].direction[1] + 
							normal[2] * render->lights[i].direction[2];

		if (ndotl * ndote < 0)
			continue;

		if (ndotl < 0 && ndote < 0)
		{
			ndotl = -ndotl;
			ndote = -ndote;
			normal[0] = -normal[0];
			normal[1] = -normal[1];
			normal[2] = -normal[2];
		}

		GzCoord R;
		R[0] = 2 * ndotl * normal[0] - render->lights[i].direction[0];
		R[1] = 2 * ndotl * normal[1] - render->lights[i].direction[1];
		R[2] = 2 * ndotl * normal[2] - render->lights[i].direction[2];
		NormalizeGzCoord(R);

		float rdote = R[0] * E[0] + R[1] * E[1] + R[2] * E[2];
		if (rdote < 0)
			rdote = 0;
		if (rdote > 1)
			rdote = 1;

		for (int k = 0; k < 3; ++k)
		{
			color[k] += (render->lights[i].color[k] * pow(rdote, render->spec)) * render->Ks[k] +
							(render->lights[i].color[k] * ndotl) * render->Kd[k];
		}
	}

	color[0] += render->Ka[0] * render->ambientlight.color[0];
	color[1] += render->Ka[1] * render->ambientlight.color[1];
	color[2] += render->Ka[2] * render->ambientlight.color[2];
}


float AreaOfTriangle(GzCoord verta, GzCoord vertb, GzCoord vertc)
{
	float area = abs(0.5 * (verta[0] * (vertb[1] - vertc[1]) + vertb[0] * (vertc[1] - verta[1]) + vertc[0] * (verta[1] - vertb[1])));
	return area;
}


void CalculateInterpRatios(GzCoord* vertexList, GzCoord point, GzCoord ratios)
{
	float ratio1 = AreaOfTriangle(vertexList[1], point, vertexList[2]);
	float ratio2 = AreaOfTriangle(vertexList[2], point, vertexList[0]);
	float ratio3 = AreaOfTriangle(vertexList[0], point, vertexList[1]);

	float sum = ratio1 + ratio2 + ratio3;

	ratios[0] = ratio1 / sum;
	ratios[1] = ratio2 / sum;
	ratios[2] = ratio3 / sum;
}


void ComputeColorBasedOnShadingModel(GzRender* render, GzCoord* vertexList, GzCoord* normalList, GzCoord point, GzColor color)
{
	if (render->interp_mode == GZ_COLOR)
	{
		GzColor color1, color2, color3;
		ComputeColor(render, normalList[0], color1);
		ComputeColor(render, normalList[1], color2);
		ComputeColor(render, normalList[2], color3);

		GzCoord ratios;
		CalculateInterpRatios(vertexList, point, ratios);

		for (int k = 0; k < 3; ++k)
		{
			color[k] = ratios[0] * color1[k] + ratios[1] * color2[k] + ratios[2] * color3[k];
		}
	}
	else if (render->interp_mode == GZ_NORMALS)
	{
		GzCoord ratios;
		CalculateInterpRatios(vertexList, point, ratios);

		GzCoord normalInterp;
		for (int k = 0; k < 3; ++k)
		{
			normalInterp[k] = ratios[0] * normalList[0][k] + ratios[1] * normalList[1][k] + ratios[2] * normalList[2][k];
		}

		ComputeColor(render, normalInterp, color);
	}
	else
	{
		ComputeColor(render, normalList[0], color);
	}

	for (int k = 0; k < 3; ++k)
	{
		if (color[k] < 0)
			color[k] = 0;
		if (color[k] > 1)
			color[k] = 1;
	}
}

