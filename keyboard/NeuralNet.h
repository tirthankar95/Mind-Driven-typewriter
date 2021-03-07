#include <iostream>
#include <vector>
using namespace std;

class NeuralNet{
public:
	NeuralNet();
	~NeuralNet();
	int getCode();
private:
	int no;
	int lim;
	vector<int> codesArr;
};
