#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <iostream>
#include "TensorAdd.h"

using namespace std;

void runRandomMode(){
	TensorAddRandom tAdd;
	tAdd.numTensors=2;
	tAdd.rank=3;
	tAdd.dim1 = 3;
	tAdd.dim2= 3;
	tAdd.dim3 =3;
	tAdd.tensorAddLTensor();
	tAdd.tensorAddDFE();
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
