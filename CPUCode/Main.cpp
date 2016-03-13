#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <iostream>
extern void tensorAddLTensor(char* inputName, char* outputName);
extern void tensorAddDFE(char* inputName, char* outputName);
using namespace std;
int main(int argc, char** argv){
	char* inputName = argv[1];
	char* outputName =argv[2];
	inputName=(char*)"test/test3_in.txt";
	outputName=(char*)"test/teset1_out.txt";
	srand(time(NULL));

	tensorAddLTensor(inputName, outputName);

	tensorAddDFE(inputName, outputName);

	return 0;
}
