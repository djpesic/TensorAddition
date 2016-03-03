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

static void addFirstRankTensors(int dim, int num) {

	Marray<float, 1> a(dim), sum(dim);

	Index<'i'> i;
	for (int ind = 0; ind < dim; ind++) {
		input >> sum(ind);
	}
	num--;
	for(int it=0;it<num;it++){
		for (int ind = 0; ind < dim; ind++) {
			input >> a(ind);
		}
		sum(i)=sum(i)+a(i);
	}
	for (int ind = 0; ind < dim; ind++) {
		output << sum(ind) << " ";
	}
}


static void addSecondRankTensors(int dim1, int dim2,int num) {
	Marray<float, 2> a(dim1, dim2), sum(dim1, dim2);
	Index<'i'> i;
	Index<'j'> j;
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			input >> sum(ind1, ind2);
		}
	}
	num--;
	for(int ind=0;ind<num;ind++){
		for (int ind1 = 0; ind1 < dim1; ind1++) {
			for (int ind2 = 0; ind2 < dim2; ind2++) {
				input >> a(ind1, ind2);
			}
		}
		sum(i,j) = sum(i,j) + a(i, j);
	}

	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			output << sum(ind1, ind2) << " ";
		}
	}
}



static void addThirdRankTensors(int dim1, int dim2, int dim3, int num) {
	Marray<float, 3> a(dim1, dim2, dim3), sum(dim1, dim2, dim3);

	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				input >> sum(ind1, ind2, ind3);
			}
		}
	}
	num--;
	for(int ind=0;ind<num;ind++){
		for (int ind1 = 0; ind1 < dim1; ind1++) {
			for (int ind2 = 0; ind2 < dim2; ind2++) {
				for (int ind3 = 0; ind3 < dim3; ind3++) {
					input >> a(ind1, ind2, ind3);
				}
			}
		}
		sum(i, j, k) = sum(i, j, k) + a(i, j, k);
	}
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				output << sum(ind1, ind2, ind3)  << " ";
			}
		}
	}
}


void tensorAddLTensor() {
	int num, rank, dim1, dim2, dim3;

	//	input.open("test/test1_in1.txt", fstream::out);
	//	input << 1 << endl;
	//	input << 1000000 << endl;
	//	for(long i=0;i<1000000;i++){
	//		input << generateRandomNumber() << " ";
	//	}
	//	input << "\n";
	//	for(long i=0;i<1000000;i++){
	//		input << generateRandomNumber() << " ";
	//	}
	//	input.close();
	//	return;

	input.open("test/test3_in.txt", fstream::in);
	if(!input){
		cout << "Input file does not exists!\n";
		return;
	}
	output.open("test/test3_out.txt", fstream::out);
	input >> num;
	input >> rank;

	switch (rank) {
	case 0: {
		//tensor rank 0: scalar, trivial case
		float sum=0, scalar;
		for(int i=0;i<num;i++){
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
