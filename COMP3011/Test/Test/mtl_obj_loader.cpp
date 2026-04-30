#include "mtl_obj_loader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>
#include <unordered_map>


//Maybe move files?


namespace mtl_obj_loader {


	

	std::vector<SubMesh> load_model_from_file(const char* filename, glm::mat4 preTransform, const char* mtlfile) {

		std::unordered_map<int, SubMesh> submeshes;

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

		bool hasNor = !attrib.normals.empty();

		std::cout << "No. of materials: " << materials.size() << std::endl;
		std::cout << "No. of shapes: " << shapes.size() << std::endl;
		
		std::vector<glm::vec3> generatedNormals(attrib.vertices.size() / 3, glm::vec3(0.0f));
		//Generate normals if missing

		if (!hasNor) {
			std::cout << "NOR EMPTY: GENERATING NOR\n";


			for (int i = 0; i < shapes.size(); ++i)
			{
				int index_offset = 0;
				const auto& mesh = shapes[i].mesh;
				for (int j = 0; j < mesh.num_face_vertices.size(); ++j)
				{
					int faceVerts = mesh.num_face_vertices[j];

					tinyobj::index_t i0 = shapes[i].mesh.indices[index_offset + 0];
					tinyobj::index_t i1 = shapes[i].mesh.indices[index_offset + 1];
					tinyobj::index_t i2 = shapes[i].mesh.indices[index_offset + 2];


					glm::vec3 v0 = {
						attrib.vertices[3*i0.vertex_index +0],
						attrib.vertices[3 * i0.vertex_index + 1],
						attrib.vertices[3 * i0.vertex_index + 2]
					};
					glm::vec3 v1 = {
						attrib.vertices[3 * i1.vertex_index + 0],
						attrib.vertices[3 * i1.vertex_index + 1],
						attrib.vertices[3 * i1.vertex_index + 2]
					};
					glm::vec3 v2 = {
						attrib.vertices[3 * i2.vertex_index + 0],
						attrib.vertices[3 * i2.vertex_index + 1],
						attrib.vertices[3 * i2.vertex_index + 2]
					};

					glm::vec3 faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));

					generatedNormals[i0.vertex_index] += faceNormal;
					generatedNormals[i1.vertex_index] += faceNormal;
					generatedNormals[i2.vertex_index] += faceNormal;

					index_offset += faceVerts;
				}
			}
			for (auto& n : generatedNormals) {
				n = glm::normalize(n);
			}
		}

		//

		for (int i = 0; i < shapes.size(); ++i)
		{
			
			int index_offset = 0;
			const auto& mesh = shapes[i].mesh;

			

			for (int j = 0; j < mesh.num_face_vertices.size(); ++j)
			{
				
				int faceVerts = mesh.num_face_vertices[j];
				int matID = mesh.material_ids[j];


				//check if material is currently in submeshes
				if (submeshes.find(matID) == submeshes.end())
				{
					Material newMat;

					//if material is a valid id
					if (matID >= 0 && matID < materials.size()) {
						
						newMat.name = materials[matID].name;
						newMat.diffuse_texname = materials[matID].diffuse_texname;

						std::cout << "Loaded Material: " << newMat.diffuse_texname << std::endl;

						

						newMat.diffuse = glm::vec3(
							materials[matID].diffuse[0],
							materials[matID].diffuse[1],
							materials[matID].diffuse[2]
						);

						if (materials[matID].dissolve < 1.0f) {

							std::cout << "TESTEITER" << materials[matID].dissolve << " \n";
							std::cout << "TESTEITER" << materials[matID].dissolve << " \n";
							newMat.isTransparent = true;
						}

						submeshes[matID] = SubMesh{ {}, newMat };

						
					}
				}
				
				

				for (int ind = 0; ind < faceVerts; ++ind) {


					tinyobj::index_t index = mesh.indices[index_offset + ind];

					glm::vec4 pos =
					{
						(attrib.vertices[3 * index.vertex_index + 0]),
						(attrib.vertices[3 * index.vertex_index + 1]),
						(attrib.vertices[3 * index.vertex_index + 2]),
						1
					};


					pos = preTransform * pos;


					glm::vec3 nor = { 0.0,0.0,0.0 };


					if (index.normal_index >= 0 && (3 * index.normal_index + 2) < attrib.normals.size()) {
						
						nor = {
							attrib.normals[3 * index.normal_index + 0],
							attrib.normals[3 * index.normal_index + 1],
							attrib.normals[3 * index.normal_index + 2]
						};
					}
					else if (!hasNor) {
						nor = generatedNormals[index.vertex_index];
					}
					

					

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

					std::vector<float>& vertices = submeshes[matID].vertices;

					vertices.push_back(pos.x);
					vertices.push_back(pos.y);
					vertices.push_back(pos.z);
					vertices.push_back(texCoord.x);
					vertices.push_back(texCoord.y);
					vertices.push_back(nor.x);
					vertices.push_back(nor.y);
					vertices.push_back(nor.z);
				}

				index_offset += faceVerts;

			}
		}

		std::vector<SubMesh> finalList;

		//Get submeshes from unordered map
		for (auto& submesh : submeshes) {
			finalList.push_back(std::move(submesh.second));
		}

		return finalList;



	}
}