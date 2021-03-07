#include "MainGame.h"
#include "classifier.h"
#include <fstream>

vector<char> codes;
int goLoop;

void init(){
	codes.resize(27);
	for(int i=0;i<27;i++)
		codes[i]=(char)('A'+i);
	codes[26]=' ';
	goLoop=1;
}
int main(int argc,char** argv){
	init();
	classifier nn;
	MainGame mainGame;
	mainGame.run();
	fstream file("save.txt",ios::app);
	while(goLoop){
		int code=nn.getCode()-1;
		if(code!=-1){
			mainGame.blink(code);
			file<<codes[code];
			cout<<codes[code];
			SDL_Delay(700);
		}
		else
			goLoop=0;
	}file<<"\n";cout<<endl;
	file.close();
	//while(mainGame.processInput());
	return 0;
}
