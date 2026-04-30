#pragma once
#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include "stb_image.h"
#include "inc.h"


GLuint setup_texture(const char* filename);
GLuint setup_mipmaps(const char* filename[], int n);

#endif