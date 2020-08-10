#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>
#include <tau.h>
#include <tools/tools.h>

int main (int argc, char **argv)
{
	const unsigned int N = 8192;
	float *x, *y;

	x = (float*)malloc(N*sizeof(float));
	y = (float*)malloc(log2(N)*sizeof(float));

	randnf(x, N);
	array2csv ("input.csv", x, N);

	avar (x, y, N, 0x00); 
	
	array2csv ("output.csv", y, log2(N/2));
	return 0;
}
