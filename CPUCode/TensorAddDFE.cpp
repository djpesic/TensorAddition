#include "LTensor/LTensor.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>
#include "MaxSLiCInterface.h"
#include "Maxfiles.h"

using namespace std;
fstream input, output;

void tensorAddDFE() {
	long rank, dim1, dim2, dim3, num, inTensorsLen =0, inTensorLen = 0;
	float* inTensors;
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
	long j = 0, offset = 0;
	float data;
	for(long i=0; i < inTensorsLen;i++){
		input >> data;
		inTensors[j*num+offset] = data;
		j++;
		if(j==inTensorLen){
			j=0;
			offset++;
		}
	}
	//call DFE

	delete[] inTensors;

	input.close();
	output.close();
}
