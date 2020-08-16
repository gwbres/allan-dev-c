#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>
#include <tau.h>
#include <tools/tools.h>

int main (int argc, char **argv)
{
	float *x, *y;
	const unsigned int N = 1024;
	unsigned int nb_symbols;

	uint8_t axis = TAU_AXIS_POW2;

	x = (float*)malloc(N*sizeof(float));
	
	if (axis == TAU_AXIS_POW2)
		nb_symbols = (int)log2(N)+1;
	else if (axis == TAU_AXIS_POW10)
		nb_symbols = (int)log10(N)+1;
	else
		nb_symbols = N;

	y = (float*)malloc(nb_symbols*sizeof(float));

	// Test bench
	randnf(x, N);
	array2csv ("input.csv", x, N);

	printf("######### AVAR (fract. data) ###########\n");
	avar (x, y, N, AVAR_FREQ_DATA, axis);
	
	if (axis == TAU_AXIS_POW2)
		array2csv ("avar-freq.csv", y, (int)log2(N)-1);
	else if (axis == TAU_AXIS_POW10)
		array2csv ("avar-freq.csv", y, (int)log10(N)-1);
	
	printf("######### AVAR ('phase' data) ###########\n");
	avar (x, y, N, AVAR_PHASE_DATA, axis);

	if (axis == TAU_AXIS_POW2)
		array2csv ("avar-phase.csv", y, (int)log2(N)-1);
	else if (axis == TAU_AXIS_POW10)
		array2csv ("avar-phase.csv", y, (int)log10(N)-1);

	free(x);
	free(y);
	return 0;
}
