#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>

void tau_axis_pow2 (int *x, unsigned int size)
{
	unsigned int i;
	x[0] = 1;
	for (i=1; i<size; i++)
	{
		x[i] = x[i-1] * 2;
	}
}

void tau_axis_pow10 (int *x, unsigned int size)
{
	unsigned int i;
	x[0] = 1;
	for (i=1; i<size; i++)
	{
		x[i] = x[i-1] * 10;
	}
}
