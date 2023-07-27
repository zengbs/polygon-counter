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

   Interval intervalY, intervalX;

   for (int i=0; i<arrayLength; i++){

//     if ( wrapper[i].EventListX == 843 ) printf("wrapper[%d].KeyX = %d\n", i, wrapper[i].KeyX);

      // KeyX is even (including 0)
      if ( ( ( wrapper[i].KeyX ) & 1 ) == 0 ){

         intervalY.counted = false;
         intervalY.high = EventListY[wrapper[i].KeyX+1];
         intervalY.low  = EventListY[wrapper[i].KeyX  ];
         intervalX.high = EventListX[wrapper[i].KeyX+1];
         intervalX.low  = EventListX[wrapper[i].KeyX  ];

#        ifdef DEBUG
         printf("Insert X: [%d, %d], Y: [%d, %d]\n", intervalX.low, intervalX.high, intervalY.low, intervalY.high);
#        endif

         ListNode *listNode = NULL;

         CountOverlappingInterval( root, &intervalX, &intervalY, &listNode, counter );


         // Insert intervalY into interval tree
         InsertTreeNode( &root, &intervalX, &intervalY );

      // KeyX is odd
      }else{

         intervalX.high = EventListX[wrapper[i].KeyX  ];
         intervalX.low  = EventListX[wrapper[i].KeyX-1];
         intervalY.high = EventListY[wrapper[i].KeyX  ];
         intervalY.low  = EventListY[wrapper[i].KeyX-1];

#        ifdef DEBUG
         printf("Delete X: [%d, %d], Y: [%d, %d]\n", intervalX.low, intervalX.high, intervalY.low, intervalY.high);
#        endif

         // Delete intervalY into interval tree
         DeleteTreeNode( &root, &intervalY );

      }

#     ifdef DEBUG
      print2D(root);
      printf("============================\n");
#     endif

      //if ( intervalY.low == 530 && intervalY.high == 537 ) exit(0);
   }
}

