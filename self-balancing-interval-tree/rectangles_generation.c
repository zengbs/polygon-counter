#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int randomNumberInRange( int minimum_number, int max_number ){

   return rand() % (max_number + 1 - minimum_number) + minimum_number;

}

void RectanglesGeneration(
     int numberRectangles, int boxSizeX, int boxSizeY,
     int rectangularMaxSizeX, int rectangularMaxSizeY,
     int rectangularMinSizeX, int rectangularMinSizeY,
     int *EventListX, int *EventListY )
{
   //srand(time(NULL));
   srand(0);

   for (int i=0; i<numberRectangles; i += 2)
   {
      int rectangularXL = randomNumberInRange( 0, boxSizeX );
      int rectangularXR = rectangularXL + randomNumberInRange( rectangularMinSizeX, rectangularMaxSizeX );
      int rectangularYB = randomNumberInRange( 0, boxSizeY );
      int rectangularYT = rectangularYB + randomNumberInRange( rectangularMinSizeY, rectangularMaxSizeY );

      if (  ( 0 < rectangularXR && rectangularXR < boxSizeX )
         && ( 0 < rectangularYT && rectangularYT < boxSizeY ) )
      {
         EventListX[i  ] = rectangularXL;
         EventListX[i+1] = rectangularXR;
         EventListY[i  ] = rectangularYB;
         EventListY[i+1] = rectangularYT;
      }
   }
}
