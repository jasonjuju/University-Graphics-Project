#pragma once
#include "inc.h"
#include"Object.h"
class AnimatedCar
{

	Object* object;

	int currentPoint = 0;
	int totalPoints = 100;

	float speed = 0.1f;

	glm::vec3 front = glm::vec3(1.0f, 0.0f, 0.0f);

	int currentNode = 0;


	std::vector<glm::vec3> nodes = {
		glm::vec3(20, -0.15, 5),
		glm::vec3(30, -0.15, 15),
		glm::vec3(20, -0.15, 15),
		glm::vec3(10, -0.15, 15),
		glm::vec3(20, -0.15, 5),
		glm::vec3(30, -0.15, -5),
		glm::vec3(20, -0.15, -5),
		glm::vec3(10, -0.15, -5)
	};



	//glm::vec3 pointA, glm::vec3 pointB, glm::vec3 pointC, float currentPoint, float totalPoints

public:

	AnimatedCar(std::vector<Object*>* objects);

	void BezierCurve();
};

