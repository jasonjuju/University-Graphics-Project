#pragma once
#include "texture.h"

GLuint setup_texture(const char* filename)
{

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	GLuint texObject;
	glGenTextures(1, &texObject);
	glBindTexture(GL_TEXTURE_2D, texObject);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int w, h, chan;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* pxls = stbi_load(filename, &w, &h, &chan, 0);

	if (pxls) {
		if (chan == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pxls);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pxls);
		}

		
		glGenerateMipmap(GL_TEXTURE_2D);
	}




	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);



	return texObject;
}


