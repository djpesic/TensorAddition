#include "LTensor/LTensor.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>
#include "MaxSLiCInterface.h"
#include "Maxfiles.h"

using namespace std;
fstream input, output;

float* readFirstRankTensor(int dim) {

	float* d=new float[dim];

	for (int ind = 0; ind < dim; ind++) {
		input >> d[ind];
	}
	return d;
}

void writeFirstRankTensor(int dim, float* resultTensor) {
	for (int ind = 0; ind < dim; ind++) {
		output << resultTensor[ind] << " ";
	}
}

float* readSecondRankTensor(int dim1, int dim2) {
	float* d = new float[dim1*dim2];
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			input >> d[ind1*dim1+ind2];
		}
	}
	return d;
}

void writeSecondRankTensor(int dim1, int dim2, float* resultTensor) {
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			output << resultTensor[ind1*dim1+ind2] << " ";
		}
	}
}

float* readThirdRankTensor(int dim1, int dim2, int dim3) {
	float* d=new float[dim1*dim2*dim3];
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				input >> d[ind1*dim1*dim2+ind2*dim2+ind3];
			}
		}
	}
	return d;
}

void writeThirdRankTensor(int dim1, int dim2, int dim3, float* resultTensor) {
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				output << resultTensor[ind1*dim1*dim2+ind2*dim2+ind3] << " ";
			}
		}
	}
}

void tensorAddDFE() {
	int rank, dim1, dim2, dim3;
	float* inTensor1=0, *inTensor2=0, *resultTensor=0;
	input.open("test/test1_in.txt", fstream::in);
	if(!input){
		cout << "Input file does not exists!\n";
		return;
	}
	output.open("test/test3_out.txt", fstream::out);
	input >> rank;

	switch (rank) {
	case 0:
		//tensor rank 0: scalar, trivial case
		float scalar1, scalar2;
		input >> scalar1 >> scalar2;
		output << scalar1 + scalar2;
		break;
	case 1:
		input >> dim1;
		inTensor1 =readFirstRankTensor(dim1);
		inTensor2 =readFirstRankTensor(dim1);
		resultTensor = new float[dim1];
		TensorAddition(dim1, inTensor1,inTensor2,resultTensor);
		writeFirstRankTensor(dim1, resultTensor);
		break;
	case 2:
		input >> dim1 >> dim2;
		inTensor1 =readSecondRankTensor(dim1,dim2);
		inTensor2 =readSecondRankTensor(dim1,dim2);
		resultTensor = new float[dim1*dim2];
		TensorAddition(dim1*dim2, inTensor1,inTensor2,resultTensor);
		writeSecondRankTensor(dim1, dim2, resultTensor);
		break;
	case 3:
		input >> dim1 >> dim2 >> dim3;
		inTensor1=readThirdRankTensor(dim1, dim2, dim3);
		inTensor2=readThirdRankTensor(dim1, dim2, dim3);
		resultTensor = new float[dim1*dim2*dim3];
		TensorAddition(dim1*dim2*dim3, inTensor1,inTensor2,resultTensor);
		writeThirdRankTensor(dim1, dim2, dim3, resultTensor);
		break;
	default:
		cout << "Ranks higher than 3 are not supported yet\n";
	}


	delete[] inTensor1;
	delete [] inTensor2;
	delete[] resultTensor;

	input.close();
	output.close();
}
