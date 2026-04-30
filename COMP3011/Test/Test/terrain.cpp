#pragma once
#include "terrain.h"
#include "texture.h"


Terrain::Terrain() {

    
    

    texture = setup_texture("objs/grass/Grass_001_diffuse.jpg");

    //Generate highmap

    


}

void Terrain::SetupTerrain(int length) {

    depth = 20;
    float scale = 1.0f;
    float uvRepeat = 100.0f;

    std::vector<float> heightMap;
    width = length + 6;

    for (int z = 0; z <= depth; z++) {
        for (int x = 0; x <= width; x++) {
            //Random float from -1 to 1
            float randomFloat = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;

            //Flatten area with street
            if (z > depth / 2 - 5 && z < depth / 2 + 5) {
                heightMap.push_back(0.0f);
            }
            else {
                heightMap.push_back(randomFloat * 6.0f);
            }

        }
    }


    for (int z = 0; z <= depth; z++) {
        for (int x = 0; x <= width; x++) {
            float fx = x * scale;
            float fz = z * scale;

            float fy = heightMap.at(z * width + x);


            //pos
            vertices.push_back(fx);
            vertices.push_back(fy);
            vertices.push_back(fz);

            //texCoords
            vertices.push_back(x / (float)width * uvRepeat);
            vertices.push_back(z / (float)depth * uvRepeat);

            //normal
            vertices.push_back(0.0f);
            vertices.push_back(1.0f);
            vertices.push_back(0.0f);
        }
    }

    for (int z = 0; z < depth; z++) {
        for (int x = 0; x < width; x++) {
            int topLeft = z * (width + 1) + x;
            int topRight = z * (width + 1) + x + 1;
            int botLeft = (z + 1) * (width + 1) + x;
            int botRight = (z + 1) * (width + 1) + x + 1;

            indices.push_back(topLeft);
            indices.push_back(botLeft);
            indices.push_back(topRight);

            indices.push_back(topRight);
            indices.push_back(botLeft);
            indices.push_back(botRight);
        }
    }
}


void Terrain::GenerateTerrain(GLuint program) {

	

    GLuint VAO, VBO, EBO;

    glCreateBuffers(1, &VBO);
    glCreateBuffers(1, &EBO);

    glCreateVertexArrays(1, &VAO);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
    glNamedBufferStorage(VBO, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayElementBuffer(VAO, EBO);
    glNamedBufferStorage(EBO, sizeof(unsigned int) * indices.size(), indices.data(), GL_DYNAMIC_STORAGE_BIT);

    glEnableVertexArrayAttrib(VAO, 0);
    glEnableVertexArrayAttrib(VAO, 1);
    glEnableVertexArrayAttrib(VAO, 2);

    glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribBinding(VAO, 1, 0);
    glVertexArrayAttribBinding(VAO, 2, 0);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(glGetUniformLocation(program, "texture1"), 0);



    glBindVertexArray(VAO);
    glm::mat4 model;


    model = glm::mat4(1.f);
    model = glm::translate(model, glm::vec3(-60.0f, -1.1f, -5.0f * depth));
    model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));



    glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


}