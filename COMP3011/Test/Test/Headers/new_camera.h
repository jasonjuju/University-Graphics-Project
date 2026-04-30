#pragma once
#ifndef NEW_CAM_CLASS
#define NEW_CAM_CLASS
#define GLM_ENABLE_EXPERIMENTAL


#include "../inc.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class NewCamera {
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	bool firstClick = true;

	int width;
	int height;

	float speed = 0.2f;
	float sensitivity = 100.0f;


	NewCamera(int width, int height, glm::vec3 position);

	void Matrix(float FOVdeg, float nearPlane, float farPlane, GLuint program, const char* uniform); // missing , Shader& shader,
	void Inputs(GLFWwindow* window);

};
#endif