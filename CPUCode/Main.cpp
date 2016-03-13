#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <iostream>
#include "TensorAdd.h"

using namespace std;

void runRandomMode(){
	TensorAddRandom tAdd;
	//------test------
	long numTensors[]={10, 100, 1000, 10000, 100000, 1000000};
	long numTensorsSize=6;
	long dimsSize=6;
	long dims[] ={10, 100, 1000, 10000, 100000, 1000000};
	tAdd.rank=1;
	for(long i=0;i<numTensorsSize;i++){
		for(long j=0;j<dimsSize;j++){
			tAdd.numTensors=numTensors[i];
			tAdd.dim1=dims[j];
			cout<<"======"<<"numTensors: "<<numTensors[i]<<", dim: "<< dims[j] << endl;
			tAdd.tensorAddLTensor();
			tAdd.tensorAddDFE();
			cout <<endl;
		}
	}
}

void runFile(char* inputName, char* outputName){
	TensorAddFile tAdd;
	tAdd.inputName=inputName;
	tAdd.outputName=outputName;
	tAdd.tensorAddLTensor();
	tAdd.tensorAddDFE();
}

int main(int argc, char** argv){
	char* inputName = argv[1];
	char* outputName =argv[2];
	inputName=(char*)"test/test1_in.txt";
	outputName=(char*)"test/test1_out.txt";
	srand(time(NULL));
	//	runFile(inputName, outputName);
	runRandomMode();
	return 0;
}
