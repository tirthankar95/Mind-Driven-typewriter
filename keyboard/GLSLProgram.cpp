#include "GLSLProgram.h"
#include "Errors.h"
#include <vector>

GLSLProgram::GLSLProgram():numAttributes(0),_programID(0),_vertexShaderID(0),_fragmentShaderID(0)
{

}
GLSLProgram::~GLSLProgram(){

}
GLuint GLSLProgram::getUniformLocation(const string& str){
	GLuint loc=glGetUniformLocation(_programID,str.c_str());
	if(loc==GL_INVALID_INDEX){
		fatalError("Uniform "+str+" not found in shader");
	}
	return loc;
}
void GLSLProgram::compileShaders(const string& vertexShaderFilePath,const string& fragmentShaderFilePath){
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID=glCreateProgram();

	_vertexShaderID=glCreateShader(GL_VERTEX_SHADER);
	if(_vertexShaderID==0){
		fatalError("Vertex Shader failed to be created!");
	}
	_fragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);
	if(_fragmentShaderID==0){
		fatalError("Fragment Shader failed to be created!");
	}
	subCompile(vertexShaderFilePath,_vertexShaderID);
	subCompile(fragmentShaderFilePath,_fragmentShaderID);
}
void GLSLProgram::linkShaders(){
	//Attach our shaders to our program
	glAttachShader(_programID,_vertexShaderID);
	glAttachShader(_programID,_fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*
	GLint isLinked=0;
	glGetProgramiv(_programID,GL_LINK_STATUS,(int*)&isLinked);
	if(isLinked==GL_FALSE){
		GLint maxLength=0;
		glGetProgramiv(_programID,GL_INFO_LOG_LENGTH,&maxLength);

		//The maxlength includes the NULL character
		vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID,maxLength,&maxLength,&infoLog[0]);

		//We don't need the program anymore
		glDeleteProgram(_programID);
		//Don't link shaders either
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		printf("%s\n", &(infoLog[0]));
		fatalError("Failed to link!\n");
	}
	glDetachShader(_programID,_vertexShaderID);
	glDetachShader(_programID,_fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}
void GLSLProgram::subCompile(string FilePath,GLuint& ShaderID){
	ifstream FFile(FilePath);
	if(FFile.fail()){
		perror(FilePath.c_str());
		fatalError("Failed to open" +FilePath);
	}
	string addline="";
	string line;
	while(getline(FFile,line)){
		addline+=line+"\n";
	}
	FFile.close();
	const char* contentsPtr=addline.c_str();
	glShaderSource(ShaderID,1,&contentsPtr,NULL);
	glCompileShader(ShaderID);

	GLint success = 0;
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
	if(success== GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(ShaderID, maxLength, &maxLength, &infoLog[0]);
		// We don't need the shader anymor.
		glDeleteShader(ShaderID);
		printf("%s\n", &(infoLog[0]));
		fatalError("Shader "+FilePath+" failed to compile!\n");
	}
}
void GLSLProgram::addAttribute(const string& attributeName){
	glBindAttribLocation(_programID,numAttributes++,attributeName.c_str());
}
void GLSLProgram::use(){
	glUseProgram(_programID);
	for(int i=0;i<numAttributes;i++){
		glEnableVertexAttribArray(i);
	}
}
void GLSLProgram::unuse(){
	glUseProgram(0);
	for(int i=0;i<numAttributes;i++){
		glDisableVertexAttribArray(i);
	}
}