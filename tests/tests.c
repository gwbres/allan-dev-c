#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>
#include <tau.h>
#include <tools/tools.h>

int main (int argc, char **argv)
{
	const unsigned int N = 128;
	float *x, *y;

	x = (float*)malloc(N*sizeof(float));
	y = (float*)malloc(N*sizeof(float));

	randnf(x, N);
	array2csv ("input.csv", x, N);

	avar (x, y, N, AVAR_PHASE_DATA, TAU_AXIS_POW2); 
	
	array2csv ("output.csv", y, log2(N/2));
	return 0;
}
