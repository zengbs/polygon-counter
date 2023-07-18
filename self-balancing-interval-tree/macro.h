#include<stdio.h>

#define LOCATION __FILE__, __FUNCTION__, __LINE__
#define REPORT_ERROR { printf( "Error: %s(%s):%d\n", LOCATION ); exit(EXIT_FAILURE); }
#define PRINT_LOCATION printf("%s(%s):%d\n", LOCATION);
#define ROOT        0
#define LEFT_CHILD  1
#define RIGHT_CHILD 2
#define NEEL        3
#define RED   true
#define BLACK false
#define LOW_END  0
#define HIGH_END 1


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
