#pragma once
#include "inc.h"
#include "Headers/submesh.h"

struct MeshCreateInfo {
	const char* filename;
	glm::mat4 preTransform;
	const char* mtlname;
};

class ObjMesh {
public:
	unsigned int VBO, VAO, vertexCount;

	bool hasTransparency = false;

	std::vector<SubMesh> submeshes;

	ObjMesh(MeshCreateInfo* createInfo);
	~ObjMesh();
};