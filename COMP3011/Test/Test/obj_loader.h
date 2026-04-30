#pragma once

#include "inc.h"



namespace obj_loader {
	std::vector<float> load_model_from_file(const char* filename, glm::mat4 preTransform, const char* mtlfile);
}