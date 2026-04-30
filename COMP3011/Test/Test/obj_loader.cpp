#include "obj_loader.h"

//#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>

namespace obj_loader {




std::vector<float> load_model_from_file(const char* filename, glm::mat4 preTransform, const char* mtlfile) {
	std::vector<float> vertices;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	
	std::cout << "Loading model from: " << filename << std::endl;

	
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename, mtlfile))
	{
		throw std::runtime_error(warn + err);
	}
	
	std::cout << "No. of materials: " << materials.size() << std::endl;
	std::cout << "No. of shapes: " << shapes.size() << std::endl;

	for (const auto& shape : shapes)
	{
		for (const auto& index : shape.mesh.indices)
		{
			

			glm::vec4 pos =
			{
				(attrib.vertices[3 * index.vertex_index + 0]),
				(attrib.vertices[3 * index.vertex_index + 1]),
				(attrib.vertices[3 * index.vertex_index + 2]),
				1
			};
			
	
			pos = preTransform * pos;

			glm::vec3 nor =
			{
				attrib.normals[3 * index.normal_index + 0],
				attrib.normals[3 * index.normal_index + 1],
				attrib.normals[3 * index.normal_index + 2]
			};
			
			nor = glm::normalize(glm::mat3(preTransform) * nor);
			

			glm::vec2 texCoord = {
				0.0f,0.0f
			};

			if (index.texcoord_index >= 0 && (2 * index.texcoord_index + 1) < attrib.texcoords.size()) {
				texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				attrib.texcoords[2 * index.texcoord_index + 1]
				};
			}

			


			vertices.push_back(pos.x);
			vertices.push_back(pos.y);
			vertices.push_back(pos.z);
			vertices.push_back(texCoord.x);
			vertices.push_back(texCoord.y);
			vertices.push_back(nor.x);
			vertices.push_back(nor.y);
			vertices.push_back(nor.z);
			
		}
	}
	
	return vertices;

}
}