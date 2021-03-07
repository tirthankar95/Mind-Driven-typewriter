#include "classifier.h"

classifier::classifier(){
	mp["AAea"]=1; mp["AeaAe"]=10;mp["EeAa"]=19;
	mp["AAa"]=2; mp["AaA"]=11; mp["EeAea"]=20;
	mp["AUu"]=3; mp["AaAea"]=12; mp["EeUu"]=21;
	mp["AEe"]=4; mp["AaUu"]=13; mp["UuA"]=22;
	mp["AAe"]=5; mp["AaEe"]=14; mp["UuAea"]=23;
	mp["AeaA"]=6; mp["AaAe"]=15; mp["UuAa"]=24;
	mp["AeaAa"]=7; mp["UuEe"]=16; mp["AeAa"]=25;
	mp["AeaUu"]=8; mp["UuAe"]=17; mp["AeAa"]=26;
	mp["AeaEe"]=9; mp["EeAe"]=18; mp["O"]=27;
}
classifier::~classifier(){

}
string classifier::closeTo(vector<double> &y){
	double res=0;int indx=-1;
	for(int i=0;i<7;i++){
		double dist=0;
		for(int j=0;j<5;j++)
			dist+=(ideal_y[i][j]-y[j])*(ideal_y[i][j]-y[j]);
		if(i==0){res=dist;indx=0;}
		else if(res>dist){
			res=dist;
			indx=i;
		}}//end of outer for
	return mapped[indx];
}
string classifier::predict(vector<double> &x){
	vector<double> y(5);
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++)
			y[i]+=x[j]*W[j][i];
	}
	return closeTo(y);
}
bool classifier::isValid(string s){
	int code=mp[s];
	if(code>=1 && code<=27)return true;
	else return false;
}
int classifier::getCode(){
	int t=2;string str="";
	while(t--){
		vector<double> x(5);
		for(int i=0;i<5;i++)cin>>x[i];
		string st=predict(x);
		str+=st;
		cout<<st<<endl;
		if(str=="O")return mp[str];
	}
	if(isValid(str))
		return mp[str];
	else return 0;
}
