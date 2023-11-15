import matplotlib.pyplot as plt
import numpy as np

# Sequential
x = ["rows", "cols", "256x256", "128x128", "64x64", "32x32", "16x16", "8x8"]

ex_rows = [0]
ex_cols = [0]
ex_256 = [1098, 1100, 1095, 1107, 1147, 1123, 1110, 1091, 1108, 1149]
ex_128 = [891, 923, 875, 926, 925, 847, 961, 863, 911, 947]
ex_64 = [828, 854, 837, 872, 970, 864, 943, 867, 859, 838]
ex_32 = [1235, 1270, 1630, 1961, 1934, 1704, 1235, 1060, 1106, 1650]
ex_16 = [15452, 15210, 12594, 14215, 16677, 16640, 11639, 15281, 15412, 17258]
ex_8 = [135094, 160452, 215516, 197276, 199589, 209336, 195598, 171400, 208039, 210339]

mean_8 = np.mean(ex_8)
mean = [0, 0, 1113, 904, 873, 1478, 15038, mean_8]

dev_rows = np.std(ex_rows)
dev_cols = np.std(ex_cols)
dev_256 = np.std(ex_256)
dev_128 = np.std(ex_128)
dev_64 = np.std(ex_64)
dev_32 = np.std(ex_32)
dev_16 = np.std(ex_16)
dev_8 = np.std(ex_8)

plt.bar(x, mean)

# Adding labels and title
plt.xlabel('Configuration')
plt.ylabel('time (ms)')
plt.title('')
plt.yscale('log')
plt.xticks(rotation=45, ha='right')

# Display the plot
plt.show()