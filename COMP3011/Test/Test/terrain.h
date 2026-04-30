#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "inc.h"
#endif

class Terrain
{
public:

	GLuint texture;

	std::vector<float> vertices;

	std::vector<GLuint> indices;

	int depth;
	int width = 20;
	//Texture


	Terrain();

	void SetupTerrain(int length);
	
	void GenerateTerrain(GLuint program);

	void SetWidth(int w) { width = w; }

protected:

};


