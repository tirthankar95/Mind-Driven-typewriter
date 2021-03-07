#pragma once
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include <iostream>
#include <string>
#include "GLSLProgram.h"
#include "OpenGLTexture.h"
using namespace std;

enum GameState{PLAY,EXIT};
class MainGame{
	public:
		MainGame();
		~MainGame();	
		void run();
		void blink(int i);
		bool processInput();
	private:
		void initSystems();
		void initShaders();
		void gameLoop();
		void drawGame();
		GameState _gameState;
		SDL_Window* _window;
		int _screenWidth;
		int _screenHeight;
		Sprite _sprite[27];
		GLSLProgram _colorProgram;
		OpenGLTexture _playaTexture[27];
};