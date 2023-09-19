# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import matplotlib.pyplot as plt
import numpy as np

x_std=[155, 153, 153.5, 154.3, 155.5, 157, 156, 152.7, 153.8, 154.4, 155.9, 155.9, 155.2, 156.1, 154, 154, 152.9, 153.5, 155.6, 155.1]
x_eig=[0.028, 0.028, 0.027, 0.028, 0.028, 0.027, 0.026, 0.027, 0.027, 0.027, 0.027, 0.027, 0.027, 0.027, 0.026, 0.028, 0.027, 0.027, 0.027, 0.028]
y=np.arange(20)
plt.plot(y,x_std,  'go--', linewidth=1, markersize=1)
plt.plot(y,x_eig, 'ro--', linewidth=1, markersize=1)
plt.show()
