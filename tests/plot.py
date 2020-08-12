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

	dtype = 'freq'
	tau_axis = None

	for arg in argv:
		key = arg.split('=')[0]
		value = arg.split('=')[1]

		if key == 'dtype':
			dtype = value

		elif key == 'tau':
			tau_axis = value

	# allantools options 
	if not(dtype in ['freq','phase']):
		print('./plot.py dtype=freq')
		print('./plot.py dtype=phase')
		return 0
	
	if not(tau_axis in [None, 'all','octave','decade']):
		print('./plot.py taus=[all,octave,decade]')
		return 0
	
	x = readcsv("input.csv")
	#x = allantools.noise.brown(16384, b2=1.0)
	#x = allantools.noise.white(16384*100) # b2=1.0)
	#x = randf(16384*10)

	# compute using model
	(taus, adevs, errors, ns) = allantools.adev(x, data_type=dtype, taus=tau_axis)
	
	# gui
	fig = plt.figure()
	ax1 = plt.subplot(111)
	plt.grid(True)

	# model
	ym = adevs
	ym = np.power(ym, 2)
	ym = 20 * np.log10(ym)
	ax1.semilogx(taus, ym, '+-', label='model')
	
	# output
	y = readcsv("output.csv") # avar
	y = 20 * np.log10(y) 

	if tau_axis == None:
		taus = powers_of_two_axis (len(y))

	elif tau_axis == 'decade':
		taus = powers_of_ten_axis (len(y))

	ax1.semilogx(taus, y, '+-', label='output')
	ax1.legend(loc='best')
	plt.show()

if __name__ == "__main__":
	main (sys.argv[1:])
