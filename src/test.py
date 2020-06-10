#! /usr/bin/env python3

import allantools
import matplotlib.pyplot as plt

def readcsv (fp):
	results = []
	with open(fp, "r") as fd:
		for line in fd:
			content = line.split(",")
			for item in content:
				results.append(float(item))
	return results

if __name__ == "__main__":
	x = readcsv("input.csv")
	(taus, adevs, errors, ns) = allantools.adev(x)
	y = readcsv("output.csv")
	
	fig = plt.figure()
	ax = plt.subplot(121)
	ax.plot(taus, adevs)
	
	ax = plt.subplot(122)
	ax.plot(y[1:])
	plt.show()
