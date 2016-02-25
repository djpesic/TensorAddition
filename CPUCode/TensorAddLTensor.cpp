#include "LTensor/LTensor.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <limits.h>

using namespace std;
static fstream input, output;

double generateRandomNumber(){
	double fMin=0, fMax=10000;
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);

}

static void addFirstRankTensors(int dim) {

	Marray<double, 1> a1(dim), b1(dim), c1(dim);

	Index<'i'> i;
	for (int ind = 0; ind < dim; ind++) {
		input >> a1(ind);
	}
	for (int ind = 0; ind < dim; ind++) {
		input >> b1(ind);
	}

	c1(i) = a1(i) + b1(i);

	for (int ind = 0; ind < dim; ind++) {
		output << c1(ind) << " ";
	}


}


static void addSecondRankTensors(int dim1, int dim2) {
	Marray<double, 2> a1(dim1, dim2), b1(dim1, dim2), c1(dim1, dim2);

	Index<'i'> i;
	Index<'j'> j;
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			input >> a1(ind1, ind2);
		}
	}
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			input >> b1(ind1, ind2);
		}
	}

	c1(i,j) = a1(i,j) + b1(i, j);

	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			output << c1(ind1, ind2) << " ";
		}
	}
}



static void addThirdRankTensors(int dim1, int dim2, int dim3) {
	Marray<double, 3> a1(dim1, dim2, dim3), b1(dim1, dim2, dim3), c1(dim1, dim2, dim3);

	Index<'i'> i;
	Index<'j'> j;
	Index<'k'> k;
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				input >> a1(ind1, ind2, ind3);
			}
		}
	}
	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				input >> b1(ind1, ind2, ind3);
			}
		}
	}
	c1(i, j, k) = a1(i, j, k) + b1(i, j, k);

	for (int ind1 = 0; ind1 < dim1; ind1++) {
		for (int ind2 = 0; ind2 < dim2; ind2++) {
			for (int ind3 = 0; ind3 < dim3; ind3++) {
				output << c1(ind1, ind2, ind3)  << " ";
			}
		}
	}
}


void tensorAddLTensor() {
	int rank, dim1, dim2, dim3;

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
	output.open("test/test31_out.txt", fstream::out);
	input >> rank;

	switch (rank) {
	case 0:
		//tensor rank 0: scalar, trivial case
		double scalar1, scalar2;
		input >> scalar1 >> scalar2;
		output << scalar1 + scalar2;
		break;
	case 1:
		input >> dim1;
		addFirstRankTensors(dim1);
		break;
	case 2:
		input >> dim1 >> dim2;
		addSecondRankTensors(dim1, dim2);
		break;
	case 3:
		input >> dim1 >> dim2 >> dim3;
		addThirdRankTensors(dim1, dim2, dim3);
		break;
	default:
		cout << "Ranks higher than 3 are not supported yet\n";
	}
	input.close();
	output.close();
}
