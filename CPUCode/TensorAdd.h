#ifndef TENSORADD_H_
#define TENSORADD_H_
#include "time.h"
class TensorAdd {
public:
	long numTensors;
	int rank;
	long dim1, dim2, dim3;

	virtual void tensorAddLTensor()=0;
	virtual void tensorAddDFE()=0;

	static float generateRandomNumber() {
		float fMin=0, fMax=10000;
		float f = (float)rand() / RAND_MAX;
		return fMin + f * (fMax - fMin);

	}

	static struct timespec diff(struct timespec start, struct timespec finish) {
		struct timespec diff;
		if ((finish.tv_nsec < start.tv_nsec)) {
			diff.tv_sec  = finish.tv_sec  - start.tv_sec  - 1;
			diff.tv_nsec = finish.tv_nsec - start.tv_nsec + 1000000000;
		} else {
			diff.tv_sec  = finish.tv_sec  - start.tv_sec;
			diff.tv_nsec = finish.tv_nsec - start.tv_nsec;
		}

		return diff;
	}
};

class TensorAddFile:public TensorAdd {
public:
	char* inputName, *outputName;
	void tensorAddLTensor();
	void tensorAddDFE();
};

class TensorAddRandom:public TensorAdd {
public:
	void tensorAddLTensor();
	void tensorAddDFE();
};

#endif /* TENSORADD_H_ */
