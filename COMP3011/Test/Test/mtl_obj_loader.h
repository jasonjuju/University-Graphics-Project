#pragma once

#include "inc.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Headers/submesh.h"


namespace mtl_obj_loader {
	

	std::vector<SubMesh> load_model_from_file(const char* filename, glm::mat4 preTransform, const char* mtlfile);
}