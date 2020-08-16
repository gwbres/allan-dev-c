#! /usr/bin/env python3

import sys

import allantools
import numpy as np
import matplotlib.pyplot as plt

def readcsv (fp):
	results = []
	with open(fp, "r") as fd:
		for line in fd:
			content = line.split(",")
			for item in content:
				results.append(float(item))
	return results

def powers_of_two_axis (N):
	tau = []
	index = 1
	for i in range (0, N):
		tau.append(index)
		index *= 2 
	return tau

def powers_of_ten_axis (N):
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

	# read input
	x = readcsv("input.csv")
	#x = allantools.noise.brown(16384, b2=1.0)
	#x = allantools.noise.white(16384*100) # b2=1.0)
	
	# gui
	fig = plt.figure()
	ax1 = plt.subplot(111)
	plt.grid(True)

	for vartype in vartypes: 

		print("VAR: {:s}".format(vartype))

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

				ax1.semilogx(taus, y, '+', label="{:s} '{:s}' {:s}".format(vartype, dtype, axis))
				ax1.legend(loc='best')

				# tb
				error = 0
				max_tol = 0.01

				print("-------- {:s} test -------".format(dtype))
				for i in range (0, min(len(ym),len(y))):
					e = abs(y[i] - ym[i])
					if e > max_tol:
						error += 1
						print("tau: {:d} error: {:.3e} dB".format(int(taus[i]), e))

				if error > 0:
					print("failed")
				else:
					print("passed")
				print("---------------------")
			
	plt.show()
		
if __name__ == "__main__":
	main (sys.argv[1:])
