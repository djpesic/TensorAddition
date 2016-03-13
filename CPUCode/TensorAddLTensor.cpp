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

	Marray<float, 1> sum(dim);
	Marray<float, 1> **tensors = new Marray<float, 1>*[num];
	Index<'i'> i;
	for(long it = 0; it< num; it++){
		tensors[it]=new Marray<float, 1>(dim);
		for (long ind = 0; ind < dim; ind++) {
			input >> (*tensors[it])(ind);
		}
	}
	clock_t start = clock();
	for(long it = 0; it<dim;it++){
		sum(it)=0;
	}

	for(long it=0;it<num;it++){
		sum(i)=sum(i)+(*tensors[it])(i);
	}
	clock_t end = clock();
	double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
	cout << "Elapsed time ltensor: " << elapsed_time << "\n";
	for (long ind = 0; ind < dim; ind++) {
		output << sum(ind) << " ";
	}
	for(long ind = 0; ind<num;ind++){
		delete tensors[ind];
	}
	delete [] tensors;
}


static void addSecondRankTensors(long dim1, long dim2,long num) {
	Marray<float, 2>  sum(dim1, dim2);
	Marray<float, 2> **tensors = new Marray<float, 2>*[num];
	Index<'i'> i;
	Index<'j'> j;
	for(long it=0; it < num; it++){
		tensors[it]=new Marray<float, 2>(dim1, dim2);
		for (long ind1 = 0; ind1 < dim1; ind1++) {
			for (long ind2 = 0; ind2 < dim2; ind2++) {
				input >> (*tensors[it])(ind1, ind2);
			}
		}
	}
	clock_t start = clock();
	for(long it1 = 0; it1 < dim1; it1++)
		for(long it = 0; it<dim2;it++){
			sum(it1, it)=0;
		}
	for(long it=0; it<num; it++){
		sum(i,j) = sum(i,j) + (*tensors[it])(i,j);
	}
	clock_t end = clock();
	double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
	cout << "Elapsed time ltensor: " << elapsed_time << "\n";
	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			output << sum(ind1, ind2) << " ";
		}
	}
	for(long ind = 0; ind<num;ind++){
		delete tensors[ind];
	}
	delete [] tensors;
}

static void addThirdRankTensors(long dim1, long dim2, long dim3, long num) {
	Marray<float, 3> sum(dim1, dim2, dim3);
	Marray<float, 3> **tensors = new Marray<float, 3>*[num];
	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	for(long it=0; it < num; it++){
		tensors[it]=new Marray<float, 3>(dim1, dim2, dim3);
		for (long ind1 = 0; ind1 < dim1; ind1++) {
			for (long ind2 = 0; ind2 < dim2; ind2++) {
				for (long ind3 = 0; ind3 < dim3; ind3++) {
					input >> (*tensors[it])(ind1, ind2, ind3);
				}
			}
		}
	}
	clock_t start = clock();
	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			for (long ind3 = 0; ind3 < dim3; ind3++) {
				sum(ind1, ind2, ind3) = 0;
			}
		}
	}
	for(long it=0;it<num;it++){
		sum(i, j, k) = sum(i, j, k) +  (*tensors[it])(i, j, k);
	}
	clock_t end = clock();
	double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
	cout << "Elapsed time ltensor: " << elapsed_time << "\n";
	for (long ind1 = 0; ind1 < dim1; ind1++) {
		for (long ind2 = 0; ind2 < dim2; ind2++) {
			for (long ind3 = 0; ind3 < dim3; ind3++) {
				output << sum(ind1, ind2, ind3)  << " ";
			}
		}
	}
	for(long ind = 0; ind<num;ind++){
		delete tensors[ind];
	}
	delete [] tensors;
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
