#include <stdio.h>
#include <stdlib.h>


// X1L, X1R, X2L, X2R, X3L, X3R, X4L, X4R
// Y1T, Y1B, Y2T, Y2B, Y3T, Y3B, Y4T, Y4B

void SweepLine( int *EventListX, int *EventListY, int numRectangles )
{

   int arrayLength = 2*numRectangles;

   int *KeyX = (int*)malloc(sizeof(int)*arrayLength);

   for ( int i=0; i<arrayLength; i++ ){
      KeyX[i] = i;
   }


   // Sort EventListX in ascending order

   // Rearrange KeyX based on the sorted index of EventListX

  //
  int counter = 0;

  for (int i=0; i<arrayLength; i++){

     Interval interval;

     if ( ( KeyX[i]&1 ) == 0 ){

        interval.high = EventListY[i+1];
        interval.low  = EventListY[i];

        if ( SearchInterval( &root, &interval,  ) )

        InsertTreeNode( &root, &interval );

     }else{

        interval.high = EventListY[i];
        interval.low  = EventListY[i-1];

        DeleteNode( &root, &interval );

     }
  }

}
