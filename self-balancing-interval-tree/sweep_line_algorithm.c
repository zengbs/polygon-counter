#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "intervaltree.h"
#include "prototypes.h"


// X1L, X1R, X2L, X2R, X3L, X3R, X4L, X4R
// Y1T, Y1B, Y2T, Y2B, Y3T, Y3B, Y4T, Y4B


struct EventListX_wrapper_structure{
   int EventListX;
   int KeyX;
};


typedef struct EventListX_wrapper_structure EventListX_wrapper;

int compare ( const void *a, const void *b )
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

   Interval interval;

   for (int i=0; i<arrayLength; i++){

      // KeyX is even (including 0)
      if ( ( ( wrapper[i].KeyX ) & 1 ) == 0 ){

         interval.high = EventListY[wrapper[i].KeyX+1];
         interval.low  = EventListY[wrapper[i].KeyX  ];
         interval.counted = false;

#        ifdef DEBUG
         printf("Insert [%d, %d]\n", interval.low, interval.high);
#        endif

         ListNode *listNode = NULL;

         CountOverlappingInterval( root, &interval, &listNode, counter );

         // Insert interval into interval tree
         InsertTreeNode( &root, &interval );

      // KeyX is odd
      }else{

         interval.high = EventListY[wrapper[i].KeyX  ];
         interval.low  = EventListY[wrapper[i].KeyX-1];

#        ifdef DEBUG
         printf("Delete [%d, %d]\n", interval.low, interval.high);
#        endif

         // Delete interval into interval tree
         DeleteTreeNode( &root, &interval );

      }

#     ifdef DEBUG
      print2D(root);
      printf("============================\n");
#     endif
   }
}

