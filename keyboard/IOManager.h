#pragma once
#include <string>
#include <vector>
using namespace std;

class IOManager{
public:
	static bool readFileToBuffer(string FilePath,vector<unsigned char>& buffer);
};