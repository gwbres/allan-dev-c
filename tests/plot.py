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

	vartypes = ['avar','oavar']
	tau_axis = None

	for arg in argv:
		key = arg.split('=')[0]
		value = arg.split('=')[1]

		if key == 'taus':
			tau_axis = value

		elif key == 'var':
			toKeep = value
			toRemove = []
			for i in range (0, len(vartypes)):
				if vartypes[i] != toKeep:
					toRemove.append(i)

			for idx in toRemove[::-1]:
				del vartypes[idx]

	# allantools options 
	if not(tau_axis in [None, 'all','octave','decade']):
		print('./plot.py taus=[all,octave,decade]')
		return 0
	
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

		for dtype in ['phase','freq']:

			# generate model 
			if vartype == 'avar':
				if tau_axis == 'all':
					(taus, ym, errors, ns) = allantools.adev(x, data_type=dtype, taus='all')
				elif tau_axis == 'decade':
					(taus, ym, errors, ns) = allantools.adev(x, data_type=dtype, taus='decade')
				elif tau_axis == 'octave':
					(taus, ym, errors, ns) = allantools.adev(x, data_type=dtype, taus='octave')
				else:
					(taus, ym, errors, ns) = allantools.adev(x, data_type=dtype)

			elif vartype == 'oavar':
				if tau_axis == 'all':
					(taus, ym, errors, ns) = allantools.oadev(x, data_type=dtype, taus='all')
				elif tau_axis == 'decade':
					(taus, ym, errors, ns) = allantools.oadev(x, data_type=dtype, taus='decade')
				elif tau_axis == 'octave':
					(taus, ym, errors, ns) = allantools.oadev(x, data_type=dtype, taus='octave')
				else:
					(taus, ym, errors, ns) = allantools.oadev(x, data_type=dtype)

			ym = np.power(ym, 2) # adev compared to avar
			ym = 20 * np.log10(ym)
			ax1.semilogx(taus, ym, '+-', label="{:s} '{:s}' model".format(vartype, dtype))
			
			# output
			y = readcsv("{:s}-{:s}.csv".format(vartype, dtype)) 
			y = 20 * np.log10(y) 

			if tau_axis == None:
				taus = powers_of_two_axis (len(y))

			elif tau_axis == 'decade':
				taus = powers_of_ten_axis (len(y))
			
			else:
				taus = np.linspace(0,len(y),len(y),dtype='int') 

			ax1.semilogx(taus, y, '+', label="{:s} '{:s}'".format(vartype, dtype))
			ax1.legend(loc='best')

			# tb
			error = 0
			max_tol = 0.01

			print("-------- {:s} test -------".format(dtype))
			for i in range (0, min(len(ym),len(y))):
				e = abs(y[i] - ym[i])
				if e > max_tol:
					error += 1
					print("tau: {:d} error: {:.3e} dB".format(taus[i], e))

			if error > 0:
				print("failed")
			else:
				print("passed")
			print("---------------------")
			
	plt.show()
		
if __name__ == "__main__":
	main (sys.argv[1:])
