#ifndef __TAU_H__
#define __TAU_H__

#include <stdint.h>

///////////////////////////////
//       TAU AXIS tools     //
/////////////////////////////

#define  POWER2_TAU_AXIS 0
#define POWER10_TAU_AXIS 1

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

#endif /* __TAU_H__ */
