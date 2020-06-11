#! /usr/bin/env python3

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

if __name__ == "__main__":
	#x = readcsv("input.csv")
	x = allantools.noise.brown(16384, b2=1.0)
	x = allantools.noise.white(16384*100) # b2=1.0)
	x = randf(16384*10)
	x -= np.mean(x) # remove DC
	#(taus, adevs, errors, ns) = allantools.adev(x)
	
	fig = plt.figure()
	ax = plt.subplot(121)
	ax.plot(psd(x, 1024))
	ax = plt.subplot(122)
	#ax.plot(taus, np.power(adevs,2))
	plt.grid(True)
	
	y = readcsv("output.csv")
	#ax = plt.subplot(121)
	#ax.plot(powers_of_two_axis(len(y)), y)
	#ax.plot(powers_of_two_axis(len(y)), y[::-1])
	plt.grid(True)
	plt.show()
