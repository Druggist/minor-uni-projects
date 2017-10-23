#!/usr/bin/env python
# -*- coding: utf-8 -*-

from __future__ import division
import numpy as np
from matplotlib import pyplot as plt
from sympy import *

def p1():
	x = Symbol("x")
	eq = x**3+3*x**2-10*x+24
	array = np.arange(-5,5,0.1)
	y = [eq.evalf(subs = { x : i }) for i in array]
	plt.plot(array, y)
	plt.show()
	solve(eq,x)

def p2():
	x, y = symbols("x y")
	eq = [x**2+3*y-10, 4*x-y**2+2]
	sol = solve(eq, [x, y], dict=True, check=False)
	sol

	for s in sol:
		for k, v in s.items():
			print(k, v.evalf())

def p3():
	x = Symbol("x")
	eq = sin(log(x,2))*cos(x**2)/x
	diff(eq)

def main():
	#p1()
	#p2()
	p3()

if __name__ == '__main__':
	main()
