import matplotlib.pyplot as plt
import numpy as np



x = ['heterogeneous system', 'cpu multicore', 'gpu']
y_kernel_time = [13.810394, 21.726354, 10.286731]
y_overall_time = [49.588739, 95.941153, 65.407475]

# Make two histograms in the same plot

fig, axs = plt.subplots(1, 2, figsize=(10, 5))  # 1 row, 2 columns

axs[0].set_title('Time of execution of the kernel')
axs[0].set_ylabel('time (s)')
axs[0].set_xlabel('type of system')
axs[0].bar(x, y_kernel_time)

axs[1].set_title('Overall time of execution')
axs[1].set_ylabel('time (s)')
axs[1].set_xlabel('type of system')
axs[1].bar(x, y_overall_time)

plt.tight_layout()
plt.show()


