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
x_std_time_3000 = [539.559, 493.145, 539.558, 539.448, 481.504, 545.114, 538.340, 545.300, 549.563, 510.584]

x_eig_clock_100 = [0.0004, 0.0003, 0.0003, 0.0003, 0.0003, 0.0004, 0.0003, 0.0004, 0.0003, 0.0004]
x_eig_clock_500 = [0.0201, 0.0200, 0.0196, 0.0197, 0.0199, 0.0198, 0.0200, 0.0201, 0.0198, 0.199]
x_eig_clock_1000 = [0.1297, 0.1283, 0.1294, 0.1294, 0.1285, 0.1282, 0.1292, 0.1314, 0.1288, 0.1287]
x_eig_clock_2000 = [0.9728, 0.9724, 0.9738, 0.9743, 0.9733, 0.9746, 0.9787, 0.9726, 0.9738, 0.9737]
x_eig_clock_3000 = [3.2372, 3.2426, 3.2352, 3.2347, 3.2419, 3.2374, 3.2394, 3.2378, 3.2332, 3.2371]

x_std_clock_100 = [0.0116, 0.0116, 0.0117, 0.0114, 0.0116, 0.0115, 0.0113, 0.0114, 0.0118, 0.0116]
x_std_clock_500 = [1.4564, 1.4618, 1.4577, 1.4576, 1.4595, 1.4527, 1.4547, 1.4593, 1.4540, 1.4553]
x_std_clock_1000 = [12.7080, 12.6496, 12.4878, 12.6762, 13.0360, 12.6400, 12.6090, 12.6449, 12.8351, 12.6457]
x_std_clock_2000 = [146.1112, 146.3938, 132.8575, 146.0704, 146.3439, 145.6280, 133.6132, 146.2374, 148.5054, 146.5043]
x_std_clock_3000 = [510.6981, 468.8524, 500.6007, 516.7391, 465.7703, 505.5561, 517.9062, 466.9684, 502.9417, 517.0433]

x_std_time=[np.mean(x_std_time_100), np.mean(x_std_time_500), np.mean(x_std_time_1000), np.mean(x_std_time_2000), np.mean(x_std_time_3000)]
x_eig_time=[np.mean(x_eig_time_100), np.mean(x_eig_time_500), np.mean(x_eig_time_1000), np.mean(x_eig_time_2000), np.mean(x_eig_time_3000)]
x_std_clock=[np.mean(x_std_clock_100), np.mean(x_std_clock_500), np.mean(x_std_clock_1000), np.mean(x_std_clock_2000), np.mean(x_std_clock_3000)]
x_eig_clock=[np.mean(x_eig_clock_100), np.mean(x_eig_clock_500), np.mean(x_eig_clock_1000), np.mean(x_eig_clock_2000), np.mean(x_eig_clock_3000)]

x_std_time_std=[np.std(x_std_time_100), np.std(x_std_time_500), np.std(x_std_time_1000), np.std(x_std_time_2000), np.std(x_std_time_3000)]
x_eig_time_std=[np.std(x_eig_time_100), np.std(x_eig_time_500), np.std(x_eig_time_1000), np.std(x_eig_time_2000), np.std(x_eig_time_3000)]
x_std_clock_std=[np.std(x_std_clock_100), np.std(x_std_clock_500), np.std(x_std_clock_1000), np.std(x_std_clock_2000), np.std(x_std_clock_3000)]
x_eig_clock_std=[np.std(x_eig_clock_100), np.std(x_eig_clock_500), np.std(x_eig_clock_1000), np.std(x_eig_clock_2000), np.std(x_eig_clock_3000)]


# for i in range(len(x_std_time)):
#     print(x_eig_clock[i])

# for i in range(len(x_std_time_std)):
#     print(x_eig_clock_std[i])


