#include<stdio.h>

#define LOCATION __FILE__, __FUNCTION__, __LINE__
#define REPORT_ERROR { printf( "Error: %s(%s):%d\n", LOCATION ); exit(EXIT_FAILURE); }
#define ROOT        0
#define LEFT_CHILD  1
#define RIGHT_CHILD 2
#define NEEL        3
#define AAA 100000
#define RED   true
#define BLACK false
