#include "RcCar.h"


RcCar::RcCar(std::vector<Object*>* objects, std::vector<LightSource*>* lights, NewCamera* c) {
	rcCamera = c;


	

	object = new Object(
		"objs/source/chevelle/WTDIMTYHY1OX052LSDDZ1WH0V.obj",
		"objs/source/chevelle/"
	);

	object->SetPosition(glm::vec3(20, -0.15, 10));
	objects->push_back(object);

	rcCamera->Position = object->GetPosition() + cameraOffset;
	rcCamera->Orientation = front;



	headlight1 = new LightSource(
		object->GetPosition() + lightOffset + headlightOffset,
		glm::vec3(1.0f, 0.8f, 0.0f)
	);

	//set spotlight
	headlight1->SetType(1);




	lights->push_back(headlight1);


	
	headlight2 = new LightSource(
		object->GetPosition() + lightOffset - headlightOffset,
		glm::vec3(1.0f, 0.8f, 0.0f)
	);

	//set spotlight
	headlight2->SetType(1);

	lights->push_back(headlight2);

	
}

void RcCar::moveForward() {
	object->SetPosition(object->GetPosition() + front * 0.1f);
	update();
}

void RcCar::moveBackward() {
	object->SetPosition(object->GetPosition() - front * 0.1f);
	update();


}

void RcCar::turnRight() {
	object->ChangeRotation(-1.0f);

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(-1.0f), glm::vec3(0, 1, 0));
	lightOffset = glm::vec3(rotation * glm::vec4(lightOffset, 0.0f));
	headlightOffset = glm::vec3(rotation * glm::vec4(headlightOffset, 0.0f));
	cameraOffset = glm::vec3(rotation * glm::vec4(cameraOffset, 0.0f));

	front = glm::vec3(rotation * glm::vec4(front, 0.0f));


	update();

}

void RcCar::turnLeft() {
	object->ChangeRotation(1.0f);

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0, 1, 0));
	lightOffset = glm::vec3(rotation * glm::vec4(lightOffset, 0.0f));
	headlightOffset = glm::vec3(rotation * glm::vec4(headlightOffset, 0.0f));
	cameraOffset = glm::vec3(rotation * glm::vec4(cameraOffset, 0.0f));

	front = glm::vec3(rotation * glm::vec4(front, 0.0f));

	update();
}

glm::vec3 RcCar::getLightPos() {
	return headlight1->lightPos;
}

void RcCar::update() {
	headlight1->SetPosition(object->GetPosition() + lightOffset + headlightOffset);
	headlight2->SetPosition(object->GetPosition() + lightOffset - headlightOffset);
	rcCamera->Position = object->GetPosition() + cameraOffset;
	rcCamera->Orientation = front;
}