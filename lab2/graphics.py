# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import numpy as np

x_eig_time_100 = [0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002]
x_eig_time_500 = [0.023, 0.021, 0.021, 0.021, 0.021, 0.021, 0.021, 0.021, 0.021, 0.021]
x_eig_time_1000 = [0.130, 0.131, 0.130, 0.130, 0.130, 0.130, 0.130, 0.130, 0.130, 0.130]
x_eig_time_2000 = [0.973, 0.974, 0.975, 0.975, 0.974, 0.979, 0.976, 0.976, 0.974, 0.973]
x_eig_time_3000 = [3.246, 3.237, 3.236, 3.237, 3.233, 3.238, 3.233, 3.243, 3.231, 3.235]

x_std_time_100 = [0.016, 0.013, 0.013, 0.013, 0.012, 0.013, 0.012, 0.012, 0.012, 0.012]
x_std_time_500 = [1.478, 1.470, 1.476, 1.469, 1.475, 1.468, 1.476, 1.468, 1.468, 1.476]
x_std_time_1000 = [13.825, 13.726, 13.927, 14.158, 14.488, 14.250, 14.199, 14.448, 14.299, 14.200]
x_std_time_2000 = []
x_std_time_3000 = []

x_eig_clock_100 = [0.0004, 0.0003, 0.0003, 0.0003, 0.0003, 0.0004, 0.0003, 0.0004, 0.0003, 0.0004]
x_eig_clock_500 = [0.0201, 0.0200, 0.0196, 0.0197, 0.0199, 0.0198, 0.0200, 0.0201, 0.0198, 0.199]
x_eig_clock_1000 = [0.1297, 0.1283, 0.1294, 0.1294, 0.1285, 0.1282, 0.1292, 0.1314, 0.1288, 0.1287]
x_eig_clock_2000 = [0.9728, 0.9724, 0.9738, 0.9743, 0.9733, 0.9746, 0.9787, 0.9726, 0.9738, 0.9737]
x_eig_clock_3000 = [3.2372, 3.2426, 3.2352, 3.2347, 3.2419, 3.2374, 3.2394, 3.2378, 3.2332, 3.2371]

x_std_clock_100 = [0.0116, 0.0116, 0.0117, 0.0114, 0.0116, 0.0115, 0.0113, 0.0114, 0.0118, 0.0116]
x_std_clock_500 = [1.4564, 1.4618, 1.4577, 1.4576, 1.4595, 1.4527, 1.4547, 1.4593, 1.4540, 1.4553]
x_std_clock_1000 = [12.7080, 12.6496, 12.4878, 12.6762, 13.0360, 12.6400, 12.6090, 12.6449, 12.8351, 12.6457]
x_std_clock_2000 = []
x_std_clock_3000 = []

x_std_time=[np.mean(x_std_time_100), np.mean(x_std_time_500), np.mean(x_std_time_1000), np.mean(x_std_time_2000), np.mean(x_std_time_3000)]
x_eig_time=[np.mean(x_eig_time_100), np.mean(x_eig_time_500), np.mean(x_eig_time_1000), np.mean(x_eig_time_2000), np.mean(x_eig_time_3000)]
x_std_clock=[np.mean(x_std_clock_100), np.mean(x_std_clock_500), np.mean(x_std_clock_1000), np.mean(x_std_clock_2000), np.mean(x_std_clock_3000)]
x_eig_clock=[np.mean(x_eig_clock_100), np.mean(x_eig_clock_500), np.mean(x_eig_clock_1000), np.mean(x_eig_clock_2000), np.mean(x_eig_clock_3000)]


y= [100, 500, 1000, 2000, 3000]
plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_std_time,  'go', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with time')
plt.plot(y,x_eig_time, 'ro', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with time')
# plt.plot(y,x_eig_clock, 'bo', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with clock')
# plt.plot(y,x_std_clock, 'yo', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with clock')
# plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

