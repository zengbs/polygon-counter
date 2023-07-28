#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"global.h"
#include"macro.h"


int randomNumberInRange( int minimum_number, int max_number ){

   return rand() % (max_number + 1 - minimum_number) + minimum_number;

}

void RectanglesGeneration(
     int numberRectangles,
     int boxSizeX, int boxSizeY,
     int rectangularMaxSizeX, int rectangularMaxSizeY,
     int rectangularMinSizeX, int rectangularMinSizeY,
     int **EventListX, int **EventListY )
{
   //srand(time(NULL));
   srand(0);

   int ii = 0;

   for (int i=0; i<numberRectangles; i++)
   {
      int rectangularWidth  = randomNumberInRange( rectangularMinSizeX, rectangularMaxSizeX );
      int rectangularHeight = randomNumberInRange( rectangularMinSizeY, rectangularMaxSizeY );

      int rectangularXL     = randomNumberInRange( 0, boxSizeX - rectangularWidth  );
      int rectangularXR     = rectangularXL + rectangularWidth;
      int rectangularYB     = randomNumberInRange( 0, boxSizeY - rectangularHeight );
      int rectangularYT     = rectangularYB + rectangularHeight;

      (*EventListX)[ii  ] = rectangularXL;
      (*EventListX)[ii+1] = rectangularXR;
      (*EventListY)[ii  ] = rectangularYB;
      (*EventListY)[ii+1] = rectangularYT;

#     ifdef DEBUG
      printf("Rectangle: %d, %d, %d, %d\n", rectangularXL, rectangularXR, rectangularYB, rectangularYT);
#     endif

      ii += 2;
   }
}
