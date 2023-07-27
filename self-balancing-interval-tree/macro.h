#include<stdio.h>

#define LOCATION __FILE__, __FUNCTION__, __LINE__
#define REPORT_ERROR { printf( "Error: %s(%s):%d\n", LOCATION ); exit(EXIT_FAILURE); }
#define PRINT_LOCATION printf("%s(%s):%d\n", LOCATION);
#define ROOT        ( 1<<0 )
#define LEFT_CHILD  ( 1<<1 )
#define RIGHT_CHILD ( 1<<2 )
#define NEEL        ( 1<<3 )
#define RED   true
#define BLACK false
#define LOW_END  0
#define HIGH_END 1
#define OVERLAPPING ( 1<<0 )
#define TOUCHING    ( 1<<1 )
#define DUPLICATE   ( 1<<2 )

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define DEBUG_LEVEL_1
#define DEBUG
