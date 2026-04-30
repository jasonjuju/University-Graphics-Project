#pragma once
#include <GL/gl3w.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <algorithm>


#include "error.h"
#include "file.h"
#include "shader.h"

#include "Headers/new_camera.h"



#include"obj_mesh.h"

#include"light_source.h"


#include "Object.h"
#include <stb_image.h>

#include "street.h"

#include "rcCar.h"
#include"AnimatedCar.h"


#define NUM_BUFFERS 1
#define NUM_VAOS 1
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];

#define WIDTH 1024
#define HEIGHT 768

//EXTRA STUFF FROM ASSESSMENT 1
//const char* MODEL_PATH = "objs/cornell2/cornell-box.obj";
//const char* MODEL_PATH = "objs/source/single_room_building/single_room_building.obj";




std::vector<Object*> objects;
std::vector<LightSource*> lightSources;

RcCar* rcCar;


AnimatedCar* animatedCar;



//light direction variable here
//glm::vec3 lightDirection = glm::vec3(0.1f, -.8f, -.61f);
//glm::vec3 lightPos = glm::vec3(2.f, 6.f, 7.f);


const char* modelDir = "objs/source/";


NewCamera nCamera(WIDTH, HEIGHT, glm::vec3(0.0f,10.0f,2.0f));

NewCamera secondCamera(WIDTH, HEIGHT, glm::vec3(10.0f, 10.0f, 2.0f));

NewCamera* activeCamera;


float skyboxVertices[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f
};

unsigned int skyboxIndices[]{
	1,2,6,
	6,5,1,

	0,4,7,
	7,3,0,

	4,5,6,
	6,7,4,

	0,3,2,
	2,1,0,

	0,1,5,
	5,4,0,

	3,7,6,
	6,2,3
};



void processKeyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float x_offset = 0.f;
	float y_offset = 0.f;
	bool cam_changed = false;

	glm::vec3 testVec = glm::vec3(0.f, 0.f, 0.f);

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {

		x_offset = 1.f;
		y_offset = 0.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {

		x_offset = -1.f;
		y_offset = 0.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

		x_offset = 0.f;
		y_offset = 1.f;
		cam_changed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {

		x_offset = 0.f;
		y_offset = -1.f;
		cam_changed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		rcCar->moveForward();
	}

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		rcCar->moveBackward();
	}

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		rcCar->turnLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		rcCar->turnRight();

	}

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		std::cout << "WERE GOING \n";
		animatedCar->BezierCurve();

	}


	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		if (activeCamera != &nCamera) {
			activeCamera = &nCamera;
			
			
		}
		
		
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {

		if (activeCamera != &secondCamera) {
			activeCamera = &secondCamera;


		}

	}

}

void SizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

GLFWwindow* Initialise(int width, int height) {
	glfwInit();


	glfwWindowHint(GLFW_SAMPLES, 8);
	

	GLFWwindow* window = glfwCreateWindow(width, height, "Assessment2", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, SizeCallback);

	return window;
}

void SetLights(GLuint program) {


	glUniform1i(glGetUniformLocation(program, "numLights"), (GLuint)lightSources.size());


	for (int i = 0; i < lightSources.size(); ++i) {

		std::string colString = "lightColour[" + std::to_string(i) + "]";
		std::string posString = "lightPos[" + std::to_string(i) + "]";
		std::string typeString = "lightType[" + std::to_string(i) + "]";

		glUniform3f(glGetUniformLocation(program, colString.c_str()), lightSources[i]->lightCol.x, lightSources[i]->lightCol.y, lightSources[i]->lightCol.z);
		glUniform3f(glGetUniformLocation(program, posString.c_str()), lightSources[i]->lightPos.x, lightSources[i]->lightPos.y, lightSources[i]->lightPos.z);

		glUniform1i(glGetUniformLocation(program, typeString.c_str()), lightSources[i]->lightType);

		//**Change
		if (lightSources[i]->lightType == 1) {
			glUniform3f(glGetUniformLocation(program, "lightDirection"), rcCar->getFront().x, rcCar->getFront().y, rcCar->getFront().z);
		}

	}


}

void RenderModels(GLuint program) {


	std::vector<Object*> transObjects;
	

	glEnable(GL_DEPTH_TEST);
	for (Object* obj : objects) {

		obj->DrawObject(program);

		if (obj->getMesh()->hasTransparency) {
			transObjects.push_back(obj);
		}


		
	}

	//Sort objects with transparency based on distance from camera
	std::sort(transObjects.begin(), transObjects.end(),
		[&](Object* a, Object* b) {
			float distA = glm::length(nCamera.Position - a->GetPosition());
			float distB = glm::length(nCamera.Position - b->GetPosition());
			return distA > distB;
		});



	for (Object* obj : transObjects) {

		

		obj->DrawTransparentObject(program);


	}


}

