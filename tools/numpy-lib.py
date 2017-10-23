#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

def plot1():
	x = np.linspace(-np.pi, np.pi, 100)
	y = np.sin(x)
	plt.plot(x,y)
	plt.xlim(-np.pi,np.pi)
	plt.ylim(-1.0,1.0)
	plt.title("100")
	plt.show()

def plot2():
	x = np.linspace(-np.pi, np.pi, 10)
	y = np.sin(x)
	plt.plot(x,y)
	plt.xlim(-np.pi,np.pi)
	plt.title("10")
	plt.show()

def main():
	Matrix1 = np.array([[ 1, 3, 1, 2],[ 1, 2, 5, 8],[ 3, 1, 2, 9],[ 5, 4, 2, 1]])
	Matrix1 = np.delete(np.delete(np.delete(Matrix1, 3, 0), 0, 0), 3, 1)
	Matrix2 = np.array([[ 2, 3, 1],[ 5, 1, 3]])
	Matrix2 = np.transpose(Matrix2)
	Matrix3 = np.dot(Matrix1, Matrix2)
	print(Matrix3)
	
	plot2()

if __name__ == '__main__':
	main()