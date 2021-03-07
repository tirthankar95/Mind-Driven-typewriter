#include "IOManager.h"
#include <fstream>
#include <iostream>

bool IOManager::readFileToBuffer(string FilePath,vector<unsigned char>& buffer){
	ifstream file(FilePath,ios::binary);
	if(file.fail()){
		perror(FilePath.c_str());
		return false;
	}
	file.seekg(0,ios::end);
	int size=file.tellg();
	file.seekg(0,ios::beg);
	//Reduce the file size by any header bytes that might be present
	size-=file.tellg();
	buffer.resize(size);
	file.read((char *)&(buffer[0]),size);
	file.close();
	return true; 
}

