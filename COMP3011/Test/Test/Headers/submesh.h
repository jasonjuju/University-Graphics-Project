#pragma once
#include <vector>
#include "../inc.h"


#include <string>



	struct Material {
		std::string name;
		std::string diffuse_texname;
		glm::vec3 diffuse;
		//Work with alpha channels if possible
		bool isTransparent = false;
	};
	struct SubMesh {
		std::vector<float> vertices;
		Material material;
		GLuint VAO;
		GLuint VBO;
		int vertexCount;
		GLuint texture;
	};

