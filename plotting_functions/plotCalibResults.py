#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec 13 23:12:08 2018

@author: robster
"""


import pandas as pd
import matplotlib.pyplot as plt
plt.ion()


filename1 = 'displaypoints_world_mm_calibrated.csv'
filename2 = 'imagepoints_calibrated.csv'
displaypoints_pixel = pd.read_csv(filename1)
image_points = pd.read_csv(filename2)

"Combine both dataframes" 
point_correspondeces = pd.concat([displaypoints_pixel,image_points], axis =1)

"Plot 2D Image points" 
ax1 = point_correspondeces.plot.scatter(x='x', y ='y',title='Display Points in Pixel', marker='x')
ax1.set_ylim(1080,0)
ax1.set_xlim(0,1980)

"Plot 3D World Points"
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(point_correspondeces['x_mm'], point_correspondeces['y_mm'], point_correspondeces['y_mm'], c='r', marker='x')

