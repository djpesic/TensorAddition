#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <iostream>
extern void tensorAddLTensor();
extern void tensorAddDFE();
using namespace std;
int main(){
	srand(time(NULL));
	clock_t start = clock();
	tensorAddLTensor();
	clock_t end = clock();
	double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
	cout << "Elapsed time ltensor: " << elapsed_time << "\n";
	return 0;
	start=clock();
	tensorAddDFE();
	end=clock();
	elapsed_time=(end-start)/(double)CLOCKS_PER_SEC;
	cout << "Elapsed time dfe: " << elapsed_time << "\n";
	return 0;
}
