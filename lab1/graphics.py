# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import numpy as np

x_std=[540.049, 493.836, 540.682, 540.553, 482.403, 545.950, 539.299, 546.119, 550.539, 511.323, 545.437, 547.153, 497.821, 546.397, 544.348, 487.565, 545.218, 547.074, 494.757, 550.341]
x_eig=[3.250, 3.242, 3.238, 3.241, 3.239, 3.239, 3.238, 3.249, 3.241, 3.239, 3.240, 3.241, 3.240, 3.246, 3.239, 3.241, 3.247, 3.238, 3.241, 3.246]
x_eig_nv=[6.437, 6.428, 6.439, 6.439, 6.432, 6.432, 6.433, 6.440, 6.392, 6.398, 6.393, 6.405, 6.404, 6.400, 6.402, 6.404, 6.413, 6.397, 6.399, 6.431]
y= np.arange(1,21)
plt.ylabel('time (s)')
plt.xlabel('number of experiment')
plt.plot(y,x_std,  'go', linewidth=1, markersize=1, label='Standard Matrix Multiplication')
plt.plot(y,x_eig, 'ro', linewidth=1, markersize=1, label='Eigen Math Library Vectorized')
plt.plot(y,x_eig_nv, 'bo', linewidth=1, markersize=1, label='Eigen Math Library Non Vectorized')
# plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()