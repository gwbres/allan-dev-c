#! /usr/bin/env python3

import sys

import math
import numpy as np
import matplotlib.pyplot as plt

import allantools

def readcsv (fp):
	results = []
	with open(fp, "r") as fd:
		for line in fd:
			content = line.split(",")
			for item in content:
				results.append(float(item))
	return results

def tau_powers_of_two (N):
	tau = []
	index = 1
	for i in range (0, N): 
		tau.append(index)
		index *= 2 
	return tau

def tau_powers_of_ten (N):
	tau = []
	index = 1
	for i in range (0, N): 
		tau.append(index)
		index *= 10
	return tau

def psd (x, n_avg):
	size_split = len(x)//n_avg
	avg = np.zeros(size_split)
	for i in range (0, n_avg):
		splitted = x[size_split:2*size_split]
		avg += np.asarray(splitted)
	avg /= n_avg
	xf = np.fft.rfft(splitted) 
	xf = np.power(np.real(xf) + np.imag(xf), 2)
	return 10*np.log10(xf)

def randf(n):
	result=[]
	for i in range (0, n):
		result.append(np.random.randint(0,high=100)/100)
	return result

def testbench (title, tau, y, ym, toldB=1e-6):
	print(" ####### {:s} ######## ".format(title))
	max_digits_tau = int(np.log10(max(tau)))
	tau_format = '{:'+str(max_digits_tau+1)+'}'
	for i in range (0, min(len(y),len(ym))):
		string = 'tau ' + tau_format.format(int(tau[i])) + ' | '
		
		error = abs(y[i] - ym[i])
		string += 'error {:10.3e} dB | '.format(error)

		string += '\033[1m' # BOLD
		if error > toldB:
			string += '\033[91m' # RED
			string += u'ERROR  \U0001F5F7'
		else:
			string += '\033[92m' # GREEN
			string += u'PASSED \U0001F5F9'

		string += '\033[0m' # ENDC
		print(string)

def main (argv):

	datatypes = ['phase','freq']
	vartypes = ['avar','oavar']
	tau_axis = ['twos', 'decade']

	for arg in argv:
		key = arg.split('=')[0]
		value = arg.split('=')[1]

		if key == 'tau':
			toKeep = value
			toRemove = []
			for i in range (0, len(tau_axis)):
				if tau_axis[i] != toKeep:
					toRemove.append(i)

			for idx in toRemove[::-1]:
				del tau_axis[idx]

		elif key == 'var':
			toKeep = value
			toRemove = []
			for i in range (0, len(vartypes)):
				if vartypes[i] != toKeep:
					toRemove.append(i)

			for idx in toRemove[::-1]:
				del vartypes[idx]

		elif key == 'data':
			toKeep = value
			toRemove = []
			for i in range (0, len(datatypes)):
				if datatypes[i] != toKeep:
					toRemove.append(i)

			for idx in toRemove[::-1]:
				del datatypes[idx]

	x = readcsv("input.csv") # read input
	
	# gui
	fig = plt.figure()
	ax1 = plt.subplot(111)
	plt.grid(True)

	for vartype in vartypes: 
		for dtype in datatypes: 
			for axis in tau_axis:

				# generate model 
				if vartype == 'avar':
					if axis == 'twos':
						(taus, ym, errors, ns) = allantools.adev(x, data_type=dtype)
					elif axis == 'decade':
						(taus, ym, errors, ns) = allantools.adev(x, data_type=dtype, taus='decade')

				elif vartype == 'oavar':
					if axis == 'twos':
						(taus, ym, errors, ns) = allantools.oadev(x, data_type=dtype)
					elif axis == 'decade':
						(taus, ym, errors, ns) = allantools.oadev(x, data_type=dtype, taus='decade')

				ym = np.power(ym, 2) # adev compared to avar
				ym = 20 * np.log10(ym)
				ax1.semilogx(taus, ym, '+-', label="{:s} '{:s}' {:s} model".format(vartype, dtype, axis))
			
				# output
				y = readcsv("{:s}-{:s}-{:s}.csv".format(
					vartype, 
					dtype,
					axis
				))

				y = 20 * np.log10(y) 

				#if axis == 'twos':
				#	taus = tau_powers_of_two(len(y)) 
				#elif axis == 'decade':
				#	taus = tau_powers_of_ten(len(y)) 

				ax1.semilogx(taus, y, '+', label="{:s} '{:s}' {:s}".format(vartype, dtype, axis))
				ax1.legend(loc='best')

				title = 'variance: {:s} - axis: {:s} - data: {:s}'.format(vartype, axis, dtype) 
				testbench (title, taus, y, ym, toldB=1e-2)

	plt.show()
		
if __name__ == "__main__":
	main (sys.argv[1:])
