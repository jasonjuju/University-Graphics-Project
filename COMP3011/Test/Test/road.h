#pragma once
#include "inc.h"
class Road
{
    GLuint texture;

    std::vector<float> vertices;

    int length;


public:

    Road();

    void DrawRoad(GLuint program, glm::vec3 pos);

    void SetLength(int l) { length = l; }
};

