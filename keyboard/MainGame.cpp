#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"
using namespace std;

MainGame::MainGame(){
	_window=NULL;
	_screenWidth=640;
    _screenHeight=480;
    _gameState=GameState::PLAY;
}
MainGame::~MainGame(){

}
void MainGame::run(){
	initSystems();
	float x=-0.65,y=0.50;
	for(int j=0;j<5;j++){
		for(int i=0;i<5;i++){
			_sprite[i+5*j].init(x,y,0.21,0.21);
			x=x+0.21+0.06;}
		x=-0.65;
		y=y-0.21-0.06;
	}
	_sprite[25].init(-0.65,-0.85,0.21,0.21);
	_sprite[26].init(-0.38,-0.85,1.02,0.20);
	string tmp="A";
	for(int i=0;i<26;i++){
		_playaTexture[i]=ImageLoader::loadPNG("black/"+tmp+".png");
		tmp[0]++;
	}
	_playaTexture[26]=ImageLoader::loadPNG("black/spaceBar.png");
	gameLoop();
}
void MainGame::initSystems(){
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Game Engine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight , SDL_WINDOW_OPENGL);
	if(_window==NULL){
		fatalError("SDL window could not be created!");
	}
	SDL_GLContext context=SDL_GL_CreateContext(_window);
	if(context==NULL){
		fatalError("SDL_GL context could not be created!");
	}
	GLenum error=glewInit();
	if(error!=GLEW_OK){
		fatalError("Could not initialize glew!");
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
	glClearColor(0.062f,0.529f,0.917f,1.0f);
	initShaders();
}
void MainGame::initShaders(){
	_colorProgram.compileShaders("Shaders/colorShader.vertex","Shaders/colorShader.fragment");
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	_colorProgram.addAttribute("vertexUV");
	_colorProgram.linkShaders();
}
void MainGame::gameLoop(){
	while(_gameState!=GameState::EXIT){
		processInput();
		drawGame();
		return;
	}
}
void MainGame::blink(int i){
	for(int j=1;j<=2;j++){
		_sprite[i].changeColor(false);
		drawGame();
		SDL_Delay(300);
		_sprite[i].changeColor(true);
		drawGame();
		SDL_Delay(300);
	}
}
bool MainGame::processInput(){
	SDL_Event evnt;
	while(SDL_PollEvent(&evnt)){
		switch(evnt.type){
			case SDL_QUIT:
				return false;
			break;
			case SDL_MOUSEMOTION:
			break;
		}//....switch
	}//.....while
	return true;
}
void MainGame::drawGame(){
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_colorProgram.use();
	glActiveTexture(GL_TEXTURE0);
	for(int i=0;i<27;i++){
		glBindTexture(GL_TEXTURE_2D,_playaTexture[i].id);
		GLuint textureLocation=_colorProgram.getUniformLocation("playa");
		glUniform1i(textureLocation,0);
			_sprite[i].draw();
		glBindTexture(GL_TEXTURE_2D,0);
	}
	_colorProgram.unuse();
	SDL_GL_SwapWindow(_window);
}