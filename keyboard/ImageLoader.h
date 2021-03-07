#pragma once
#include "OpenGLTexture.h"
#include <string>
using namespace std;

class ImageLoader{
public:
	static OpenGLTexture loadPNG(string FilePath);
};