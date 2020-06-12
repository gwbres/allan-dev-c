#ifndef __ADEV_H__
#define __ADEV_H__

#include <stdint.h>

///////////////////////////////
//       TAUs               //
/////////////////////////////

// tau_axis:
//  creates Tau axis of requested size
//  axis = DEFAULT_TAU_AXIS:
//		+ creates a tau axis ranging from {0:size-1}

//  axis = POWER2_TAU_AXIS:
//		+ creates a tau axis rangin from {2^0,2^size-1}

//  axis = POWER10_TAU_AXIS:
//		+ creates a tau axis rangin from {10^0,10^size-1}
void tau_axis (int *tau, unsigned int size, uint8_t axis);

// tau_axis_pow2:
//  creates a Tau axis made only of powers of 2
void tau_axis_pow2 (int *tau, unsigned int size);

// tau_axis:
//  creates a Tau axis made only of powers of 10
void tau_axis_pow10 (int *tau, unsigned int size);

//////////////////////////////
//       VARIANCEs         //
////////////////////////////

// avar:
//  returns Allan deviation
//  float *x: input raw/fractionnal data
//  unsigned int size: x array allocated size
//  uint8_t is_fractionnal: set 0x01 if *x is fractionnal data
void avar_tau_pow2 (float *x, float *y, unsigned int size, uint8_t is_fractionnal); 

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
void adev_tau_pow2 (float *x, float *y, unsigned int size, uint8_t is_fractionnal);

// stddev
//  returns standard deviation 
//  float *x: input data
//  unsigned int size: x array allocated size
float stddev (float *x, unsigned int size);

//////////////////////////////////////////////////////////////////

#define  POWER2_TAU_AXIS 0
#define POWER10_TAU_AXIS 1

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
