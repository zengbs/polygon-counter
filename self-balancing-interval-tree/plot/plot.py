from math import *
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MultipleLocator
import matplotlib.font_manager as font_manager

def Square(x):
   return x**1.9

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
numberPolygons = np.loadtxt( table, usecols=(3), unpack=True )


font = font_manager.FontProperties(style='normal', size=20)


ax.plot( numberPolygons, naiveAlgo,                          '-s', color='red',  lw=3, ms=12, label="Naive Algo"     )
ax.plot( numberPolygons, 3*naiveAlgo[0]/Square(numberPolygons[0])*Square(numberPolygons), color='red', lw=3, linestyle='dashed' )
ax.plot( numberPolygons, efficientAlgo,                      '-o', color='blue', lw=3, ms=12, label="Efficient Algo" )
ax.plot( numberPolygons, 0.5*efficientAlgo[0]/NLogN(numberPolygons[0])*NLogN(numberPolygons), color='blue',  lw=3, linestyle='dashed' )

ax.text(20000, 100, r'$\propto N^{1.9}$', fontsize=20, color='red' , rotation=40 )
ax.text(20000, 0.1, r'$\propto N\log N$', fontsize=20, color='blue', rotation=25 )

# set axis
ax.set_xscale( 'log' )
ax.set_yscale( 'log' )
#ax.set_xlim( 8, 3.0e3 )
#ax.set_ylim( 5.0e8, 1e11 )
ax.set_xlabel( 'Number of rectangles (N)', fontsize=20)
ax.set_ylabel( 'Time (sec)',       fontsize=20)
ax.tick_params( which='both', tick2On=True, direction='in', labelsize=20 )
ax.legend( loc='upper left', numpoints=1, labelspacing=0.1, prop=font )

# save/show figure
plt.savefig( FileOut+".png", bbox_inches='tight', pad_inches=0.05, format='png' )
