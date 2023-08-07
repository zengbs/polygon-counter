#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

()


void Pixelization( int numRectangles, int boxSizeX, int boxSizeY, int EventListX, int EventListY, int *counter )
{
   int *box = calloc(boxSizeX*boxSizeY, sizeof(int));

   if ( box == NULL ) REPORT_ERROR;

   int xL, yB, xR, yT;

   for ( int i=0;i<2*numRectangles; i+=2 ){

      xL = EventListX[i];
      yB = EventListY[i];

      xR = EventListX[i+1];
      yT = EventListY[i+1];

      for ( int y=yB; y<=yT; y++ ){
         for ( int x=xL; x<=xR; x++ ){
            box[ x+y*boxSizeX ]++;
         }
      }
   }

   *counter = 0;

   for ( int i=0;i<2*numRectangles; i+=2 ){

      xL = EventListX[i];
      yB = EventListY[i];

      xR = EventListX[i+1];
      yT = EventListY[i+1];

      bool breakloops = false;

      for ( int y=yB; y<=yT; y++ ){
         for ( int x=xL; x<=xR; x++ ){
            if ( box[ x+y*boxSizeX ] > 1 ){
               (*counter)++;
               breakloops = true;
               break;
            }
         }
         if ( breakloops ) break;
      }
   }

}
