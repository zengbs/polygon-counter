#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
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
   neel->highList = NULL;
   neel->left     = NULL;
   neel->right    = NULL;
   neel->parent   = NULL;

   root = neel;


   int boxSizeX            = 1000;
   int boxSizeY            = 1000;
   int rectangularMaxSizeX = 10;
   int rectangularMaxSizeY = 10;
   int rectangularMinSizeX = 1;
   int rectangularMinSizeY = 1;

   int *EventListX         = NULL;
   int *EventListY         = NULL;


   FILE *pFile = fopen("Record__polygonCount_vs_time", "w");

#  ifdef TIMER
   double time_sweepLine, time_naive;
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
      int naiveCounter = 0;

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

      NaiveCountOverlappingRectangles( EventListX, EventListY, numRectangles, &naiveCounter );

#     ifdef TIMER
      Stop();
      time_naive = GetValue();
#     endif

      if ( counter != naiveCounter ) REPORT_ERROR;

#     ifdef TIMER
      fprintf( pFile, "%e  %e  %d  %d %d\n", time_sweepLine, time_naive, counter, naiveCounter, numRectangles );
#     endif

   }

   free(EventListX);
   free(EventListY);
   free(neel);

   return 0;
}
