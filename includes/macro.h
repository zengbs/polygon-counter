#ifndef __MACRO_H__
#define __MACRO_H__

#include <stdio.h>
#include <stdint.h>

#define LOCATION __FILE__, __FUNCTION__, __LINE__
#define REPORT_ERROR { printf( "Error: %s(%s):%d\n", LOCATION ); abort(); }
#define PRINT_LOCATION printf("%s(%s):%d\n", LOCATION);
#define RED_NODE         (  true  )
#define BLACK_NODE       (  false )

// Red-black tree
#define ROOT_NODE        (  1<<0  )
#define LEFT_CHILD       (  1<<1  )
#define RIGHT_CHILD      (  1<<2  )
#define NEEL             (  1<<3  )

// Bounding box of polygon
#define OVERLAPPING      (  1<<0  )
#define TOUCHING         (  1<<1  )
#define DUPLICATE        (  1<<2  )

#define MAX(x, y)        (  ((x) > (y)) ? (x) : (y)  )
#define MIN(x, y)        (  ((x) < (y)) ? (x) : (y)  )

#define COMMENT_SYMBOL '#'
#define MAX_STRING     100
#define UINT64
#define INT64
#define TIMER

//#define SCALING_BIGBOX
//#define SCALING_SMALLBOX
//#define SAME_SCALE
#define QUICK_START

#if ( defined SAME_SCALE ) || ( defined QUICK_START )
#define NAIVE
#endif


//#define PIXELIZATION
//#define PRINT_RECTANGLES
//#define DEBUG

//#define RANDOM_GENERATION
#define RANDOM_GENERATION_SCALING

#define ASSERT(x) if (!(x)) { REPORT_ERROR; }

// Polygon
#define INTERSECT_POLYGONS  (  1<<0  )
#define TOUCHING_POLYGONS   (  1<<1  )
#define DISJOINT_POLYGONS   (  1<<2  )
#define DUPLICATE_POLYGONS  (  1<<3  )


#  if ( defined INT16 )
#define BYTE_SIZE_INT 2
#elif ( defined INT32 )
#define BYTE_SIZE_INT 4
#elif ( defined INT64 )
#define BYTE_SIZE_INT 8
#endif

#  if ( defined UINT16 )
#define BYTE_SIZE_INT 2
#elif ( defined UINT32 )
#define BYTE_SIZE_INT 4
#elif ( defined UINT64 )
#define BYTE_SIZE_INT 8
#endif


#define BIT_SIZE_INT  ( 8*BYTE_SIZE_INT )


#if ( defined INT16 || defined INT32 || defined INT64 )
#define __INT_MAX   ( ~( (INT)1 << (BIT_SIZE_INT-1) ) )
#define __INT_MIN   (    (INT)1 << (BIT_SIZE_INT-1)   )
#endif

#if ( defined UINT16 || defined UINT32 || defined UINT64 )
#define __UINT_MAX   ( ~(UINT)0 )
#define __UINT_MIN   (  (UINT)0 )
#endif

#endif
