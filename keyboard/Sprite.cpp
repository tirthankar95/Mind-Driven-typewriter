#include "Sprite.h"
#include <cstddef>
#include "VertexTm.h"

Sprite::Sprite(){
	_vbufID=0;
}
Sprite::~Sprite(){
	if(!_vbufID)
		glDeleteBuffers(1,&_vbufID);
}
void Sprite::init(float x,float y,float width,float height,bool defaultColor){
	_x=x;
	_y=y;
	_width=width;
	_height=height;
	if(_vbufID==0)
		glGenBuffers(1,&_vbufID);
	VertexTm vertexData[6];//drawing a square
	// First Triangle
		vertexData[0].position.x=x;
		vertexData[0].position.y=y;
		vertexData[0].setUV(0,0);

		vertexData[1].position.x=x;
		vertexData[1].position.y=y+height;
		vertexData[1].setUV(0,1);

		vertexData[2].position.x=x+width;
		vertexData[2].position.y=y+height;
		vertexData[2].setUV(1,1);
	// Second Triangle
		vertexData[3].position.x=x;
		vertexData[3].position.y=y;
		vertexData[3].setUV(0,0);

		vertexData[4].position.x=x+width;
		vertexData[4].position.y=y;
		vertexData[4].setUV(1,0);

		vertexData[5].position.x=x+width;
		vertexData[5].position.y=y+height;
		vertexData[5].setUV(1,1);
	if(defaultColor)
	for(int i=0;i<6;i++)
		vertexData[i].setColor(255,255,255,255);
	if(!defaultColor)
	for(int i=0;i<6;i++)
		vertexData[i].setColor(0,0,0,0);
	glBindBuffer(GL_ARRAY_BUFFER,_vbufID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertexData),vertexData,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
void Sprite::changeColor(bool original){
	if(original)
		init(_x,_y,_width,_height,true);
	else
		init(_x,_y,_width,_height,false);
}
void Sprite::draw(){
	//Bind the buffer object
	glBindBuffer(GL_ARRAY_BUFFER,_vbufID);
	//Tell opengl that we want to use the first 
	//attribute array. We only need one array right
	//now since we are only using position
		glEnableVertexAttribArray(0);
		//This is the position attribute pointer
			glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(VertexTm),(void*)offsetof(VertexTm,position));
		//This is the color attribute pointer
			glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexTm),(void*)offsetof(VertexTm,color));
		//This is the UV attribute pointer
			glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(VertexTm),(void*)offsetof(VertexTm,uv));
			glDrawArrays(GL_TRIANGLES,0,6);
		glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

//paper.dvi - download