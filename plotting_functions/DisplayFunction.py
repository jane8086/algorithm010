#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 13 23:12:08 2018

@author: robster
"""


import pandas as pd
import matplotlib.pyplot as plt
plt.ion()


filename1 = 'displaypoints_pixel.csv'
filename2 = 'imagepoints.csv'
displaypoints_pixel = pd.read_csv(filename1)
image_points = pd.read_csv(filename2)

"Clean data"
displaypoints_pixel = displaypoints_pixel.drop([' '], axis=1)
image_points = image_points.drop([' '], axis=1)
image_points.columns = ['u_image', 'v_image']

"Combine both dataframes" 
point_correspondeces = pd.concat([displaypoints_pixel,image_points], axis =1)

"Plot 2D Pixel points" 
ax1 = point_correspondeces.plot.scatter(x='x', y ='y',title='Display Points in Pixel')
ax1.set_ylim(1080,0)
ax1.set_xlim(0,1980)

"Plot 22 Image Points"
ax2 = point_correspondeces.plot.scatter(x='u_image', y ='v_image',title='Image Points in Pixel')
ax2.set_ylim(964,0)
ax2.set_xlim(0,1288)

#"Select Sub-Data where noise occur"
#subdata = point_correspondeces.query('(350 <= x < 355) & (0 <= y < 1000)')
#ax3 = subdata.plot.scatter(x='x', y ='y',title='Display Points in Pixel')
#ax4 = subdata.plot.scatter(x='u_image', y ='v_image',title='Image Points in Pixel')
#
