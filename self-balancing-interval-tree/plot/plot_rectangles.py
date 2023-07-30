import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np

FileOut = "rectangles_map"

table = "table__rectangles"

xl      = np.loadtxt( table, usecols=(0), unpack=True )
yb      = np.loadtxt( table, usecols=(1), unpack=True )
width   = np.loadtxt( table, usecols=(2), unpack=True )
height  = np.loadtxt( table, usecols=(3), unpack=True )

fig, ax = plt.subplots()

for i in range(len(xl)):
   rect = patches.Rectangle((xl[i], yb[i]), width[i], height[i], facecolor="none", edgecolor="black", linewidth=1)
   ax.add_patch(rect)


plt.xlim([0,101])
plt.ylim([0,101])

ax.set_xticks([])
ax.set_yticks([])

plt.savefig( FileOut+".png", bbox_inches='tight', pad_inches=0.05, format='png' )
