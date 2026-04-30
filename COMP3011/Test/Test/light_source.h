#pragma once
#include "inc.h"





class LightSource {
public:
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 lightCol = glm::vec3(1.0f,1.0f,1.0f); 

	int lightType = 0;

	//Direction?

	LightSource(glm::vec3 pos, glm::vec3 col);

	void SetPosition(glm::vec3 newPos);

	void SetType(int newType);


};