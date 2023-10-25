#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <stdint.h>
#include "macro.h"

#if   ( defined INT16 )
typedef int16_t INT;
#elif ( defined INT32 )
typedef int32_t INT;
#elif ( defined INT64 )
typedef int64_t INT;
#endif

#  if ( defined UINT16 )
typedef uint16_t  UINT;
#elif ( defined UINT32 )
typedef uint32_t  UINT;
#elif ( defined UINT64 )
typedef uint64_t  UINT;
#endif

typedef struct SubIntervalTree SubIntervalTreeNode;
typedef struct IntervalTree IntervalTreeNode;
typedef struct EventListX_wrapper_structure EventListX_wrapper;


#endif
