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

	uint8_t axis = TAU_AXIS_POW10;

	x = (float*)malloc(N*sizeof(float));
	
	if (axis == TAU_AXIS_POW2)
		y = (float*)malloc((int)log2(N)*sizeof(float));

	else if (axis == TAU_AXIS_POW10)
		y = (float*)malloc((int)log10(N)*sizeof(float));
	
	else
		y = (float*)malloc((int)log10(N)*sizeof(float));

	// Test bench
	randnf(x, N);
	array2csv ("input.csv", x, N);
	avar (x, y, N, AVAR_FREQ_DATA, axis);
	
	if (axis == TAU_AXIS_POW2)
		array2csv ("output.csv", y, log2(N));
	
	else if (axis == TAU_AXIS_POW10)
		array2csv ("output.csv", y, log10(N));

	return 0;
}
