#ifndef __ADEV_H__
#define __ADEV_H__

#include <stdint.h>

// TAU AXIS
#define TAU_AXIS_POW2	0
#define TAU_AXIS_POW10	1
#define TAU_AXIS_ALL		2

#define AVAR_PHASE_DATA	0
#define AVAR_FREQ_DATA	1

//////////////////////////////
//       VARIANCEs         //
////////////////////////////

// avar:
//  returns Allan deviation
//  float *x: input raw/fractionnal data
//  unsigned int size: x array allocated size
void avar (float *x, float *y, unsigned int size, uint8_t dtype, uint8_t axis); 

void avar_phase_data (float *x, float *y, unsigned int size);
void avar_phase_data_pow2 (float *x, float *y, unsigned int size);
void avar_phase_data_pow10 (float *x, float *y, unsigned int size);

void avar_freq_data (float *x, float *y, unsigned int size, uint8_t axis);

// stdvar:
//  returns standard variance
//  float *x: input data
//  unsigned int size: *x allocated size
float stdvar (float *x, unsigned int size);

//////////////////////////////
//       DEVIATIONs        //
////////////////////////////

// adev:
//  returns Allan deviation
//  float *x: input raw/fractionnal data
//  unsigned int size: x array allocated size
//  uint8_t is_fractionnal: set 0x01 if *x is fractionnal data
void adev (float *x, float *y, unsigned int size, uint8_t is_fractionnal);

// stddev
//  returns standard deviation 
//  float *x: input data
//  unsigned int size: x array allocated size
float stddev (float *x, unsigned int size);

//////////////////////////////////////////////////////////////////

// mean:
//  returns mean of *x data set
float mean (float *x, unsigned size);

// split:
//  splits *x array into **y subsets
void split (float *x, float **y, unsigned int n_clusters, unsigned int clust_size);

// avar_calc
//  returns AVAR() for input clusters **x 
float avar_calc (float **x, unsigned int n_clusters, unsigned int clust_size, uint8_t fractionnal);

#endif
