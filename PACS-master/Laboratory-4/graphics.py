import matplotlib.pyplot as plt
import numpy as np

ex_rows = [1]
ex_cols = [1]
ex_1 = [6478, 6447, 6466, 6440, 6446, 6445, 6581, 6468, 6535, 6453]
ex_2 = [2027, 2031, 2014, 2034, 2035, 2039, 2033, 2045, 2138, 2121]
ex_4 = [1078, 963, 1046, 958, 865, 1045, 953, 941, 968, 1018]
ex_8 = [921, 861, 884, 815, 853, 883, 870, 848, 909, 874]
ex_16 = [814, 886, 788, 835, 822, 902, 819, 1003, 913, 883]
ex_32 = [2854, 1945, 1791, 2649, 1810, 2074, 1407, 1832, 2651, 3013]
ex_64 = [25867, 27134, 29032, 39752, 40306, 36065, 30625, 33342, 24318, 42635]
ex_128 = [378561 ,390627 ,408479 ,266599 ,216096 ,448520 ,347685 ,297464 ,256730 ,344982]

mean_rows = np.mean(ex_rows)
mean_cols = np.mean(ex_cols)
mean_1 = np.mean(ex_1)
mean_2 = np.mean(ex_2)
mean_4 = np.mean(ex_4)
mean_8 = np.mean(ex_8)
mean_16 = np.mean(ex_16)
mean_32 = np.mean(ex_32)
mean_64 = np.mean(ex_64)
mean_128 = np.mean(ex_128)

dev_rows = np.std(ex_rows)
dev_cols = np.std(ex_cols)
dev_1 = np.std(ex_1)
dev_2 = np.std(ex_2)
dev_4 = np.std(ex_4)
dev_8 = np.std(ex_8)
dev_16 = np.std(ex_16)
dev_32 = np.std(ex_32)
dev_64 = np.std(ex_64)
dev_128 = np.std(ex_128)

x = ["rows", "cols", "1x1", "2x2", "4x4", "8x8", "16x16", "32x32", "64x64", "128x128"]
mean = [mean_rows, mean_cols, mean_1, mean_2, mean_4, mean_8, mean_16, mean_32, mean_64, mean_128]
dev = [dev_rows, dev_cols, dev_1, dev_2, dev_4, dev_8, dev_16, dev_32, dev_64, dev_128]
# Coefficient of variation
cv = [100*dev_rows/mean_rows, 100*dev_cols/mean_cols, 100*dev_1/mean_1, 100*dev_2/mean_2, 100*dev_4/mean_4, 100*dev_8/mean_8, 100*dev_16/mean_16, 100*dev_32/mean_32, 100*dev_64/mean_64, 100*dev_128/mean_128]

plt.bar(x, cv)

# Adding labels and title
plt.xlabel('Configuration')
plt.ylabel('time (ms)')
plt.title('')
# plt.yscale('log')
plt.xticks(rotation=45, ha='right')

# Display the plot
plt.show()