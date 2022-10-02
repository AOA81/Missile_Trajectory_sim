import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os

path_x = "./data_x.txt"
path_y = "./data_y.txt"
path_z = "./data_z.txt"

count_x = len(open(path_x, "r+").readlines())
count_y = len(open(path_y, "r+").readlines())
count_z = len(open(path_z, "r+").readlines())

fo_x = open(path_x, "r+")
fo_y = open(path_y, "r+")
fo_z = open(path_z, "r+")

x = []
y = []
z = []

#print(count_x)

while(count_x):
    x.append(float(fo_x.readline()))
    count_x -= 1
while(count_y):
    y.append(float(fo_y.readline()))
    count_y -= 1
while(count_z):
    z.append(-float(fo_z.readline()))
    count_z -= 1

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot(x, y, z, label='trajectory curve')
ax.legend()

plt.show()

os.system("rm ./data_x.txt ./data_y.txt ./data_z.txt")


