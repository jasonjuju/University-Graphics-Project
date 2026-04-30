#pragma once

#include "obj_mesh.h"
#include "mtl_obj_loader.h"
#include <iostream>

ObjMesh::ObjMesh(MeshCreateInfo* createInfo) {

	vertexCount = 0;


	//std::vector<float> vertices = 
	submeshes = mtl_obj_loader::load_model_from_file(createInfo->filename, createInfo->preTransform, createInfo->mtlname);
	

	//For each submesh:

	for (SubMesh& submesh : submeshes) {
		std::vector<float> vertices = submesh.vertices;



		submesh.vertexCount = int(vertices.size()) / 8;
		 
		if (vertices.empty()) {
			std::cerr << "Error: Submesh has no vertices. Skipping buffer creation\n";
			continue;
		}

		glCreateBuffers(1, &VBO);


		glCreateVertexArrays(1, &VAO);
		glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
		glNamedBufferStorage(VBO, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

		glEnableVertexArrayAttrib(VAO, 0);
		glEnableVertexArrayAttrib(VAO, 1);
		glEnableVertexArrayAttrib(VAO, 2);

		glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

		glVertexArrayAttribBinding(VAO, 0, 0);
		glVertexArrayAttribBinding(VAO, 1, 0);
		glVertexArrayAttribBinding(VAO, 2, 0);

		submesh.VAO = VAO;
		submesh.VBO = VBO;

		if (submesh.material.isTransparent) {
			hasTransparency = true;
		}
	}

	
	
	
}

ObjMesh::~ObjMesh() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}