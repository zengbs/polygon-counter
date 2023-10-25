#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "includes/typedef.h"
#include "includes/global.h"
#include "includes/macro.h"


UINT randomNumberInRange( UINT minimum_number, UINT max_number ){

   if ( minimum_number >= max_number ) REPORT_ERROR;

   return rand() % (max_number + 1 - minimum_number) + minimum_number;

}

void RectanglesGeneration(
     UINT numberRectangles,
     UINT boxSizeX, UINT boxSizeY,
     UINT rectangularMaxSizeX, UINT rectangularMaxSizeY,
     UINT rectangularMinSizeX, UINT rectangularMinSizeY,
     UINT rectangleArea,
     UINT **EventListX, UINT **EventListY )
{

   UINT ii = 0;

#  ifdef PRINT_RECTANGLES
   std::ofstream outputFile;
   outputFile.open( "Table__rectangles", std::fstream::out );
   if (!outputFile.is_open()) REPORT_ERROR;

   outputFile << "# boxSizeX            = " << boxSizeX            << std::endl;
   outputFile << "# boxSizeY            = " << boxSizeY            << std::endl;
   outputFile << "# rectangularMaxSizeX = " << rectangularMaxSizeX << std::endl;
   outputFile << "# rectangularMaxSizeY = " << rectangularMaxSizeY << std::endl;
   outputFile << "# rectangularMinSizeX = " << rectangularMinSizeX << std::endl;
   outputFile << "# rectangularMinSizeY = " << rectangularMinSizeY << std::endl;
#  endif

   for (UINT i=0; i<numberRectangles; i++)
   {

      UINT rectangularWidth, rectangularHeight;

      rectangularWidth  = randomNumberInRange( rectangularMinSizeX, rectangularMaxSizeX );

      ( rectangleArea > 0 ) ? ( rectangularHeight = rectangleArea/rectangularWidth ) :
                              ( rectangularHeight = randomNumberInRange( rectangularMinSizeY, rectangularMaxSizeY ) );

      UINT rectangularXL     = randomNumberInRange( 0, boxSizeX - rectangularWidth  );
      UINT rectangularXR     = rectangularXL + rectangularWidth;
      UINT rectangularYB     = randomNumberInRange( 0, boxSizeY - rectangularHeight );
      UINT rectangularYT     = rectangularYB + rectangularHeight;

#     ifdef PRINT_RECTANGLES
      outputFile << rectangularXL << " "
                 << rectangularXR << " "
                 << rectangularYB << " "
                 << rectangularYT << std::endl;
#     endif

      (*EventListX)[ii  ] = rectangularXL;
      (*EventListX)[ii+1] = rectangularXR;
      (*EventListY)[ii  ] = rectangularYB;
      (*EventListY)[ii+1] = rectangularYT;


      ii += 2;
   }

#  ifdef PRINT_RECTANGLES
   outputFile.close();
#  endif

}
