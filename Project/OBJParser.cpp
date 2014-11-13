#pragma warning(disable: 4786)
#include <stdlib.h>
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "OBJParser.h"

#define EXPECTED_SIZE  20000

using namespace std;

void OBJParser::parse(char *fileName) {
	char buf[1024];
	char* stopString;
	char* faceColor=NULL;
	string line;
	string separators = " ";
	vector<string> tokenList;
	int vertexNum=1, normalNum=1, textureNum=1, faceNum=1;
	
	this->vertices.clear();
	this->normals.clear();
	this->textures.clear();
	this->faces.clear();

	this->vertices.reserve(EXPECTED_SIZE);
	this->normals.reserve(EXPECTED_SIZE);
	this->textures.reserve(EXPECTED_SIZE);
	this->faces.reserve(EXPECTED_SIZE);

	
	ifstream fin(fileName); // Open the OBJ file
	
	while(fin.getline(buf,1024)) {
	
		tokenList.clear();
		line = buf;
		
		if(line[0] == '#') continue;
		getTokens(line, separators, tokenList);
		if(tokenList.size() == 0) continue;
		string token = tokenList[0];
		if(token == "mtllib") {
			string mtlName = tokenList[1];
			this->mtl = (char *)malloc(sizeof(char)*(mtlName.size()+1));
			strcpy(mtl, mtlName.c_str());
		}
		else if(token == "v") {
			double x = strtod(tokenList[1].c_str(), &stopString);
			double y = strtod(tokenList[2].c_str(), &stopString);
			double z = strtod(tokenList[3].c_str(), &stopString);
			this->vertices.push_back(Vertex(vertexNum++, x, y, z));
		}
		else if(token == "vn") {
			double x = strtod(tokenList[1].c_str(), &stopString);
			double y = strtod(tokenList[2].c_str(), &stopString);
			double z = strtod(tokenList[3].c_str(), &stopString);
			this->normals.push_back(VertexNormal(normalNum++, x, y, z));
		}
		else if(token == "vt") {
			double x = strtod(tokenList[1].c_str(), &stopString);
			double y = strtod(tokenList[2].c_str(), &stopString);
			double z;
			if(tokenList.size() == 3)
				z = -1.0;
			else 
				z = strtod(tokenList[3].c_str(), &stopString);
			this->textures.push_back(VertexTexture(textureNum++, x, y, z));
		}
		else if(token == "usemtl") {
			faceColor = (char *) malloc(sizeof(char)*(tokenList[1].size()+1));
			strcpy(faceColor,tokenList[1].c_str());
		}
		else if(token == "f") {
			vector<string> vList;
			//char* color = (char *)malloc(sizeof(char)*(faceColor.size()+1));
			//strcpy(color,faceColor.c_str());
			Face face(faceNum++, faceColor);
	
			for(int i=1; i < tokenList.size(); i++) {
				string s = tokenList[i];
				vList.clear();
				string token("/");
				this->getTokens(s,token,vList);
				int idx = s.find("//");

				Face::FaceVertex fVertex;
				if(idx >= 0 && idx <= s.length()) {
					fVertex.v = atoi(vList[0].c_str());
					fVertex.vt = -1;
					fVertex.vn = atoi(vList[1].c_str());
				}
				else if(vList.size() == 1) {
					fVertex.v = atoi(vList[0].c_str());
					fVertex.vt = -1;
					fVertex.vn = -1;
				}
				else if(vList.size() == 2) {
					fVertex.v = atoi(vList[0].c_str());
					fVertex.vt = atoi(vList[1].c_str());
					fVertex.vn = -1;

				}
				else {
					fVertex.v = atoi(vList[0].c_str());
					fVertex.vt = atoi(vList[1].c_str());
					fVertex.vn = atoi(vList[2].c_str());
				}
				face.faceVertices.push_back(fVertex);
			}
			this->faces.push_back(face);
		}		
	}
	fin.close();
}

Vertex OBJParser::getVertex(int vertexNum) {
	return this->vertices[vertexNum-1];
}

VertexNormal OBJParser::getVertexNormal(int normalNum) {
	return this->normals[normalNum-1];
}

VertexTexture OBJParser::getVertexTexture(int textureNum) {
	return this->textures[textureNum-1];
}

Face OBJParser::getFace(int faceNum) {
	return this->faces[faceNum-1];
}

void OBJParser::getTokens(string& stmt, string& separators, vector<string>& token_list)
{
   int n = stmt.length();
   int start, stop;

   start = stmt.find_first_not_of(separators);
   while ((start >= 0) && (start < n)) {
      stop = stmt.find_first_of(separators, start);
      if ((stop < 0) || (stop > n)) stop = n;
      token_list.push_back(stmt.substr(start, stop - start));
      start = stmt.find_first_not_of(separators, stop+1);
   }
}

