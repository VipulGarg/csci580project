#include "gz.h"

struct Point2D
{
	Point2D() : x(0), y(0) {};

	float x;
	float y;
};


struct Rectangle2D
{
	Rectangle2D() : width(0), height(0) {};

	Point2D topLeft;
	float width;
	float height;
};


// In the form of ax + by + c = 0;
struct Line2D
{
	Line2D(float x1, float y1, float x2, float y2)
	{
		a = y1 - y2;
		b = x2 - x1;
		c = x1 * y2 - x2 * y1;
	};

	float a;
	float b;
	float c;

	float ValuePoint(float x, float y)
	{
		return a * x + b * y + c;
	}
};


struct Vector3D
{
	Vector3D(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		x = x2 - x1;
		y = y2 - y1;
		z = z2 - z1;
	};

	Vector3D(float x, float y, float z) : x(x), y(y), z(z) {};

	float x;
	float y;
	float z;

	void normalizeVector()
	{
		float mag = sqrt(x * x + y * y + z * z);
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
};


struct Plane3D
{
	Plane3D(float a, float b, float c, float d):
		a(a),
		b(b),
		c(c),
		d(d)
	{};

	float a;
	float b;
	float c;
	float d;

	float GetZ(float x, float y)
	{
		if (c == 0)
			return 0;

		return ( -d - a * x - b * y) / c;
	}
};


void CrossProduct(Vector3D& v1, Vector3D& v2, float& a, float& b, float& c)
{
	a = v1.y * v2.z - v1.z * v2.y;
	b = v1.z * v2.x - v1.x * v2.z;
	c = v1.x * v2.y - v1.y * v2.x;
}


void GetMinBoundingBoxFromTriangle(GzCoord* vertexList, Rectangle2D& rect2D)
{
	float min_x = min(min(vertexList[0][0], vertexList[1][0]), vertexList[2][0]);
	float max_x = max(max(vertexList[0][0], vertexList[1][0]), vertexList[2][0]);
	float min_y = min(min(vertexList[0][1], vertexList[1][1]), vertexList[2][1]);
	float max_y = max(max(vertexList[0][1], vertexList[1][1]), vertexList[2][1]);

	rect2D.topLeft.x = min_x;
	rect2D.topLeft.y = min_y;

	rect2D.height = max_y - min_y;
	rect2D.width = max_x - min_x;
}
