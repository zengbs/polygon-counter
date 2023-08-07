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
         int yy = xL + y*boxSizeX;
         for ( int xx=xL; xx<=xR; xx++ ){
            box[ xx + yy*boxSizeX ]++;
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
         int yy = xL + y*boxSizeX;
         for ( int xx=xL; xx<=xR; xx++ ){
            if ( box[ xx + yy*boxSizeX ] > 1 ){
               (*counter)++;
               breakloops = true;
            }
         }
         if ( breakloops ) break;
      }
   }

}
