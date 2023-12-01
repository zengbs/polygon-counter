#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../includes/typedef.h"
#include "../includes/global.h"
#include "../includes/macro.h"
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"

void Pixelization( UINT numRectangles, UINT boxSizeX, UINT boxSizeY, UINT *EventListX, UINT *EventListY, UINT *counter )
{

   if ( checkIntOverflow( boxSizeX, boxSizeY, '*') ) REPORT_ERROR;

   UINT *box = (UINT*)calloc(size_t(boxSizeX*boxSizeY), sizeof(UINT));

   if ( box == NULL ) REPORT_ERROR;

   unsigned long long xL, yB, xR, yT;

   for ( UINT i=0;i<2*numRectangles; i+=2 ){

      xL = EventListX[i];
      yB = EventListY[i];

      xR = EventListX[i+1];
      yT = EventListY[i+1];

      for ( unsigned long long y=yB; y<yT; y++ ){
         for ( unsigned long long x=xL; x<xR; x++ ){
            box[ x+y*(unsigned long long)boxSizeX ]++;
         }
      }
   }

   *counter = 0;

   for ( UINT i=0;i<2*numRectangles; i+=2 ){

      xL = EventListX[i];
      yB = EventListY[i];

      xR = EventListX[i+1];
      yT = EventListY[i+1];

      bool breakloops = false;

      for ( UINT y=yB; y<yT; y++ ){
         for ( UINT x=xL; x<xR; x++ ){
            if ( box[ x+y*boxSizeX ] > 1 ){
               (*counter)++;
               breakloops = true;
               break;
            }
         }
         if ( breakloops ) break;
      }
   }

   free(box);

}
