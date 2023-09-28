# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import numpy as np

x_std_time=[]
x_eig_time=[]
x_std_clock=[]
x_eig_clock=[]


y= [100, ]
plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_std_time,  'go', linewidth=1, markersize=1, label='Standard Matrix Multiplication measured with time')
plt.plot(y,x_eig_time, 'ro', linewidth=1, markersize=1, label='Eigen Math Library Vectorized measured with time')
plt.plot(y,x_eig_clock, 'bo', linewidth=1, markersize=1, label='Eigen Math Library Vectorized measured with clock')
plt.plot(y,x_std_clock, 'yo', linewidth=1, markersize=1, label='Standard Matrix Multiplication measured with clock')
# plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

