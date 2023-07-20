#include <stdio.h>
#include <stdlib.h>


// X1L, X1R, X2L, X2R, X3L, X3R, X4L, X4R
// Y1T, Y1B, Y2T, Y2B, Y3T, Y3B, Y4T, Y4B


struct EventListX_wrapper_structure{
   int EventListX;
   int KeyX;
};


typedef struct EventListX_wrapper_strucure EventListX_wrapper;

int compare ( const void *a, const void *b )
{
   int number1 = (*(EventListX_wrapper*)a).EventListX;
   int number2 = (*(EventListX_wrapper*)b).KeyX;

   return number1 - number2;
}

void SweepLine( int *EventListX, int *EventListY, int numRectangles )
{
   int arrayLength = 2*numRectangles;

   EventListX_wrapper *wrapper = (EventListX_wrapper*)malloc(sizeof(EventListX_wrapper)*arrayLength);

   for ( int i=0; i<arrayLength; i++ ){
      wrapper->EventListX = EventListX[i];
      wrapper->KeyX       = i;
   }

   // Sort EventListX in ascending order
   qsort( wrapper, arrayLength, sizeof(EventListX_wrapper), compare);

  // The number of overlapping rectangles (excluding touching rectangles)
  int counter = 0;

  for (int i=0; i<arrayLength; i++){

     Interval interval;

     // KeyX is even (including 0)
     if ( ( ( wrapper[i].KeyX ) & 1 ) == 0 ){

        interval.high = wrapper[i+1].EventListY;
        interval.low  = wrapper[i  ].EventListY;

        ListNode *listNode = NULL;

        if ( SearchInterval( &root, &interval, &listNode, OVERLAPPING ) ) counter++;

        InsertTreeNode( &root, &interval );

     // KeyX is odd
     }else{

        interval.high = wrapper[i  ].EventListY;
        interval.low  = wrapper[i-1].EventListY;

        DeleteNode( &root, &interval );

     }
  }

}
