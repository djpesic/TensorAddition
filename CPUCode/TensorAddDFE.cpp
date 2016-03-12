#include "LTensor/LTensor.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>
#include "MaxSLiCInterface.h"
#include "Maxfiles.h"

using namespace std;
fstream input, output;
const int loopSize =TensorAddition_tileSize;
void tensorAddDFE(char* inputName, char* outputName) {
	long rank, dim1, dim2, dim3, inTensorsLen =0, inTensorLen = 0;
	float* inTensors, *sum;
	int num;
	input.open("test/test3_in.txt", fstream::in);
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

	int numZeroes = loopSize- inTensorLen % loopSize;
	inTensors = new float[inTensorsLen+numZeroes*num];
	int skipSize = loopSize*(num-1);
	int numLoaded=0;// counts to loopSize
	int numLoaded1=0;//counts to tensor length
	int offset=0;
	long cnt=0;
	float data;
	for(long i=0;i<inTensorsLen;i++){
		input >> data;
		inTensors[cnt]=data;
		cnt++;
		numLoaded++;
		numLoaded1++;
		if(numLoaded==loopSize){
			cnt+=skipSize;
			numLoaded=0;
		}
		if(numLoaded1==inTensorLen){
			for(int j=0;j<numZeroes;j++){
				inTensors[cnt]=0;
				cnt++;
			}
			offset+=loopSize;
			cnt=offset;
			numLoaded1=numLoaded=0;

		}
	}

	//call DFE
	inTensorLen+=numZeroes;
	inTensorsLen+=numZeroes*num;
	sum = new float[inTensorLen];

	TensorAddition(inTensorsLen, inTensorLen, num, inTensors, sum);
	for(int i=0;i<inTensorLen;i++){
		output << sum[i] << " ";
	}
	delete[] inTensors;
	delete[] sum;
	input.close();
	output.close();
}
