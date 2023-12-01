#include <stdio.h>
#include <stdlib.h>
#include <immintrin.h>
#include "../includes/typedef.h"
#include "../includes/global.h"
#include "../includes/macro.h"
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"


bool compare ( const EventListX_wrapper& a, const EventListX_wrapper& b )
{
   UINT number1 = a.EventListX;
   UINT number2 = b.EventListX;

   return number1 < number2;
}



void SweepLine( IntervalTreeNode **root, Polygon **polygonArray,
                UINT *EventListX, UINT *EventListY, UINT numRectangles,
                UINT *RectangularCounter, UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter )
{

#  ifdef TIMER
   Start(&timeUL_sweepline1);
#  endif

   UINT arrayLength = 2*numRectangles;

   EventListX_wrapper *wrapper = new EventListX_wrapper [ arrayLength ];

   time_sweepline4 = time_sweepline5 = time_sweepline6 = 0.0;

   for ( UINT i=0; i<arrayLength; i++ ){
      wrapper[i].EventListX   = EventListX[i];
      wrapper[i].KeyX         = i;
      wrapper[i].polygon      = polygonArray[(i-(i&1))>>1];
   }

#  ifdef TIMER
   Stop(&timeUL_sweepline1);
   time_sweepline1 = GetValue(&timeUL_sweepline1);
#  endif

#  ifdef TIMER
   Start(&timeUL_sweepline2);
#  endif

   // Sort EventListX in ascending order
   std::sort( wrapper, wrapper+arrayLength, compare );

#  ifdef TIMER
   Stop(&timeUL_sweepline2);
   time_sweepline2 = GetValue(&timeUL_sweepline2);
#  endif

#  ifdef TIMER
   Start(&timeUL_sweepline3);
#  endif

   SegregateEvenAndOdd( wrapper, arrayLength );

#  ifdef TIMER
   Stop(&timeUL_sweepline3);
   time_sweepline3 = GetValue(&timeUL_sweepline3);
#  endif

   Interval intervalY;
#  ifdef DEBUG
   Interval intervalX;
#  endif

#  ifdef TIMER
   Start(&timeUL_sweepline7);
#  endif

   for (UINT i=0; i<arrayLength; i++){

      // KeyX is even (including 0)
      if ( ( ( wrapper[i].KeyX ) & 1 ) == 0 ){

         intervalY.counted = false;
         intervalY.high = EventListY[wrapper[i].KeyX+1];
         intervalY.low  = EventListY[wrapper[i].KeyX  ];

#        ifdef DEBUG
         intervalX.high = EventListX[wrapper[i].KeyX+1];
         intervalX.low  = EventListX[wrapper[i].KeyX  ];
         printf("Insert X: [%d, %d], Y: [%d, %d]\n", intervalX.low, intervalX.high, intervalY.low, intervalY.high);
#        endif

#        ifdef TIMER
         Start(&timeUL_sweepline4);
#        endif

         // Count overlapping intervals in an interval tree
         CountOverlappingInterval( *root, &intervalY, wrapper[i].polygon, RectangularCounter,
                                   TouchingCounter, IntersectedCounter, DuplicateCounter );

#        ifdef TIMER
         Stop(&timeUL_sweepline4);
         time_sweepline4 += GetValue(&timeUL_sweepline4);
#        endif

#        ifdef TIMER
         Start(&timeUL_sweepline5);
#        endif

         // Insert intervalY into interval tree
         InsertTreeNode( root, &intervalY, wrapper[i].polygon, NULL );

#        ifdef TIMER
         Stop(&timeUL_sweepline5);
         time_sweepline5 += GetValue(&timeUL_sweepline5);
#        endif

      // KeyX is odd
      }else{

#        ifdef DEBUG
         intervalX.high = EventListX[wrapper[i].KeyX  ];
         intervalX.low  = EventListX[wrapper[i].KeyX-1];
#        endif
         intervalY.high = EventListY[wrapper[i].KeyX  ];
         intervalY.low  = EventListY[wrapper[i].KeyX-1];

#        ifdef DEBUG
         printf("Delete X: [%d, %d], Y: [%d, %d]\n", intervalX.low, intervalX.high, intervalY.low, intervalY.high);
#        endif

#        ifdef TIMER
         Start(&timeUL_sweepline6);
#        endif

         // Delete intervalY from interval tree
         DeleteTreeNode( root, &intervalY, wrapper[i].polygon );

#        ifdef TIMER
         Stop(&timeUL_sweepline6);
         time_sweepline6 += GetValue(&timeUL_sweepline6);
#        endif

      }

   }

   delete[] wrapper;

#  ifdef TIMER
   Stop(&timeUL_sweepline7);
   time_sweepline7 = GetValue(&timeUL_sweepline7);
#  endif

}
