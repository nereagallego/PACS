import matplotlib.pyplot as plt
import numpy as np

x = [16, 128, 1024, 1048576, 4294967295]
y = [11, 11, 16, 2831, 10471147]

print(np.divide(y,x))

# plt.ylabel('time (us)')
# plt.xlabel('size of N')
# plt.plot(x,y, 'go', linewidth=1, markersize=3, label='')
# plt.xscale('log')
# plt.yscale('log')
# plt.legend()
# plt.show()