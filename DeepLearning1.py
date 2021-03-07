import numpy as np

#Global Variables
R=7*4 #no. of training and validation examples
C=28500 #no. of features in an example 
dataX=np.zeros((R,C))
dataY=np.zeros((R,1))
cnt=0

def floatMine(s):
	n=len(s);fin=""
	for i in range(n):
		if s[i]=="\n": break;
		else: fin=fin+s[i]
	ret=float(fin)
	return ret

def readFromFile():
	global cnt
	fo_ip=open("InputDL.txt","r")
	fo_op=open("OutputDL.txt","r")
	while cnt<28:
		vec=[]
		while True:
			line=fo_ip.readline()
			if line == "NULL\n": break;
			else: vec.append(floatMine(line))
		if cnt<28:
			dataX[cnt]=vec
			dataY[cnt]=int(fo_op.readline())
			cnt+=1

readFromFile()
print(dataX.ndim)
