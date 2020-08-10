#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>

void tau_axis_pow2 (int *x, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size; i++)
	{
		x[i] = (int)roundf(powf(2,i));
	}
}

void tau_axis_pow10 (int *x, unsigned int size)
{
	unsigned int i;
	for (i=0; i<size; i++)
	{
		x[i] = (int)roundf(powf(10,i));
	}
}

void tau_axis (int *x, unsigned size, uint8_t is_pow)
{
	unsigned int i;
	if (is_pow & POWER2_TAU_AXIS)
		tau_axis_pow2(x, size);

	else if (is_pow & POWER10_TAU_AXIS)
		tau_axis_pow10(x, size);
	
	else {
		for (i=0; i<size; i++)
			x[i] = i;
	}
}
