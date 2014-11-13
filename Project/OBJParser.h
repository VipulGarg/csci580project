#ifndef _OBJPARSER_H_
#define _OBJPARSER_H_
#pragma warning(disable: 4786)

#include <vector>
#include <string>


using namespace std;

/* 
 * Class definition for vertices in (x,y,z) coordinates
 * Format in OBJ file: v x y z 
*/
class Vertex {
public:
	Vertex() {}
	Vertex(int num, double xx, double yy, double zz) : vertexNum(num), x(xx), y(yy), z(zz) {}

	int vertexNum; // Identification number of a vertex
	double x;
	double y;
	double z;
};

/*
 * Class definition for vertex normals
 * Format in OBJ file: vn x y z
 */
class VertexNormal {
public:
	VertexNormal() {}
	VertexNormal(int num, double xx, double yy, double zz) : vertexNormalNum(num), x(xx),
		y(yy), z(zz) {}

	int vertexNormalNum; // Identification number of a vertex normal
	double x;
	double y;
	double z;
};

/*
 * Class definition for vertex textures
 * Format in OBJ file: vt x y [z] --> z is optional
 */
class VertexTexture {
public:
	VertexTexture() {}
	VertexTexture(int num, double xx, double yy, double zz=-1.0) : vertexTextureNum(num), x(xx),
		y(yy), z(zz) {}

	int vertexTextureNum; // Identification number of a vertex texture
	double x;
	double y;
	double z;
};

/*
 * Class definition for polygons made from the verticies listed
 * Format in OBJ file: f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3] ... --> vt and vn are optional
 */
class Face {
public:
	class FaceVertex {
	public:
		FaceVertex() {}
		FaceVertex(int i, int j, int k) : v(i), vt(j), vn(k) {}
		int v;
		int vt; // "-1" means no value for vt
		int vn; // "-1" means no value for vn
	};

	int faceNum; // Identification number of a face
	vector<FaceVertex> faceVertices; // List of vertices forming a face
	char *color;  // Reference for a color entry in a mtl-type file
	
	Face() : color(NULL) {}
	Face(int num, char *faceColor) : faceNum(num), color(faceColor) {}
};

/*
 * Class definition for a OBJ-File parser
 */
class OBJParser {
	char *mtl; // Name of mtl-type file
	vector<Vertex> vertices;  // Array containing vertices resulting from parsing an obj file
	vector<VertexNormal> normals; // Array containing vertex normals resulting from parsing an obj file
    vector<VertexTexture> textures; // Array containing vertex textures resulting from parsing an obj file
	vector<Face> faces; // Array containing polygons resulting from parsing an obj files

public:

	OBJParser() : mtl(NULL) {} // Default Constructor
    void parse(char *fileName); // parsing function
	void getTokens(string&, string&, vector<string>&);

	Vertex getVertex(int vertexNum); // returns a vertex with an id of vertexNum
	VertexNormal getVertexNormal(int normalNum); // returns a vertex normal with an id of normalNum
	VertexTexture getVertexTexture(int textureNum); // returns a vertex texture with an id of textureNum
	Face getFace(int faceNum); // returns a polygon with an id of faceNum

	int getNumOfVertices() { return vertices.size();} // returns the total # of vertices
	int getNumOfNormals() { return normals.size();} // returns the total # of normals
	int getNumOfTextures() { return textures.size();} // returns the total # of textures
	int getNumOfFaces() { return faces.size(); } // returns the total # of polygons

	~OBJParser() {
		if(mtl) delete mtl;
	}
};

#endif
