#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import numpy as np
from matplotlib import pyplot as plt
from scipy import ndimage as ndi
from skimage import data, img_as_float, filters, color, feature, morphology, measure, exposure, draw



if __name__ == '__main__':
	img_count = 18
	plt.figure(figsize=(img_count, img_count), dpi=300)

	img_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "images/")
	images = []
	for x in range(1, img_count + 1):
		path = img_path+"samolot"+str(x)+".jpg" if x > 9 else img_path+"samolot0"+str(x)+".jpg"
		rgb_img = img_as_float(data.load(path))
		p2, p98 = np.percentile(rgb_img, (2, 95))
		img_rescale = exposure.rescale_intensity(rgb_img, in_range=(p2, p98))
		img = ndi.binary_fill_holes(morphology.dilation(feature.canny(filters.sobel(color.rgb2gray(img_rescale)), sigma = 1.8, low_threshold = 0.05, high_threshold= 0.19), selem=morphology.square(4)))
		borders = measure.find_contours(img, 0.5) 

		plt.subplot(6, 4, x)
		plt.axis('off')
		for border in borders:
			plt.plot(border[:, 1], border[:, 0], linewidth=0.5)
			rr, cc = draw.circle(sum(border[:, 0]) / len(border[:, 0]),
								sum(border[:, 1]) / len(border[:, 1]),
								int(max(max(border[:, 0]) - min(border[:, 0]),
								max(border[:, 1]) - min(border[:, 1])) / 20))
			rgb_img[rr, cc] = 1

		plt.imshow(rgb_img)

	plt.savefig('out.jpg',bbox_inches='tight')
	plt.close()