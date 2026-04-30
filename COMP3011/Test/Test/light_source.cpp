#include "light_source.h"


LightSource::LightSource(glm::vec3 pos, glm::vec3 col) {
	lightPos = pos;
	lightCol = col;
}




void LightSource::SetPosition(glm::vec3 newPos) {
	lightPos = newPos;
}


void LightSource::SetType(int newType) {
	lightType = newType;
}