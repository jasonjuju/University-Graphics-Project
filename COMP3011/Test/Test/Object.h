#pragma once
#include "obj_mesh.h"
#include "Object.h"




class Object {



	ObjMesh* objMesh;

	glm::vec3 pos;

	glm::vec3 scale;

	float rotation;

	const char* MODEL_PATH;
	const char* TEXTURE_PATH;
	const char* MTL_PATH;

public:

	Object(const char* modelPath, const char* mtlPath);

	~Object();
	void DrawObject(GLuint program);

	void DrawTransparentObject(GLuint program);



	void SetUpTextures();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 newPos);

	glm::vec3 GetScale();

	void SetScale(glm::vec3 newScale);

	ObjMesh* getMesh();

	GLuint GetTexture();

	void SetTexture();

	void SetRotation(float newRot);
	float GetRotation();
	void  ChangeRotation(float change);


	Object* Clone();


};