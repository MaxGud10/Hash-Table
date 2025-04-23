import matplotlib.pyplot as plt
import numpy as np
import sys
import os

file_name = sys.argv[1]
hist_name = sys.argv[2]

with open(file_name, 'r') as file:
    data = [line.strip().split() for line in file]

x_values = [int(row[0]) for row in data]
y_values = [int(row[1]) for row in data]

plt.bar(x_values, y_values)

plt.xlabel('Bucket number')
plt.ylabel('Occurrences')
plt.title(hist_name)

plt.savefig(('histograms/' + hist_name + '.png'))

variance = np.var(y_values)
print(f"The variance of {hist_name}: {variance}")