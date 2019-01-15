#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sun Jan  6 20:06:16 2019

@author: robster
"""

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
plt.ion()

max_error = 0.1000/25
min_error = 5e-6
amount_points = 1000000
plt.close('all')
error = max_error

while(error >= min_error):
    
    a = '{:f}'.format(error)
    filename1 = 'new_phasevalues_max_error_' + a  + '.csv'
    filename2 = 'new_imagepoints_max_error_' + a  + '.csv'
    new_phasevalues = pd.read_csv(filename1)
    new_imagepoints = pd.read_csv(filename2)
    "Combine both dataframes" 
    new_data = pd.concat([new_imagepoints,new_phasevalues], axis =1)
    print('Amount of points = ' + str(new_data.size))
    b = new_data[:amount_points]
    ax = b.plot.scatter(x='u_image', y='v_image', c = 'phasevalue_ver', colormap='viridis', title='All ' + str(new_data.size) +' Points of Vertical Phasemap with max_error = ' + a)
    error = error/5
#ax.set_ylim(964,0)
    
    
#ax.set_xlim(0,1288)

