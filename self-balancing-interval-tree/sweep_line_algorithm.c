#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "intervaltree.h"
#include "prototypes.h"


// X1L, X1R, X2L, X2R, X3L, X3R, X4L, X4R
// Y1T, Y1B, Y2T, Y2B, Y3T, Y3B, Y4T, Y4B

static int compare ( const void *a, const void *b )
{
   int number1 = (*(EventListX_wrapper*)a).EventListX;
   int number2 = (*(EventListX_wrapper*)b).EventListX;

   return number1 - number2;
}

void SweepLine( int *EventListX, int *EventListY, int numRectangles, int *counter )
{
   int arrayLength = 2*numRectangles;

   EventListX_wrapper *wrapper = (EventListX_wrapper*)malloc(sizeof(EventListX_wrapper)*arrayLength);

   for ( int i=0; i<arrayLength; i++ ){
      wrapper[i].EventListX = EventListX[i];
      wrapper[i].KeyX       = i;
   }

   // Sort EventListX in ascending order
   qsort( wrapper, arrayLength, sizeof(EventListX_wrapper), compare);

   SegregateEvenAndOdd( wrapper, arrayLength );

   Interval intervalY;
#  ifdef DEBUG
   Interval intervalX;
#  endif

   for (int i=0; i<arrayLength; i++){


      // KeyX is even (including 0)
      if ( ( ( wrapper[i].KeyX ) & 1 ) == 0 ){

         intervalY.counted = false;
         intervalY.high = EventListY[wrapper[i].KeyX+1];
         intervalY.low  = EventListY[wrapper[i].KeyX  ];
#        ifdef DEBUG
         intervalX.high = EventListX[wrapper[i].KeyX+1];
         intervalX.low  = EventListX[wrapper[i].KeyX  ];
#        endif

#        ifdef DEBUG
         printf("Insert X: [%d, %d], Y: [%d, %d]\n", intervalX.low, intervalX.high, intervalY.low, intervalY.high);
#        endif

         ListNode *listNode = NULL;

         CountOverlappingInterval( root, &intervalY, &listNode, counter );


         // Insert intervalY into interval tree
         InsertTreeNode( &root, &intervalY );

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

         // Delete intervalY from interval tree
         DeleteTreeNode( &root, &intervalY );

      }

#     ifdef DEBUG
      print2D(root);
      printf("============================\n");
#     endif

   }
}

