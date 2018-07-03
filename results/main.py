import numpy as np
import matplotlib.pyplot as plt

print("Entering Python Environment...")
print("Generating obtained data plot...")
print("Plot also writen in: S_C-plot.png")

l = [0, 10, 20, 50, 100]

input_data = open("results/S_C.txt", "r")
input_data3D = open("results/S_C3D.txt", "r")

data = np.loadtxt(input_data)
data3D = np.loadtxt(input_data3D)

fig1, ax1 = plt.subplots(1)

ax1.plot(data[..., 0], data[..., 1], 'C1',label='1D')
ax1.plot(data[l, 0], data[l, 1], 'o', color='C1')

ax1.plot(data3D[..., 0], data3D[..., 1], 'C2', label='3D')
ax1.plot(data3D[l, 0], data3D[l, 1], 'o', color='C2')

ax1.set_xlabel('Sakoe-Chiba band width (%)')
ax1.set_ylabel('Score (%)')

ax1.legend(loc='best', ncol=2)
fig1.tight_layout(pad=0.1)

fig1.savefig('results/S_C-plot')

# -------

fig2, ax2 = plt.subplots(1)

ax2.plot(data[..., 0], data[..., 2], 'C1',label='1D')

ax2.plot(data3D[..., 0], data3D[..., 2], 'C2', label='3D')

ax2.set_xlabel('Sakoe-Chiba band width (%)')
ax2.set_ylabel('Time (s)')

ax2.legend(loc='best', ncol=2)
fig2.tight_layout(pad=0.1)

fig2.savefig('results/S_C-plot-time')

plt.show()

input_data.close()

input_data3D.close()
