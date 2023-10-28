import matplotlib.pyplot as plt
import numpy as np

# Sequential
x = [16, 128, 1024, 1048576, 4294967295]
y = [11, 11, 16, 2831, 10471147]
print(np.divide(y,x))

# Parallel
threads = [1, 2, 4, 8, 16]
microseconds = [105450513, 55977659, 27984860, 13995603, 6998771]


plt.ylabel('time (us)')
plt.xlabel('number of threads')
plt.plot(threads,microseconds, 'go', linestyle='-', linewidth=1, markersize=3, label='')
plt.legend()
plt.show()
