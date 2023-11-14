import matplotlib.pyplot as plt
import numpy as np

# Sequential
x = ["rows", "cols", "256x256", "128x128", "64x64", "32x32", "16x16", "8x8", "4x4", "2x2", "1x1"]
y = [2057, 2088, 1113, 904, 873, 1478, 15038]
print(np.divide(y,x))

# Parallel
threads = [1, 2, 4, 8, 16]
microseconds = [105450513, 55977659, 27984860, 13995603, 6998771]


plt.ylabel('time (us)')
plt.xlabel('number of threads')
plt.plot(threads,microseconds, 'go', linestyle='-', linewidth=1, markersize=3, label='')
plt.legend()
plt.show()