# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import numpy as np

x_eig_time_100 = [0.001, 0.001, 0.000, 0.000, 0.000, 0.000, 0.000, 0.002, 0.002, 0.002]
x_eig_time_500 = [0.017, 0.018, 0.017, 0.018, 0.017, 0.018, 0.018, 0.019, 0.017, 0.018]
x_eig_time_1000 = [0.129, 0.128, 0.129, 0.125, 0.131, 0.127, 0.127, 0.129, 0.124, 0.127]
x_eig_time_2000 = [0.972, 0.966, 0.969, 0.971, 0.969, 0.965, 0.971, 0.966, 0.974, 0.964]
x_eig_time_3000 = [3.213, 3.221, 3.220, 3.223, 3.226, 3.228, 3.216, 3.222, 3.226, 3.220]

x_std_time_100 = [0.012, 0.013, 0.011, 0.013, 0.013, 0.012, 0.013, 0.012, 0.013, 0.012]
x_std_time_500 = [1.464, 1.458, 1.474, 1.462, 1.457, 1.467, 1.460, 1.461, 1.462, 1.463]
x_std_time_1000 = [13.790, 13.991, 13.009, 13.667, 13.699, 13.174, 13.088, 13.146, 13.230, 12.798]
x_std_time_2000 = [145.585, 136.650, 152.879, 150.753, 150.741, 151.848, 150.538, 151.126, 135.097, 152.684]
x_std_time_3000 = []

x_eig_clock_100 = [0.0004, 0.0003, 0.0003, 0.0003, 0.0003, 0.0004, 0.0003, 0.0004, 0.0003, 0.0004]
x_eig_clock_500 = [0.0201, 0.0200, 0.0196, 0.0197, 0.0199, 0.0198, 0.0200, 0.0201, 0.0198, 0.199]
x_eig_clock_1000 = [0.1297, 0.1283, 0.1294, 0.1294, 0.1285, 0.1282, 0.1292, 0.1314, 0.1288, 0.1287]
x_eig_clock_2000 = [0.9728, 0.9724, 0.9738, 0.9743, 0.9733, 0.9746, 0.9787, 0.9726, 0.9738, 0.9737]
x_eig_clock_3000 = [3.2372, 3.2426, 3.2352, 3.2347, 3.2419, 3.2374, 3.2394, 3.2378, 3.2332, 3.2371]

x_std_clock_100 = [0.0116, 0.0116, 0.0117, 0.0114, 0.0116, 0.0115, 0.0113, 0.0114, 0.0118, 0.0116]
x_std_clock_500 = [1.4564, 1.4618, 1.4577, 1.4576, 1.4595, 1.4527, 1.4547, 1.4593, 1.4540, 1.4553]
x_std_clock_1000 = [12.7080, 12.6496, 12.4878, 12.6762, 13.0360, 12.6400, 12.6090, 12.6449, 12.8351, 12.6457]
x_std_clock_2000 = [146.1112, 146.3938, 132.8575, 146.0704, 146.3439, 145.6280, 133.6132, 146.2374, 148.5054, 146.5043]
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
plt.plot(y,x_eig_clock, 'bo', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with clock')
plt.plot(y,x_std_clock, 'yo', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with clock')
plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

# get time of day

x_eig_time_100 = [0.001, 0.001, 0.000, 0.000, 0.000, 0.000, 0.000, 0.002, 0.002, 0.002]
x_eig_time_500 = [0.017, 0.018, 0.017, 0.018, 0.017, 0.018, 0.018, 0.019, 0.017, 0.018]
x_eig_time_1000 = [0.129, 0.128, 0.129, 0.125, 0.131, 0.127, 0.127, 0.129, 0.124, 0.127]
x_eig_time_2000 = [0.972, 0.966, 0.969, 0.971, 0.969, 0.965, 0.971, 0.966, 0.974, 0.964]
x_eig_time_3000 = [3.213, 3.221, 3.220, 3.223, 3.226, 3.228, 3.216, 3.222, 3.226, 3.220]

x_std_time_100 = [0.012, 0.013, 0.011, 0.013, 0.013, 0.012, 0.013, 0.012, 0.013, 0.012]
x_std_time_500 = [1.464, 1.458, 1.474, 1.462, 1.457, 1.467, 1.460, 1.461, 1.462, 1.463]
x_std_time_1000 = [13.790, 13.991, 13.009, 13.667, 13.699, 13.174, 13.088, 13.146, 13.230, 12.798]
x_std_time_2000 = [145.585, 136.650, 152.879, 150.753, 150.741, 151.848, 150.538, 151.126, 135.097, 152.684]
x_std_time_3000 = []

x_eig_gtd_100 = [0.0004, 0.0003, 0.0003, 0.0004, 0.0003, 0.0003, 0.0003, 0.0003, 0.0004, 0.0003]
x_eig_gtd_500 = [0.0198, 0.0197, 0.0196, 0.0201, 0.0196, 0.0201, 0.0201, 0.0200, 0.0195, 0.0201]
x_eig_gtd_1000 = [0.1287, 0.1306, 0.1289, 0.1299, 0.1301, 0.1300, 0.1289, 0.1296, 0.1292, 0.1296]
x_eig_gtd_2000 = [0.9729, 0.9727, 0.9802, 0.9736, 0.9729, 0.9734, 0.9737, 0.9759, 0.9741, 0.9740]
x_eig_gtd_3000 = [3.2403, 3.2395, 3.2421, 3.2470, 3.2448, 3.2370, 3.2369, 3.2381, 3.2408, 3.2426]

x_std_gtd_100 = [0.0115, 0.0116, 0.0116, 0.0116, 0.0115, 0.0116, 0.0115, 0.0116, 0.0116, 0.0117]
x_std_gtd_500 = [1.4685, 1.4694, 1.4694, 1.4696, 1.4692, 1.4680, 1.4685, 1.4701, 1.4711, 1.4767]
x_std_gtd_1000 = [13.7111, 13.3080, 13.8915, 13.7515, 13.4313, 13.6422, 13.8498, 13.3587, 13.5627, 13.8420]
x_std_gtd_2000 = []
x_std_gtd_3000 = []

x_std_time=[np.mean(x_std_time_100), np.mean(x_std_time_500), np.mean(x_std_time_1000), np.mean(x_std_time_2000), np.mean(x_std_time_3000)]
x_eig_time=[np.mean(x_eig_time_100), np.mean(x_eig_time_500), np.mean(x_eig_time_1000), np.mean(x_eig_time_2000), np.mean(x_eig_time_3000)]
x_std_gtd=[np.mean(x_std_gtd_100), np.mean(x_std_gtd_500), np.mean(x_std_gtd_1000), np.mean(x_std_gtd_2000), np.mean(x_std_gtd_3000)]
x_eig_gtd=[np.mean(x_eig_gtd_100), np.mean(x_eig_gtd_500), np.mean(x_eig_gtd_1000), np.mean(x_eig_gtd_2000), np.mean(x_eig_gtd_3000)]


y= [100, 500, 1000, 2000, 3000]
plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_std_time,  'go', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with time')
plt.plot(y,x_eig_time, 'ro', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with time')
plt.plot(y,x_eig_gtd, 'bo', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with gtd')
plt.plot(y,x_std_gtd, 'yo', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with gtd')
plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

