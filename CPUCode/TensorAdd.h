#ifndef TENSORADD_H_
#define TENSORADD_H_

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