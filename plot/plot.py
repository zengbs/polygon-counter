from math import *
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MultipleLocator
import matplotlib.font_manager as font_manager

def Square(x):
   return x**1.9

def NLogN(x):
   return x*np.log(x)*np.log(x)


# performance tables
table = 'Record__polygonCount_vs_time__SCALING_ADAPTIVE_BOX'

# settings
FileOut = 'fig__scaling_adaptivebox'


f, ax = plt.subplots( 1, 1, sharex=False, sharey=False )
f.subplots_adjust( hspace=0.0, wspace=0.3 )
f.set_size_inches( 10, 10 )

# line styles
LStyle_Dot     = [1, 2]
LStyle_Dash    = [4, 2]
LStyle_DashDot = [4, 2, 1, 2]


# load data
generateWrapper = np.loadtxt( table, usecols=( 0), unpack=True )
sorting         = np.loadtxt( table, usecols=( 1), unpack=True )
segregate       = np.loadtxt( table, usecols=( 2), unpack=True )
counting        = np.loadtxt( table, usecols=( 3), unpack=True )
insertion       = np.loadtxt( table, usecols=( 4), unpack=True )
deletion        = np.loadtxt( table, usecols=( 5), unpack=True )
sweepLine       = np.loadtxt( table, usecols=( 6), unpack=True )

numberPolygons  = np.loadtxt( table, usecols=(10), unpack=True )

total = generateWrapper+sorting+segregate+counting+insertion+deletion+sweepLine

font = font_manager.FontProperties(style='normal', size=20)


ax.plot( numberPolygons, total          , '-s', color='red',    lw=3, ms=12, label="Overall"   )
ax.plot( numberPolygons, generateWrapper, '-d', color='cyan',   lw=3, ms=12, label="Generating wrapper" )
ax.plot( numberPolygons, sorting        , '-x', color='blue',   lw=3, ms=12, label="Sorting"   )
ax.plot( numberPolygons, segregate      , '-o', color='green',  lw=3, ms=12, label="Detaching" )
ax.plot( numberPolygons, counting       , '-v', color='orange', lw=3, ms=12, label="Counting bounding box"  )
ax.plot( numberPolygons, insertion      , '-P', color='purple', lw=3, ms=12, label="Insertion" )
ax.plot( numberPolygons, deletion       , '-*', color='brown',  lw=3, ms=12, label="Deletion"  )
ax.plot( numberPolygons, sweepLine      , '-D', color='olive',  lw=3, ms=12, label="Sweeping"  )
ax.plot( numberPolygons, 0.5*total[0]/NLogN(numberPolygons[0])*NLogN(numberPolygons), color='k',  lw=3, linestyle='dashed' )
ax.plot( numberPolygons, 0.5*total[0]/Square(numberPolygons[0])*Square(numberPolygons), color='k',  lw=3, linestyle='dashed' )

ax.text(1e7, 1e6, r'$\propto N^{2}$'  , fontsize=20, color='k' , rotation=45 )
ax.text(1e7, 7e2, r'$\propto N\log N$', fontsize=20, color='k', rotation=32 )

# set axis
ax.set_xscale( 'log' )
ax.set_yscale( 'log' )
#ax.set_xlim( 8, 3.0e3 )
#ax.set_ylim( 5.0e8, 1e11 )
ax.set_xlabel( 'Number of polygons (N)', fontsize=20)
ax.set_ylabel( 'Time (sec)',       fontsize=20)
ax.tick_params( which='both', tick2On=True, direction='in', labelsize=20 )
ax.legend( loc='upper left', numpoints=1, labelspacing=0.1, prop=font )

# save/show figure
plt.savefig( FileOut+".png", bbox_inches='tight', pad_inches=0.05, format='png' )
