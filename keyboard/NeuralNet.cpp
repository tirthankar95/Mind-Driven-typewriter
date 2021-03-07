#include "NeuralNet.h"

NeuralNet::NeuralNet(){
		no=0;
		vector<int> tmp({0,15,15,11,4,26,8,18,26,3,14,6});
		codesArr=tmp;
		lim=codesArr.size();
	}
NeuralNet::~NeuralNet(){

}
int NeuralNet::getCode(){
		if(no<lim)
			return codesArr[no++];
		else return -1;
	}