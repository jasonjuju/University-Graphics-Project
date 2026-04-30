#pragma once
#include "Object.h"
#include"light_source.h"
#include"Headers/new_camera.h"
class RcCar
{

	Object* object;

	LightSource* headlight1;
	LightSource* headlight2;

	float speed = 0.1f;

	glm::vec3 front = glm::vec3(-1.0f, 0.0f, 0.0f);

	glm::vec3 lightOffset = glm::vec3(-0.8f,0.0f,0.0f);

	glm::vec3 headlightOffset = glm::vec3(0.0f, 0.0f, 0.35f);

	glm::vec3 cameraOffset = glm::vec3(-0.33f, 0.25f, 0.0f);


	NewCamera* rcCamera;

public:
	//define object
	RcCar(std::vector<Object*>* objects, std::vector<LightSource*>* lights, NewCamera* c);

	void moveForward();

	void turnRight();

	void turnLeft();

	void moveBackward();

	glm::vec3 getFront() { return front; }

	glm::vec3 getLightPos();

	void update();

};

