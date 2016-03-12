#include "LTensor/LTensor.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>

using namespace std;
static fstream input, output;

float generateRandomNumber(){
	float fMin=0, fMax=10000;
	float f = (float)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);

}

static void addFirstRankTensors(long dim, long num) {

	Marray<float, 1> a(dim), sum(dim);

	Index<'i'> i;
	for (long ind = 0; ind < dim; ind++) {
		input >> sum(ind);
	}
	num--;
	for(long it=0;it<num;it++){
		for (long ind = 0; ind < dim; ind++) {
			input >> a(ind);
		}
		sum(i)=sum(i)+a(i);
	}
	for (long ind = 0; ind < dim; ind++) {
		output << sum(ind) << " ";
	}
}


static void addSecondRankTensors(long dim1, long dim2,long num) {
	Marray<float, 2> a(dim1, dim2), sum(dim1, dim2);
	Index<'i'> i;
	Index<'j'> j;
	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			input >> sum(ind1, ind2);
		}
	}
	num--;
	for(long ind=0;ind<num;ind++){
		for (long ind1 = 0; ind1 < dim1; ind1++) {
			for (long ind2 = 0; ind2 < dim2; ind2++) {
				input >> a(ind1, ind2);
			}
		}
		sum(i,j) = sum(i,j) + a(i, j);
	}

	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			output << sum(ind1, ind2) << " ";
		}
	}
}



static void addThirdRankTensors(long dim1, long dim2, long dim3, long num) {
	Marray<float, 3> a(dim1, dim2, dim3), sum(dim1, dim2, dim3);

	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			for (long ind3 = 0; ind3 < dim3; ind3++) {
				input >> sum(ind1, ind2, ind3);
			}
		}
	}
	num--;
	for(long ind=0;ind<num;ind++){
		for (long ind1 = 0; ind1 < dim1; ind1++) {
			for (long ind2 = 0; ind2 < dim2; ind2++) {
				for (long ind3 = 0; ind3 < dim3; ind3++) {
					input >> a(ind1, ind2, ind3);
				}
			}
		}
		sum(i, j, k) = sum(i, j, k) + a(i, j, k);
	}
	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			for (long ind3 = 0; ind3 < dim3; ind3++) {
				output << sum(ind1, ind2, ind3)  << " ";
			}
		}
	}
}


void tensorAddLTensor(char* inputName, char* outputName) {
	long  rank, dim1, dim2, dim3;
	int num;
	//
	//	input.open("test/test110e4x10e6_in1.txt", fstream::out);
	//	input << 10000;
	//	input << 1 << endl;
	//	input << 1000000 << endl;
	//	for(long j=0;j<10000;j++){
	//		for(long i=0;i<1000000;i++){
	//			input << generateRandomNumber() << " ";
	//		}
	//		input << "\n";
	//	}
	//
	//	input.close();
	//	return;

	input.open(inputName, fstream::in);
	if(!input){
		cout << "Input file does not exists!\n";
		return;
	}
	output.open(outputName, fstream::out);
	input >> num;
	input >> rank;

	switch (rank) {
	case 0: {
		//tensor rank 0: scalar, trivial case
		float sum=0, scalar;
		for(long i=0;i<num;i++){
			input >> scalar;
			sum+=scalar;
		}
		output << sum;
		break;
	}
	case 1:
		input >> dim1;
		addFirstRankTensors(dim1,num);
		break;
	case 2:
		input >> dim1 >> dim2;
		addSecondRankTensors(dim1, dim2,num);
		break;
	case 3:
		input >> dim1 >> dim2 >> dim3;
		addThirdRankTensors(dim1, dim2, dim3,num);
		break;
	default:
		cout << "Ranks higher than 3 are not supported yet\n";
	}
	input.close();
	output.close();
}
