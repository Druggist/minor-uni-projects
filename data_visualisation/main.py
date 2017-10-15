#!/usr/bin/env python
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
from matplotlib.legend_handler import HandlerLine2D
from matplotlib import rc
import csv

def load_avg_data(path):
	with open(path, 'r') as csvfile:
		reader = csv.reader(csvfile, delimiter=',')
		next(reader)
		x = []
		y = []
		for row in reader:
			x.append(float(row[1]) / 1000)
			values = []
			iterrow = iter(row)
			next(iterrow)
			next(iterrow)
			for val in iterrow:
				values.append(float(val))
			cell = sum(values)/float(len(values)) * 100
			y.append(cell)
	return (x, y)

def load_last_row_data(path):
	with open(path, 'r') as csvfile:
		reader = csv.reader(csvfile, delimiter=',')
		x = []
		row = None
		for row in reader: pass
		iterrow = iter(row)
		next(iterrow)
		next(iterrow)
		for val in iterrow:
			x.append(float(val)*100)
	return x

def draw_line_plot(ax):
	data = load_avg_data('./data/rsel.csv')
	line1, = ax.plot(data[0], data[1], 'b-o', label='1-Evol-RS', linewidth=1, markeredgecolor='k', markevery=25)
	data = load_avg_data('./data/cel-rs.csv')
	line2, = ax.plot(data[0], data[1], 'g-v', label='1-Coev-RS', linewidth=1, markeredgecolor='k', markevery=25)
	data = load_avg_data('./data/2cel-rs.csv')
	line3, = ax.plot(data[0], data[1], 'r-D', label='2-Coev-RS', linewidth=1, markeredgecolor='k', markevery=25)
	data = load_avg_data('./data/cel.csv')
	line4, = ax.plot(data[0], data[1], 'k-s', label='1-Coev', linewidth=1, markeredgecolor='k', markevery=25)
	data = load_avg_data('./data/2cel.csv')
	line5, = ax.plot(data[0], data[1], 'm-d', label='2-Coev', linewidth=1, markeredgecolor='k', markevery=25)
	ax.axis([0, 500, 60, 100])
	ax.legend(handler_map={
		line1: HandlerLine2D(numpoints=2),
		line2: HandlerLine2D(numpoints=2),
		line3: HandlerLine2D(numpoints=2),
		line4: HandlerLine2D(numpoints=2),
		line5: HandlerLine2D(numpoints=2),
		})
	ax.set_xlabel('Rozegranych gier (x1000)')
	ax.set_ylabel('Odsetek wygranych gier [%]')
	ax.grid(linestyle=':', linewidth=1)
	ax_y = ax.twiny()
	ax_y.set_xlim([0, 200])
	ax_y.set_xticks([0, 40, 80, 120, 160, 200])
	
def draw_box_plot(ax):
	labels = list(['1-Evol-RS', '1-Coev-RS', '2-Coev-RS', '1-Coev', '2-Coev'])
	data = []
	meanpointprops = dict(marker='o', markerfacecolor='blue', markeredgecolor='black')

	data.append(load_last_row_data('./data/rsel.csv'))
	data.append(load_last_row_data('./data/cel-rs.csv'))
	data.append(load_last_row_data('./data/2cel-rs.csv'))
	data.append(load_last_row_data('./data/cel.csv'))
	data.append(load_last_row_data('./data/2cel.csv'))
	ax.boxplot(data, notch=True, bootstrap=100000, meanprops=meanpointprops, meanline=False, showmeans=True, boxprops=dict(color='blue'), flierprops=dict(marker='+', markerfacecolor='blue', markeredgecolor='blue', markersize='12'), whiskerprops=dict(color='blue', linestyle='--'))
	ax.grid(linestyle=':', linewidth=1)
	ax.yaxis.tick_right()
	ax.set_ylim([60, 100])
	ax.set_xticklabels(labels, rotation=25)

def main():
	#plt.rc('text', usetex=True)
	plt.rc('font', family='serif')
	fig, ((ax1, ax2)) = plt.subplots(nrows=1, ncols=2)
	draw_line_plot(ax1)
	draw_box_plot(ax2)
	plt.tight_layout()
	plt.show()

if __name__ == '__main__':
	main()