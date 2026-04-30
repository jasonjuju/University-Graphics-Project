#pragma once
#include "road.h"
#include "texture.h"


Road::Road() {
    texture = setup_texture("objs/source/road/Road_2K.jpg");


    vertices =


    {
        

         //top face
         -0.5f,  0.5f, -0.5f,  0.f, 1.f,   0.f, 1.f, 0.f,
          0.5f,  0.5f, -0.5f,  1.f, 1.f,   0.f, 1.f, 0.f,
          0.5f,  0.5f,  0.5f,  1.f, 0.f,   0.f, 1.f, 0.f,
          0.5f,  0.5f,  0.5f,  1.f, 0.f,   0.f, 1.f, 0.f,
         -0.5f,  0.5f,  0.5f,  0.f, 0.f,   0.f, 1.f, 0.f,
         -0.5f,  0.5f, -0.5f,  0.f, 1.f,   0.f, 1.f, 0.f

    };
}





void Road::DrawRoad(GLuint program, glm::vec3 pos) {
    

   

    GLuint VAO, VBO;

    glCreateBuffers(1, &VBO);
    

    glCreateVertexArrays(1, &VAO);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
    glNamedBufferStorage(VBO, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

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

    //Cost intensive, **REWRITE**
    for (int i = 0; i < length; ++i) {
        model = glm::mat4(1.f);
        model = glm::translate(model, (pos + glm::vec3(i * 10.0f, -1.0f, 0.0f)));
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
        
        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));


        glDrawArrays(GL_TRIANGLES, 0, 36);


        model = glm::mat4(1.f);
        model = glm::translate(model, (pos + glm::vec3(i * 10.0f, -1.0f, 10.0f)));
        model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));

        glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    

}