void RenderShadows(GLuint program) {
	for (Object* obj : objects) {
		obj->DrawObject(program);
	}
}

int main(int argc, char** argv)
{

	activeCamera = &nCamera;

	GLFWwindow* window = Initialise(WIDTH, HEIGHT);

	

	gl3wInit();

	glEnable(GL_MULTISAMPLE);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(DebugCallback, 0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Street street(&objects, &lightSources);

	
	GLuint program = CompileShader("new.vert", "new.frag");

	GLuint skyboxShader = CompileShader("skybox.vert", "skybox.frag");

	//GLuint shadowShader = CompileShader("shadow.vert", "shadow.frag");
	


	rcCar = new RcCar(&objects, &lightSources, &secondCamera);

	animatedCar = new AnimatedCar(&objects);
	
	
	street.GenerateStreet(program, 20);



	
	
	
	
	//Skybox, maybe move to it's own file
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	std::string facesCubemap[6] = {
		"objs/skybox/posx.jpg",
		"objs/skybox/negx.jpg",
		"objs/skybox/posy.jpg",
		"objs/skybox/negy.jpg",
		"objs/skybox/posz.jpg",
		"objs/skybox/negz.jpg"
	};

	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	for (unsigned int i = 0; i < 6; i++) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);

		if (data) {

			stbi_set_flip_vertically_on_load(false);

			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else {
			std::cout << "Failed to load: " << facesCubemap << "\n";
			stbi_image_free(data);
		}
	}

	//Shadows
	

	/*
	//Shadows
	GLuint shadowMapFBO;
	glCreateFramebuffers(1, &shadowMapFBO);

	GLuint shadowMapWidth = 2048;
	GLuint shadowMapHeight = 2048;
	GLuint shadowMap;

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float clampColour[] = { 1.0f,1.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColour);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//!!For spotlight replace ortho with perspective
	
	//! adjust to fit scene
	glm::mat4 orthgonalProjection = glm::ortho(-35.0f, 35.0f, -35.0f, 35.0f, 0.1f, 75.0f);

	glm::mat4 perspectiveProjection = glm::perspective(glm::radians(90.f), 1.0f, 0.1f, 100.f);



	//! scuffed using
	glm::mat4 lightView = glm::lookAt(rcCar->getLightPos(), rcCar->getLightPos() + rcCar->getFront(), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 lightProjection = perspectiveProjection * lightView;

	*/
	
	

	while (!glfwWindowShouldClose(window))
	{
		static const GLfloat bgd[] = { .8f, .8f, .8f, 1.f };
		glClearBufferfv(GL_COLOR, 0, bgd);
		glClear(GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Skybox stuff
		
		glDepthFunc(GL_LEQUAL);
		
		glUseProgram(skyboxShader);
		glUniform1i(glGetUniformLocation(skyboxShader, "skybox"), 0);
		
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);


		//!! camera related
		view = glm::mat4(glm::mat3(glm::lookAt(activeCamera->Position, activeCamera->Position + activeCamera->Orientation, activeCamera->Up)));
	


		projection = glm::perspective(glm::radians(45.0f), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);

		//END OF SKYBOX
		
		//Shadows
		//glUseProgram(shadowShader);
		//glUniformMatrix4fv(glGetUniformLocation(shadowShader, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightProjection * lightView));


		//glEnable(GL_DEPTH_TEST);

		//glViewport(0, 0, shadowMapWidth, shadowMapHeight);

		//glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);

		//glClear(GL_DEPTH_BUFFER_BIT);



		//RenderModels(shadowShader);


		//glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//glViewport(0, 0, WIDTH, HEIGHT);

		
		//!!
		

		//glUniformMatrix4fv(glGetUniformLocation(program, "lightProjection"), 1, GL_FALSE, glm::value_ptr(lightProjection));

		//glActiveTexture(GL_TEXTURE2);
		//glBindTexture(GL_TEXTURE_2D, shadowMap);
		//glUniform1i(glGetUniformLocation(program, "shadowMap"), 2);



		glUseProgram(program);


		glUniform3f(glGetUniformLocation(program, "camPos"), activeCamera->Position.x, activeCamera->Position.y, activeCamera->Position.z);

		//glUniform3f(glGetUniformLocation(program, "camPos"), Camera.Position.x, Camera.Position.y, Camera.Position.z);

		//Camera stuff
		activeCamera->Matrix(45.0f, 0.1f, 200.0f, program, "camMatrix");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		animatedCar->BezierCurve();

		RenderModels(program);
	
		
		street.DrawStreet(program, 20);

		SetLights(program);

		glfwSwapBuffers(window);

		glfwPollEvents();
		processKeyboard(window);


		if (activeCamera == &nCamera) {
			nCamera.Inputs(window);
		}
		
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}