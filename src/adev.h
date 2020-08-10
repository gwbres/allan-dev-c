#ifndef __ADEV_H__
#define __ADEV_H__

#include <stdint.h>

//////////////////////////////
//       VARIANCEs         //
////////////////////////////

// avar:
//  returns Allan deviation
//  float *x: input raw/fractionnal data
//  unsigned int size: x array allocated size
//  uint8_t is_fractionnal: set 0x01 if *x is fractionnal data
void avar (float *x, float *y, unsigned int size, uint8_t is_fractionnal); 

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
