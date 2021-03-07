#pragma once
#include <GL/glew.h>

class Sprite{
	public:
		Sprite();
		~Sprite();
		void init(float x,float y,float width,float height,bool defaultColor=true);
		void changeColor(bool var);
		void draw();
	private:
		float _x;
		float _y;
		float _width;
		float _height;
		GLuint _vbufID;
};