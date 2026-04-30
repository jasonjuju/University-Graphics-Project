#pragma once
#include "Object.h"
#include "inc.h"
#include "texture.h"




Object::Object(const char* modelPath, const char* mtlPath) 
	: MODEL_PATH(modelPath), MTL_PATH(mtlPath) {

	std::cout << "BEFORE ANYTHING\n";

	pos = glm::vec3(0);
	scale = glm::vec3(1);
	rotation = 0;

	

	MeshCreateInfo createInfo;

	createInfo.filename = MODEL_PATH;
	createInfo.preTransform = glm::mat4(1.0);
	createInfo.mtlname = MTL_PATH;

	std::cout << "BEFORE MESH\n";

	objMesh = new ObjMesh(&createInfo);


	SetUpTextures();


}

	Object::~Object() {
		delete objMesh;
	}


	void Object::DrawObject(GLuint program) {

		glm::mat4 model = glm::mat4(1.f);

		
		model = glm::translate(model, pos);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 1, 0));
		model = glm::scale(model, this->GetScale());
		
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

		

		glDepthMask(GL_TRUE);
		//glDisable(GL_BLEND);


		for (SubMesh& submesh : objMesh->submeshes) {
			
			if (submesh.material.isTransparent) {
				continue;
			}

			GLuint texLocation = glGetUniformLocation(program, "texture1");


			if (texLocation != -1) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, submesh.texture);
				glUniform1i(texLocation, 0);
			}
			

			glBindVertexArray(submesh.VAO);
			glDrawArrays(GL_TRIANGLES, 0, submesh.vertexCount);
		}



		

		//For each submesh
		//	get texture name, VAO, VBO
	}

	void Object::DrawTransparentObject(GLuint program) {


		glm::mat4 model = glm::mat4(1.f);


		model = glm::translate(model, pos);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 1, 0));
		model = glm::scale(model, this->GetScale());

		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));


		glEnable(GL_BLEND);
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (auto& submesh : objMesh->submeshes) {
			if (!submesh.material.isTransparent) {
				continue;
			}


			GLuint texLocation = glGetUniformLocation(program, "texture1");


			if (texLocation != -1) {
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, submesh.texture);
				glUniform1i(texLocation, 0);
			}


			glBindVertexArray(submesh.VAO);
			glDrawArrays(GL_TRIANGLES, 0, submesh.vertexCount);
		}


		glDepthMask(GL_TRUE);
		//glDisable(GL_BLEND);
	}

	void Object::SetUpTextures() {
		for (auto& submesh : objMesh->submeshes) {

			//convert to const char*
			std::string strPath = std::string(MTL_PATH) + submesh.material.diffuse_texname.data();
			const char* textPath = strPath.c_str();

			submesh.texture = setup_texture(textPath);
		}
	}

	void Object::SetRotation(float newRot) {
		rotation = newRot;
	}

	glm::vec3 Object::GetPosition() {
		return pos;
	}

	void Object::SetPosition(glm::vec3 newPos) {
		pos = newPos;
	}

	glm::vec3 Object::GetScale() {
		return scale;
	}

	void Object::SetScale(glm::vec3 newScale) {
		scale = newScale;
	}

	ObjMesh* Object::getMesh() {
		return objMesh;
	}

	float Object::GetRotation() {
		return rotation;
	}

	void Object::ChangeRotation(float change) {
		rotation += change;

		if (rotation >= 360.0f) {
			rotation = rotation -360;
		}
	}

	Object* Object::Clone() {
		Object* clone = new Object (*this);
		return clone;
	}
	


