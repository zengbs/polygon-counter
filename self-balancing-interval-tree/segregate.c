#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include"global.h"
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


void LomutoPartition( EventListX_wrapper *wrapper, int leftEnd, int rightEnd )
{
    int j = leftEnd-1;

    for (int i = leftEnd; i <= rightEnd; i++){

        // if wrapper[i].KeyX is odd
        if ( ( wrapper[i].KeyX & 1 ) == 1 ){
            j++;
            XorSwap( &(wrapper[i].KeyX), &(wrapper[j].KeyX) );
        }
    }
}


void SegregateEvenAndOdd( EventListX_wrapper *wrapper, int numRectangles )
{
   int start = -1;
   int current, next;

   for ( int end=0; end<numRectangles; end++ ){

      start++;

      current = wrapper[end  ].EventListX;
      next    = wrapper[end+1].EventListX;

      while( current == next )
      {
         end++;
         current = wrapper[end].EventListX;

         if (end+1 < numRectangles)  next = wrapper[end+1].EventListX;
         else break;
      }

      if (start < end){
         LomutoPartition( wrapper, start, end );
         start = end;
      }
   }
}
