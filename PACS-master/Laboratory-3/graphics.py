import matplotlib.pyplot as plt
import numpy as np

x = [16, 128, 1024, 1048576, 4294967295]
y = [25, 27, 45, 12838, 15344100]

print(np.divide(y,x))

# plt.ylabel('time (us)')
# plt.xlabel('size of N')
# plt.plot(x,y, 'go', linewidth=1, markersize=3, label='')
# plt.xscale('log')
# plt.yscale('log')
# plt.legend()
# plt.show()