#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include<immintrin.h>
#include"global.h"
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


TreeNode *neel = NULL;
TreeNode *root = NULL;


int main(){


   // Allocate neel node
   neel           = (TreeNode*)malloc(sizeof(TreeNode));
   neel->color    = BLACK;
   neel->max      = INT_MIN;
   neel->min      = INT_MIN;
   neel->low      = INT_MIN;
   neel->highList = NULL;
   neel->left     = NULL;
   neel->right    = NULL;
   neel->parent   = NULL;
   neel->listLength = 0;

   root = neel;


   int boxSizeX            = 1000000000;
   int boxSizeY            = 1000000000;
   int rectangularMaxSizeX = 200;
   int rectangularMaxSizeY = 200;
   int rectangularMinSizeX = 1;
   int rectangularMinSizeY = 1;

   int *EventListX         = NULL;
   int *EventListY         = NULL;


   FILE *pFile = fopen("Record__polygonCount_vs_time", "w");

#  ifdef TIMER
   double time_sweepLine, time_naive;
#  endif

#  ifdef TIMER
   fprintf( pFile, "# boxSizeX = %d\n", boxSizeX );
   fprintf( pFile, "# boxSizeY = %d\n", boxSizeY );
   fprintf( pFile, "# rectangularMaxSizeX = %d\n", rectangularMaxSizeX );
   fprintf( pFile, "# rectangularMaxSizeY = %d\n", rectangularMaxSizeY );
   fprintf( pFile, "# rectangularMinSizeX = %d\n", rectangularMinSizeX );
   fprintf( pFile, "# rectangularMinSizeY = %d\n", rectangularMinSizeY );
#  endif

   for (int numRectangles=10; numRectangles<1000001; numRectangles *= 10)
   {

      EventListX              = (int*)malloc(sizeof(int)*numRectangles*2);
      EventListY              = (int*)malloc(sizeof(int)*numRectangles*2);

      RectanglesGeneration( numRectangles, boxSizeX, boxSizeY,
                            rectangularMaxSizeX, rectangularMaxSizeY,
                            rectangularMinSizeX, rectangularMinSizeY,
                            &EventListX, &EventListY );


      int counter = 0;
#     ifdef NAIVE
      int naiveCounter = 0;
#     endif

#     ifdef TIMER
      Start();
#     endif

      SweepLine( EventListX, EventListY, numRectangles, &counter );

#     ifdef TIMER
      Stop();
      time_sweepLine = GetValue();
#     endif


#     ifdef TIMER
      Start();
#     endif

#     ifdef NAIVE
      NaiveCountOverlappingRectangles( EventListX, EventListY, numRectangles, &naiveCounter );
#     endif

#     ifdef TIMER
      Stop();
      time_naive = GetValue();
#     endif

#     ifdef NAIVE
      if ( counter != naiveCounter ) REPORT_ERROR;
#     endif

#     ifdef TIMER
      fprintf( pFile, "%e  %e  %d  %d %f\n", time_sweepLine, time_naive, counter, numRectangles, (float)counter/(float)numRectangles);
#     endif

      _mm_clflush(EventListX);
      _mm_clflush(EventListY);

      free(EventListX);
      free(EventListY);

   }

   free(neel);
   fclose(pFile);

   return 0;
}
