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
		avar_freq_data_pow2 (x, y, size);
	}
}

void avar_freq_data_pow2 (float *x, float *y, unsigned int size)
{
	unsigned int i, j, k;
	unsigned int clust_size; 

	float *means;
	float acc = 0.f;

	const unsigned int nb_max_clusters = size;

	unsigned int index = (int)log2(size);

	means = (float*)malloc(nb_max_clusters * sizeof(float));

	y[0] = stdvar(x, size); // y[tau=0] is always stdvar
	
	for (i=1; i <= size; i *= 2) 
	{	// i <=> nb of clusters <=> 'tau' offset
		// <!> tau axis: powers of 2!

		clust_size = size / i;

		printf("n_clust: %d - clust_size: %d\n", i, clust_size);

		// for each cluster of data
		// compute statistical mean over cluster
		// compute avar between statistical means
		for (j=0; j < i; j++)
		{ 
			acc = 0.f;
			for (k=0; k < clust_size; k++)
			{
				acc += x[k + j*clust_size];
			} 
		
			means[j] = acc /(float)clust_size; // store mean for next calc.
		}

		// compute Allan var.
		acc = 0.f;
		for (j=0; j < i-1; j++) // y(n+1) - y(n) must exist !!
		{
			acc += powf(means[j+1] - means[j], 2); 
		}

		y[index] = acc / 2.0 / ((float)i-1.0); // normalization..
		index--;
	}

	free(means);
}

void avar_phase_data_pow2 (float *x, float *y, unsigned int size)
{
	unsigned int tau, i;

	float acc = 0.f;

	// tau=0: use all data points
	acc = 0.f;
	for (i=0; i < size-2; i++)
	{ 
		acc += powf(x[i+2] - 2*x[i+1] + x[i], 2); 
	}

	y[0] = acc / 2.0 / (float)(size-2.0); 
	
	for (tau=1; tau < size; tau *= 2) 
	{
		printf("tau: %d\n", tau); 

		acc = 0.f;
		for (i=tau; i < size/tau-2; i++)
		{ 
			acc += powf(x[tau*i+2] - 2*x[tau*i+1] + x[tau*i], 2); 
		}

		y[tau] = acc / 2.0 / (float)(size-2.0); 
		y[tau] /= (float)tau;
		y[tau] /= (float)tau;

	}
}
