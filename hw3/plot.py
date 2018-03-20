from matplotlib import pyplot as plt
import numpy as np



file_name = "output/slurm-702309.out"

F = open(file_name,"r")

for line in F:
    lin = line.split(" ")[:-1]

print(line[-1])

"""
plt.xlabel("x")
plt.ylabel("u(x)")
ax.set_xlim(xmin=0,xmax=1)
plt.legend(handles=[approx, true])
fig.savefig('report/plots/u_plot_24_processors_10e6.png')
plt.show()
"""
