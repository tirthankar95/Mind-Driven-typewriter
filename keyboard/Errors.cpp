#include <iostream>
#include <SDL2/SDL.h>
#include "Errors.h"

void fatalError(string str){
	cout<<" error string : "<<str<<endl;
	cout<<" Enter a key to quit ";char ch;
	cin>>ch;
	SDL_Quit();
	exit(1);
}