#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "adev.h"
#include "tools.h"

int main (int argc, char **argv)
{
	const unsigned int N = 8192;
	float *x, *avar;
	x = (float*)malloc(N*sizeof(float));
	avar = (float*)malloc(log2(N)*sizeof(float));

	randnf(x, N);
	array2csv("input.csv", x, N);
	avar_tau_pow2 (x, avar, N, 0x01); 
	array2csv("output.csv", avar, log2(N/2));
	return 0;
}
