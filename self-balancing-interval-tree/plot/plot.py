from math import *
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MultipleLocator
import matplotlib.font_manager as font_manager

def Square(x):
   return x*x

def NLogN(x):
   return x*np.log(x)


# performance tables
table = 'table'

# settings
FileOut = 'fig__benchmark'


f, ax = plt.subplots( 1, 1, sharex=False, sharey=False )
f.subplots_adjust( hspace=0.0, wspace=0.3 )
f.set_size_inches( 10, 10 )

# line styles
LStyle_Dot     = [1, 2]
LStyle_Dash    = [4, 2]
LStyle_DashDot = [4, 2, 1, 2]


# load data
efficientAlgo  = np.loadtxt( table, usecols=(0), unpack=True )
naiveAlgo      = np.loadtxt( table, usecols=(1), unpack=True )
numberPolygons = np.loadtxt( table, usecols=(4), unpack=True )


font = font_manager.FontProperties(style='normal', size=20)

# plot the performance
# ============================================================
#nodes=np.asarray( [2**n for n in range(4,12)] )

ax.plot( numberPolygons, naiveAlgo,                          '-s', color='red',  lw=3, ms=12, label="Naive Algo"     )
ax.plot( numberPolygons, naiveAlgo[0]/Square(numberPolygons[0])*Square(numberPolygons), color='red', lw=3, linestyle='dashed' )
ax.plot( numberPolygons, efficientAlgo,                      '-o', color='blue', lw=3, ms=12, label="Efficient Algo" )
ax.plot( numberPolygons, efficientAlgo[0]/NLogN(numberPolygons[0])*NLogN(numberPolygons), color='blue',  lw=3, linestyle='dashed' )

# set axis
ax.set_xscale( 'log' )
ax.set_yscale( 'log' )
#ax.set_xlim( 8, 3.0e3 )
#ax.set_ylim( 5.0e8, 1e11 )
ax.set_xlabel( 'Number of rectangles (N)', fontsize=20)
ax.set_ylabel( 'Time (sec)',       fontsize=20)
ax.tick_params( which='both', tick2On=True, direction='in', labelsize=20 )
#ax.tick_params( axis='x', pad=10 )
#ax.set_xticks([10,1e2,1e3])
# add legend
ax.legend( loc='upper left', numpoints=1, labelspacing=0.1, prop=font )



# save/show figure
plt.savefig( FileOut+".png", bbox_inches='tight', pad_inches=0.05, format='png' )
