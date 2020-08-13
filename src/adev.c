#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <adev.h>

float mean (float *x, unsigned int size)
{
	unsigned int i;
	float acc = 0.f;
	for (i=0; i<size; i++)
	{
		acc += x[i];
	}

	return acc / (float)size;
}

float stdvar (float *x, unsigned int size)
{
	unsigned int i;
	
	float acc = 0.f;
	float m = mean(x, size);
	
	for (i=0; i<size; i++)
	{
		acc += powf(x[i] - m, 2); 	
	}

	return acc / (float)size;
}

void avar (float *x, float *y, unsigned int size, uint8_t dtype, uint8_t axis) 
{
	if (dtype == AVAR_PHASE_DATA) {
		avar_phase_data_pow2 (x, y, size);
	} else {
		avar_freq_data (x, y, size, axis);
	}
}

void avar_freq_data (float *x, float *y, unsigned int size, uint8_t axis)
{
	unsigned int i = 1, j, k;
	unsigned int clust_size; 

	float *means;
	float acc = 0.f;
	
	unsigned int index;
	unsigned max_nb_of_clusters;

	y[0] = stdvar(x, size); // y[tau=0] is always stdvar
	
	// last index
	if (axis == TAU_AXIS_POW2) {
		index = (int)log2(size);
		max_nb_of_clusters = (int)log2(size);
	} else if (axis == TAU_AXIS_POW10) {
		index = (int)log10(size);
		max_nb_of_clusters = (int)log10(size);
	} else {
		index = size;
		max_nb_of_clusters = size;
	}
		
	means = (float*)malloc(max_nb_of_clusters * sizeof(float)); 
	
	while (i <= size)
	{
		// i: nb of clusters := tau offset
		clust_size = size / i;
		printf("n_clust: %d - clust_size: %d\n", i, clust_size);

		// compute statistical mean for each cluster 
		for (j=0; j < i; j++)
		{ 
			acc = 0.f;
			for (k=0; k < clust_size; k++)
			{
				acc += x[k + j*clust_size];
			} 
		
			means[j] = acc /(float)clust_size; // storage
		}

		// compute Allan var.
		acc = 0.f;
		for (j=0; j < i-1; j++) // y(n+1) - y(n)!!
		{
			acc += powf(means[j+1] - means[j], 2); 
		}

		y[index] = acc / 2.0 / ((float)i-1.0); // normalization..
		index--;

		if (axis == TAU_AXIS_POW2)
			i *= 2;
		else
			i *= 10; // powers of ten
	}

	free(means);
}

void avar_phase_data_pow2 (float *x, float *y, unsigned int size)
{
	unsigned int tau = 1, i;
	unsigned int index = 0;

	float acc;

/*
    long i, n, stride;
    double sum, v;

    stride = ovlp ? 1 : tau;
    sum = n = 0;
    for (i = 0; (i + 2*tau) < count; i += stride) {
        v = data[i + 2*tau] - 2 * data[i + tau] + data[i];
        sum += v * v;
        n += 1;
    }
    sum /= 2.0;

    if (terms != NULL) { *terms = n; }
    if (n < ADEV_MIN_SAMPLES) { return 0.0; }

    return sqrt(sum / n) / tau;
*/

	while (tau < size)
	{
		acc = 0.f;
		printf("tau: %d\n", tau);

		for (i=0; i < size-2*tau; i += tau) // i+2tau exists
		{ 
			acc += powf(x[i] - 2*x[i+tau] + x[i + 2*tau], 2); 
		}

		y[index] = acc / 2.0; 
		y[index] /= (float)tau;
		index++;

		tau *= 2; // pow2 axis
	}
}
