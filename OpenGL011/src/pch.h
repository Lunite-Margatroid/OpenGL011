#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdlib.h>

#include <windows.h>
#define HEIGHT 1600
#define WIDTH 900

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define WIDTH	1600
#define HEIGHT	900

#ifndef PI
#define PI 3.14159f
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);