#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division             # Division in Python 2.7
import matplotlib
matplotlib.use('Agg')                       # So that we can render files without GUI
import matplotlib.pyplot as plt
from matplotlib import rc
import numpy as np
import math
from matplotlib import colors

def load_data(path):
	data = []
	with open(path, 'r') as file:
		obj = [int(i) for i in file.readline().split()]
		for line in file:
			data.append([float(i) for i in line.split()])
	return (obj, data)

def plot_map(dim, data):
	rc('legend', fontsize=10)

	img = np.zeros((int(dim[0]), int(dim[1]), 3))
	max_val = float(max(map(max, data)))
	for i in range(len(data)):
		for j in range(len(data[i])):
			v = float(data[i][j]) / max_val
			if j != 0:
				img[i, j] = gradient(v,float(data[i][j-1]) / max_val)
			else:
				img[i, j] = gradient(v, v)
	im = plt.imshow(img, aspect='auto')
	div = 100000 #km
	im.set_extent([0, dim[0]*dim[2]/div, dim[1]*dim[2]/div, 0])
	plt.axis([0, dim[0]*dim[2]/div, dim[1]*dim[2]/div, 0])
	plt.savefig('map.pdf')

def gradient(v, vl):
	smoothing = 0.01
	diff = 1.25

	m = 1.0
	if v > vl:
		if v - vl >= smoothing:
			m = vl / v * diff
	elif v < vl:
		if vl - v >= smoothing:
			m = vl / v / diff

	if v <= 2.0/3: return (np.clip(m*(v*3.0/2), 0, 1), np.clip(m, 0, 1), np.clip(m*(2.0/3 - v), 0, 1))
	else: return (np.clip(m, 0, 1), np.clip(m*((1 - v) * 3), 0, 1), 0)

if __name__ == '__main__':
	data = load_data("./big.dem")
	plot_map(data[0], data[1])