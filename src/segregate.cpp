#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/typedef.h"
#include "../includes/global.h"
#include "../includes/macro.h"
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"


void LomutoPartition( EventListX_wrapper *wrapper, UINT leftEnd, UINT rightEnd )
{
    UINT j = leftEnd-1;

    for (UINT i = leftEnd; i <= rightEnd; i++){

        // if wrapper[i].KeyX is odd
        if ( ( wrapper[i].KeyX & 1 ) == 0 ){
            j++;
            XorSwap( &(wrapper[i].KeyX), &(wrapper[j].KeyX) );
            SwapPointer( (void**)&(wrapper[i].polygon), (void**)&(wrapper[j].polygon) );
        }
    }
}


void SegregateEvenAndOdd( EventListX_wrapper *wrapper, UINT numRectangles )
{
   UINT start = -1;
   UINT current, next;

   for ( UINT end=0; end<numRectangles-1; end++ ){

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


