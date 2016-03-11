#include "LTensor/LTensor.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>
#include "MaxSLiCInterface.h"
#include "Maxfiles.h"

using namespace std;
fstream input, output;
const int loopSize =13;
void tensorAddDFE() {
	long rank, dim1, dim2, dim3, inTensorsLen =0, inTensorLen = 0;
	float* inTensors, *sum;
	int num;
	input.open("test/test1_in.txt", fstream::in);
	if(!input){
		cout << "Input file does not exists!\n";
		return;
	}
	output.open("test/test3_out.txt", fstream::out);
	input >> num >>  rank;

	switch (rank) {
	case 0:
		//tensor rank 0: scalar, trivial case
		inTensorLen = 1;
		inTensorsLen = num;
		break;
	case 1:
		input >> dim1;
		inTensorLen = dim1;
		inTensorsLen = num*dim1;
		break;
	case 2:
		input >> dim1 >> dim2;
		inTensorLen = dim1*dim2;
		inTensorsLen = num*dim1*dim2;
		break;
	case 3:
		input >> dim1 >> dim2 >> dim3;
		inTensorLen = dim1*dim2*dim3;
		inTensorsLen = num*dim1*dim2*dim3;
		break;
	default:
		cout << "Ranks higher than 3 are not supported yet\n";
		return ;
	}
	//prepare data for DFE
	inTensors = new float[inTensorsLen];
	long offset = 0,cnt=0;
	float data;
	for(long i=0; i < inTensorsLen;i++){
		input >> data;
		inTensors[cnt+offset] = data;
		cnt++;
		if(cnt==loopSize){
			cnt+=num*loopSize;
		}
		if(cnt==inTensorLen){
			cnt=0;
			offset+=loopSize;
		}
	}

	for(int i=0;i<inTensorsLen;i++){
			cout << inTensors[i] << " ";
		}

	return;
	//call DFE
	sum = new float[inTensorLen];
	TensorAddition(inTensorsLen,num,inTensorLen,inTensors,sum);
	for(int i=0;i<inTensorsLen;i++){
		output << sum << " ";
	}
	delete[] inTensors;
	delete[] sum;
	input.close();
	output.close();
}
