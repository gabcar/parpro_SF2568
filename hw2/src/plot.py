from matplotlib import pyplot as plt



file_name = "ufile.txt"

F = open(file_name,"r")

for line in F:
    lin = line.split(" ")[:-1]
    lin = [float(i) for i in lin]

plt.figure()

plt.plot(lin)

plt.show()
