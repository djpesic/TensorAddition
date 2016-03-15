#include "LTensor/LTensor.h"
#include "TensorAdd.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <limits.h>
#include "MaxSLiCInterface.h"
#include "Maxfiles.h"

using namespace std;

static void addFirstRankTensors(long dim, long num) {

	Marray<float, 1> sum(dim);
	Marray<float, 1> **tensors = new Marray<float, 1>*[num];
	Index<'i'> i;
	for(long it = 0; it< num; it++){
		tensors[it]=new Marray<float, 1>(dim);
		for (long ind = 0; ind < dim; ind++) {
			(*tensors[it])(ind) = TensorAdd::generateRandomNumber();
		}
	}
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	for(long it = 0; it<dim;it++){
		sum(it)=0;
	}

	for(long it=0;it<num;it++){
		sum(i)=sum(i)+(*tensors[it])(i);
	}
	clock_gettime(CLOCK_REALTIME, &end);
	struct timespec diff = TensorAdd::diff(start, end);
	printf("Elapsed time ltensor: %ld.%09ld s\n", diff.tv_sec, diff.tv_nsec);

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
				(*tensors[it])(ind1, ind2) = TensorAdd::generateRandomNumber();
			}
		}
	}
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	for(long it1 = 0; it1 < dim1; it1++)
		for(long it = 0; it<dim2;it++){
			sum(it1, it)=0;
		}
	for(long it=0; it<num; it++){
		sum(i,j) = sum(i,j) + (*tensors[it])(i,j);
	}
	clock_gettime(CLOCK_REALTIME, &end);

	struct timespec diff = TensorAdd::diff(start, end);
	printf("Elapsed time ltensor: %ld.%09ld s\n", diff.tv_sec, diff.tv_nsec);
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
					(*tensors[it])(ind1, ind2, ind3) = TensorAdd::generateRandomNumber();
				}
			}
		}
	}
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
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
	clock_gettime(CLOCK_REALTIME, &end);

	struct timespec diff = TensorAdd::diff(start, end);
	printf("Elapsed time ltensor: %ld.%09ld s\n", diff.tv_sec, diff.tv_nsec);

	for(long ind = 0; ind<num;ind++){
		delete tensors[ind];
	}
	delete [] tensors;
}


void TensorAddRandom::tensorAddLTensor() {
	switch (rank) {
	case 0: {
		//tensor rank 0: scalar, trivial case
		float sum=0, scalar;
		for(long i=0;i<numTensors;i++){
			scalar = generateRandomNumber();
			sum+=scalar;
		}
		break;
	}
	case 1:
		addFirstRankTensors(dim1,numTensors);
		break;
	case 2:
		addSecondRankTensors(dim1, dim2,numTensors);
		break;
	case 3:
		addThirdRankTensors(dim1, dim2, dim3,numTensors);
		break;
	default:
		cout << "Ranks higher than 3 are not supported yet\n";
	}
}

const long loopSize =TensorAddition_tileSize;

void TensorAddRandom::tensorAddDFE() {
	long inTensorsLen =0, inTensorLen = 0;
	float* inTensors, *sum;

	switch (rank) {
	case 0:
		//tensor rank 0: scalar, trivial case
		inTensorLen = 1;
		inTensorsLen = numTensors;
		break;
	case 1:
		inTensorLen = dim1;
		inTensorsLen = numTensors*dim1;
		break;
	case 2:
		inTensorLen = dim1*dim2;
		inTensorsLen = numTensors*dim1*dim2;
		break;
	case 3:
		inTensorLen = dim1*dim2*dim3;
		inTensorsLen = numTensors*dim1*dim2*dim3;
		break;
	default:
		cout << "Ranks higher than 3 are not supported yet\n";
		return ;
	}
	//prepare data for DFE

	long numZeroes = loopSize- inTensorLen % loopSize;
	inTensors = new float[inTensorsLen+numZeroes*numTensors];
	long skipSize = loopSize*(numTensors-1);
	long numLoaded=0;// counts to loopSize
	long numLoaded1=0;//counts to tensor length
	long offset=0;
	long cnt=0;
	float data;
	for(long i=0;i<inTensorsLen;i++){
		data = generateRandomNumber();
		inTensors[cnt]=data;
		cnt++;
		numLoaded++;
		numLoaded1++;
		if(numLoaded==loopSize){
			cnt+=skipSize;
			numLoaded=0;
		}
		if(numLoaded1==inTensorLen){
			for(long j=0;j<numZeroes;j++){
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
	inTensorsLen+=numZeroes*numTensors;
	sum = new float[inTensorLen];
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	TensorAddition(inTensorsLen, inTensorLen, numTensors, inTensors, sum);
	clock_gettime(CLOCK_REALTIME, &end);

	struct timespec diff = TensorAdd::diff(start, end);
	printf("Elapsed time dfe: %ld.%09ld s\n", diff.tv_sec, diff.tv_nsec);

	delete[] inTensors;
	delete[] sum;
}

