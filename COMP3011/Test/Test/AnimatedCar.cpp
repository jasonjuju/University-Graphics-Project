#include "AnimatedCar.h"



AnimatedCar::AnimatedCar(std::vector<Object*>* objects) {


	


	object = new Object(
		"objs/source/car_obj/K1AGJVQ50VCSD2UOPBS13FD0S.obj",
		"objs/source/car_obj/"
	);

	object->SetPosition(glm::vec3(20, -0.15, 5));
	objects->push_back(object);

	







	


}



void AnimatedCar::BezierCurve() {


	glm::vec3 pointA = nodes.at(currentNode);
	glm::vec3 pointB = nodes.at((currentNode+1) % nodes.size());
	glm::vec3 pointC = nodes.at((currentNode+2) %nodes.size());


	float t = float(currentPoint + 1) / float(totalPoints);

	//glm::vec3 diffAB = pointB - pointA;

	glm::vec3 ab = glm::mix(pointA, pointB, t);

	glm::vec3 bc = glm::mix(pointB, pointC, t);

	glm::vec3 fin = glm::mix(ab, bc, t);


	currentPoint++;

	if (currentPoint == totalPoints) {
		currentPoint = 0;

		currentNode = (currentNode + 2) % nodes.size();
	}

	object->SetPosition(fin);

	glm::vec3 dir = 2.0f *(1.0f - t) * (pointB - pointA) + 2.0f * t * (pointC - pointB);
	front = dir;

	float angle =  glm::degrees(atan2(dir.x, dir.z));

	//
	object->SetRotation(angle -90);


	
}