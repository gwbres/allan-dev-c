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

// avar()
//  returns Allan deviation
//  float *x: input data
//  unsigned int size: x array allocated size
// 
//  uint8_t dtype:
//    1: AVAR_PHASE_DATA: use this value for raw data (raw phase, raw sensor..)
//    2: AVAR_FREQ_DATA: use this value for fractionnal data (delta f /f) 
//
//  uint8_t axis:
//    tau axis configuration, 
//    TAU_AXIS_POW2: compute AVAR for tau in powers of two (faster)
//    TAU_AXIS_POW10: compute AVAR for tau in powers of ten (faster)
//    TAU_AXIS_ALL: compute AVAR for all possible tau values 
void avar (float *x, float *y, unsigned int size, uint8_t dtype, uint8_t axis);

// oavar()
//  returns Allan deviation
//  float *x: input data
//  unsigned int size: x array allocated size
// 
//  uint8_t dtype:
//    1: AVAR_PHASE_DATA: use this value for raw data (raw phase, raw sensor..)
//    2: AVAR_FREQ_DATA: use this value for fractionnal data (delta f /f) 
//
//  uint8_t axis:
//    tau axis configuration, 
//    TAU_AXIS_POW2: compute AVAR for tau in powers of two (faster)
//    TAU_AXIS_POW10: compute AVAR for tau in powers of ten (faster)
//    TAU_AXIS_ALL: compute AVAR for all possible tau values 
void oavar (float *x, float *y, unsigned int size, uint8_t dtype, uint8_t axis);

// avar_phase_data()
//  returns Allan deviation, intended to be used against raw data (radians, angles..)
//  float *x: input data
//  unsigned int size: x array allocated size
//  float *y: output
//
//  uint8_t axis:
//    tau axis configuration, 
//    TAU_AXIS_POW2: compute AVAR for tau in powers of two (faster)
//    TAU_AXIS_POW10: compute AVAR for tau in powers of ten (faster)
//    TAU_AXIS_ALL: compute AVAR for all possible tau values 
//
//  uint8_t overlapping
//   0x00: disable overlapping (= AVAR)
//   0x01: enable overlapping  (= OAVAR)
void avar_phase_data (float *x, float *y, unsigned int size, uint8_t axis, uint8_t overlapping);

// avar_freq_data()
//  returns Allan deviation, intended to be used against fractionnal data (fractionnal frequency..)
//  float *x: input data
//  unsigned int size: x array allocated size
//  float *y: output
//
//  uint8_t axis:
//    tau axis configuration, 
//    TAU_AXIS_POW2: compute AVAR for tau in powers of two (faster)
//    TAU_AXIS_POW10: compute AVAR for tau in powers of ten (faster)
//    TAU_AXIS_ALL: compute AVAR for all possible tau values 
void avar_freq_data (float *x, float *y, unsigned int size, uint8_t axis, uint8_t overlapping);

///////////////////////////////
//       DEVIATIONs         //
/////////////////////////////

// adev()
// returns sqrt(avar())
// it is more efficient to call avar() and perform sqrt() in post processing
void adev (float *x, float *y, unsigned int size, uint8_t dtype, uint8_t axis);

// oadev()
// returns sqrt(avar())
// it is more efficient to call avar() and perform sqrt() in post processing
void oadev (float *x, float *y, unsigned int size, uint8_t dtype, uint8_t axis);

//////////////////////////
//       OTHER         //
////////////////////////

// mean()
//  returns mean of *x data set
float mean (float *x, unsigned size);

// stdvar()
//  returns standard variance of *x data serie
//  float *x: input data
//  unsigned int size: *x array size 
float stdvar (float *x, unsigned int size);

// stddev()
//  returns standard deviation of *x data serie
//  float *x: input data
//  unsigned int size: *x array size 
float stddev (float *x, unsigned int size);

#endif
