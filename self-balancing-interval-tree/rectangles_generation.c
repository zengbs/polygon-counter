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

#  ifdef PRINT_RECTANGLES
   FILE *pFile = fopen("table__rectangles", "w");

   if ( numberRectangles == 100 ){
      fprintf( pFile, "# boxSizeX = %d\n", boxSizeX );
      fprintf( pFile, "# boxSizeY = %d\n", boxSizeY );
      fprintf( pFile, "# rectangularMaxSizeX = %d\n", rectangularMaxSizeX );
      fprintf( pFile, "# rectangularMaxSizeY = %d\n", rectangularMaxSizeY );
      fprintf( pFile, "# rectangularMinSizeX = %d\n", rectangularMinSizeX );
      fprintf( pFile, "# rectangularMinSizeY = %d\n", rectangularMinSizeY );
   }
#  endif

   for (int i=0; i<numberRectangles; i++)
   {
      int rectangularWidth  = randomNumberInRange( rectangularMinSizeX, rectangularMaxSizeX );
      int rectangularHeight = randomNumberInRange( rectangularMinSizeY, rectangularMaxSizeY );

      int rectangularXL     = randomNumberInRange( 0, boxSizeX - rectangularWidth  );
      int rectangularXR     = rectangularXL + rectangularWidth;
      int rectangularYB     = randomNumberInRange( 0, boxSizeY - rectangularHeight );
      int rectangularYT     = rectangularYB + rectangularHeight;

#     ifdef PRINT_RECTANGLES
      if ( numberRectangles == 100 )
         fprintf(pFile, "%d %d %d %d\n", rectangularXL, rectangularYB, rectangularWidth, rectangularHeight );
#     endif

      (*EventListX)[ii  ] = rectangularXL;
      (*EventListX)[ii+1] = rectangularXR;
      (*EventListY)[ii  ] = rectangularYB;
      (*EventListY)[ii+1] = rectangularYT;


      ii += 2;
   }

#  ifdef PRINT_RECTANGLES
   fclose(pFile);
#  endif

}
