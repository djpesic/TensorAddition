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

//	start=clock();
//	tensorAddDFE(inputName, outputName);
//	end=clock();
//	elapsed_time=(end-start)/(double)CLOCKS_PER_SEC;
//	cout << "\nElapsed time dfe: " << elapsed_time << "\n";
	return 0;
}
