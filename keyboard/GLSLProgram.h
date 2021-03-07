#pragma once
#include <string>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
using namespace std;

class GLSLProgram{
public:
	GLSLProgram();
	~GLSLProgram();
	void compileShaders(const string& vertexShaderFilePath,const string& fragmentShaderFilePath);
	void linkShaders();
	void addAttribute(const string& attributeName);
	void use();
	void unuse();
	GLuint getUniformLocation(const string& str);
private:
	int numAttributes;
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	void subCompile(string str,GLuint& in);
};