y= [100, 500, 1000, 2000, 3000]
plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_std_time,  'go-', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with time')
plt.plot(y,x_eig_time, 'ro-', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with time')
plt.plot(y,x_eig_clock, 'bo-', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with clock')
plt.plot(y,x_std_clock, 'yo-', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with clock')
plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

# get time of day 

x_eig_gtd_100_d = [0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001, 0.0002]
x_eig_gtd_500_d = [0.0022, 0.0022, 0.0022, 0.0022, 0.0022, 0.0023, 0.0021, 0.0021, 0.0022, 0.0022]
x_eig_gtd_1000_d = [0.0077, 0.0069, 0.0072, 0.0068, 0.0068, 0.0075, 0.0070, 0.0070, 0.0077, 0.0069]
x_eig_gtd_2000_d = [0.0263, 0.0263, 0.0262, 0.0254, 0.0259, 0.0264, 0.0258, 0.0260, 0.0256, 0.0258]
x_eig_gtd_3000_d = [0.0586, 0.0583, 0.0581, 0.0574, 0.0580, 0.0586, 0.0582, 0.0583, 0.0588, 0.0583]

x_std_gtd_100_d = [0.0013, 0.0013, 0.0013, 0.0013, 0.0012, 0.0012, 0.0012, 0.0012, 0.0012, 0.0012]
x_std_gtd_500_d = [0.0205, 0.0205, 0.0205, 0.0204, 0.0209, 0.0205, 0.0208, 0.0207, 0.0205, 0.0203]
x_std_gtd_1000_d = [0.0765, 0.0756, 0.0755, 0.0749, 0.0751, 0.0747, 0.0751, 0.0747, 0.0761, 0.0745]
x_std_gtd_2000_d = [0.2943, 0.2854, 0.2891, 0.2866, 0.2855, 0.2881, 0.2863, 0.2872, 0.2854, 0.2854]
x_std_gtd_3000_d = [0.6678, 0.6675, 0.6729, 0.6798, 0.6741, 0.6614, 0.6624, 0.6725, 0.6621, 0.6961]

x_eig_gtd_100_c = [0.0002, 0.0003, 0.0002, 0.0002, 0.0003, 0.0002, 0.0002, 0.0002, 0.0002, 0.0003]
x_eig_gtd_500_c = [0.0180, 0.0175, 0.0175, 0.0177, 0.0175, 0.0174, 0.0173, 0.0173, 0.0178, 0.0176]
x_eig_gtd_1000_c = [0.1241, 0.1221, 0.1219, 0.1223, 0.1223, 0.1215, 0.1217, 0.1226, 0.1221, 0.1223]
x_eig_gtd_2000_c = [0.9478, 0.9469, 0.9458, 0.9507, 0.9467, 0.9500, 0.9479, 0.9466, 0.9458, 0.9463]
x_eig_gtd_3000_c = [3.1818, 3.1811, 3.1807, 3.1835, 3.1769, 3.1888, 3.1814, 3.1840, 3.1820, 3.1835]

x_std_gtd_100_c = [0.0103, 0.0103, 0.0103, 0.0103, 0.0104, 0.0104, 0.0104, 0.0104, 0.0102, 0.0102]
x_std_gtd_500_c = [1.4475, 1.4479, 1.4495, 1.4574, 1.4506, 1.4502, 1.4491, 1.4534, 1.4566, 1.4477]
x_std_gtd_1000_c = [13.3742, 12.7494, 13.3793, 13.8533, 12.7560, 13.0284, 13.0768, 14.8608, 13.9935, 13.9654]
x_std_gtd_2000_c = [148.2331, 149.8140, 151.0924, 133.9369, 150.7466, 150.2961, 147.2977, 133.9187, 149.4663, 148.8732]
x_std_gtd_3000_c = [526.6722, 545.9185, 509.4830, 530.8198, 564.4460, 503.6744, 542.6650, 545.3361, 496.6570, 529.6580]


x_eig_gtd_100 = [x_eig_gtd_100_d[i] + x_eig_gtd_100_c[i] for i in range(len(x_eig_gtd_100_d))]
x_eig_gtd_500 = [x_eig_gtd_500_d[i] + x_eig_gtd_500_c[i] for i in range(len(x_eig_gtd_500_d))]
x_eig_gtd_1000 = [x_eig_gtd_1000_d[i] + x_eig_gtd_1000_c[i] for i in range(len(x_eig_gtd_1000_d))]
x_eig_gtd_2000 = [x_eig_gtd_2000_d[i] + x_eig_gtd_2000_c[i] for i in range(len(x_eig_gtd_2000_d))]
x_eig_gtd_3000 = [x_eig_gtd_3000_d[i] + x_eig_gtd_3000_c[i] for i in range(len(x_eig_gtd_3000_d))]

x_std_gtd_100 = [x_std_gtd_100_d[i] + x_std_gtd_100_c[i] for i in range(len(x_std_gtd_100_d))]
x_std_gtd_500 = [x_std_gtd_500_d[i] + x_std_gtd_500_c[i] for i in range(len(x_std_gtd_500_d))]
x_std_gtd_1000 = [x_std_gtd_1000_d[i] + x_std_gtd_1000_c[i] for i in range(len(x_std_gtd_1000_d))]
x_std_gtd_2000 = [x_std_gtd_2000_d[i] + x_std_gtd_2000_c[i] for i in range(len(x_std_gtd_2000_d))]
x_std_gtd_3000 = [x_std_gtd_3000_d[i] + x_std_gtd_3000_c[i] for i in range(len(x_std_gtd_3000_d))]


x_std_gtd=[np.mean(x_std_gtd_100), np.mean(x_std_gtd_500), np.mean(x_std_gtd_1000), np.mean(x_std_gtd_2000), np.mean(x_std_gtd_3000)]
x_eig_gtd=[np.mean(x_eig_gtd_100), np.mean(x_eig_gtd_500), np.mean(x_eig_gtd_1000), np.mean(x_eig_gtd_2000), np.mean(x_eig_gtd_3000)]
print(x_std_gtd, x_eig_gtd)


plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_std_time,  'go-', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with time')
plt.plot(y,x_eig_time, 'ro-', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with time')
plt.plot(y,x_eig_gtd, 'bo-', linewidth=1, markersize=3, label='Eigen Math Library Vectorized measured with gtd')
plt.plot(y,x_std_gtd, 'yo-', linewidth=1, markersize=3, label='Standard Matrix Multiplication measured with gtd')
plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

x_std_gtd_c=[np.mean(x_std_gtd_100_c), np.mean(x_std_gtd_500_c), np.mean(x_std_gtd_1000_c), np.mean(x_std_gtd_2000_c), np.mean(x_std_gtd_3000_c)]
x_eig_gtd_c=[np.mean(x_eig_gtd_100_c), np.mean(x_eig_gtd_500_c), np.mean(x_eig_gtd_1000_c), np.mean(x_eig_gtd_2000_c), np.mean(x_eig_gtd_3000_c)]
x_std_gtd_d=[np.mean(x_std_gtd_100_d), np.mean(x_std_gtd_500_d), np.mean(x_std_gtd_1000_d), np.mean(x_std_gtd_2000_d), np.mean(x_std_gtd_3000_d)]
x_eig_gtd_d=[np.mean(x_eig_gtd_100_d), np.mean(x_eig_gtd_500_d), np.mean(x_eig_gtd_1000_d), np.mean(x_eig_gtd_2000_d), np.mean(x_eig_gtd_3000_d)]

print(x_eig_gtd_d)

plt.title('Measured with gtd')
plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_std_gtd_c,  'go-', linewidth=1, markersize=3, label='Computation time of Standard MM')
plt.plot(y,x_eig_gtd_c, 'ro-', linewidth=1, markersize=3, label='Computation time of Eigen-based MM')
plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()

plt.title('Measured with gtd')
plt.ylabel('time (s)')
plt.xlabel('size of N')
plt.plot(y,x_eig_gtd_d, 'bo-', linewidth=1, markersize=3, label='Initialization time of Eigen-based MM')
plt.plot(y,x_std_gtd_d, 'yo-', linewidth=1, markersize=3, label='Initialization time of Standard MM')
plt.yscale('log')
default_y_ticks = range(len(y))
plt.xticks(y)
plt.legend()
plt.show()