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

x_std_user=[539.559, 493.145, 539.558, 539.448, 481.504, 545.114, 538.340, 545.300, 549.563, 510.584, 544.489, 546.331, 497.089, 545.555, 543.359, 486.709, 544.265, 546.113, 492.075, 546.981]
x_eig_user=[3.231, 3.225, 3.223, 3.225, 3.222, 3.228, 3.220, 3.232, 3.228, 3.224, 3.228, 3.229, 3.223, 3.223, 3.227, 3.228, 3.224, 3.224, 3.227, 3.228]
x_eig_nv_user=[6.415, 6.412, 6.422, 6.418, 6.405, 6.415, 6.409, 6.414, 6.374, 6.384, 6.367, 6.382, 6.384, 6.382, 6.383, 6.382, 6.386, 6.374, 6.381, 6.416]

x_std_sys=[0.194, 0.103, 0.282, 0.239, 0.219, 0.119, 0.196, 0.101, 0.166, 0.093, 0.113, 0.118, 0.098, 0.112, 0.103, 0.088, 0.121, 0.115, 0.099, 0.105]
x_eig_sys=[0.011, 0.014, 0.011, 0.013, 0.014, 0.007, 0.014, 0.013, 0.010, 0.012, 0.009, 0.009, 0.013, 0.010, 0.009, 0.010, 0.011, 0.011, 0.011, 0.010]
x_eig_nv_sys=[0.012, 0.010, 0.010, 0.014, 0.020, 0.010, 0.011, 0.019, 0.012, 0.008, 0.018, 0.017, 0.013, 0.012, 0.013, 0.016, 0.013, 0.017, 0.012, 0.009]

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

av_std = 0
av_eig = 0
av_eig_nv = 0
av_std_user = 0
av_eig_user = 0
av_eig_nv_user = 0
av_std_sys = 0
av_eig_sys = 0
av_eig_nv_sys = 0

for i in range(len(x_std)):
    av_std += x_std[i]
    av_eig += x_eig[i]
    av_eig_nv += x_eig_nv[i]
    av_std_user += x_std_user[i]
    av_eig_user += x_eig_user[i]
    av_eig_nv_user += x_eig_nv_user[i]
    av_std_sys += x_std_sys[i]
    av_eig_sys += x_eig_sys[i]
    av_eig_nv_sys += x_eig_nv_sys[i]

av_std /= 20
av_eig /= 20
av_eig_nv /= 20
av_std_user /= 20
av_eig_user /= 20
av_eig_nv_user /= 20
av_std_sys /= 20
av_eig_sys /= 20
av_eig_nv_sys /= 20

print(av_std_sys, av_eig_sys, av_eig_nv_sys)
