#pragma once
#include <GL/glew.h>

struct VertexTm{
	struct Position
	{
		float x;
		float y;
	}position;
	struct Color{
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	}color;
	struct UV
	{
		float u;
		float v;
	}uv;
	void setColor(GLubyte r,GLubyte g,GLubyte b,GLubyte a){
		color.r=r;color.g=g;color.b=b;color.a=a;
	}
	void setUV(float u,float v){
		uv.u=u;uv.v=v;
	}
};