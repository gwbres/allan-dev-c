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

	x = (float*)malloc(N*sizeof(float));
	y = (float*)malloc(N*sizeof(float));
	
	// generate input 
	randnf(x, N);
	array2csv ("input.csv", x, N);
	
	printf("######### AVAR (fract. data) ###########\n");

	// tau powers of two
	avar (x, y, N, AVAR_FREQ_DATA, TAU_AXIS_POW2);
	array2csv ("avar-freq-twos.csv", y, (int)log2(N)-1);

	// tau powers of ten
	avar (x, y, N, AVAR_FREQ_DATA, TAU_AXIS_POW10);
	array2csv ("avar-freq-decade.csv", y, (int)log10(N)-1);

	// tau='all'
	//avar (x, y, N, AVAR_FREQ_DATA, TAU_AXIS_ALL);
	//array2csv ("avar-freq-all.csv", y, N);

	printf("######### AVAR (phase data) ###########\n");

	// tau powers of two
	avar (x, y, N, AVAR_PHASE_DATA, TAU_AXIS_POW2);
	array2csv ("avar-phase-twos.csv", y, (int)log2(N)-1);

	// tau powers of ten
	avar (x, y, N, AVAR_PHASE_DATA, TAU_AXIS_POW10);
	array2csv ("avar-phase-decade.csv", y, (int)log10(N)-1);

	// tau='all'
	//avar (x, y, N, AVAR_PHASE_DATA, TAU_AXIS_ALL);
	//array2csv ("avar-phase-all.csv", y, N);

	free(x);
	free(y);
	return 0;
}
