#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include"global.h"
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"

//void XorSwap(int *x, int *y)
//{
//  if (x != y)
//  {
//    *x ^= *y;
//    *y ^= *x;
//    *x ^= *y;
//  }
//}

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

   for ( int end=0; end<numRectangles-1; end++ ){

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


//int main(){
//
//   int numRectangles = 6;
//
//   EventListX_wrapper *wrapper = (EventListX_wrapper*)malloc(sizeof(EventListX_wrapper)*numRectangles);
//
//   wrapper[0].EventListX = 0;  wrapper[0].KeyX = 0;
//   wrapper[1].EventListX = 0;  wrapper[1].KeyX = 1;
//   wrapper[2].EventListX = 0;  wrapper[2].KeyX = 2;
//   wrapper[3].EventListX = 1;  wrapper[3].KeyX = 3;
//   wrapper[4].EventListX = 1;  wrapper[4].KeyX = 4;
//   wrapper[5].EventListX = 1;  wrapper[5].KeyX = 5;
//
//   SegregateEvenAndOdd(wrapper, numRectangles);
//
//    for (int i=0; i<numRectangles; i++){
//       printf("%d, %d\n", wrapper[i].EventListX, wrapper[i].KeyX);
//    }
//
//
//}
