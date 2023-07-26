#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


TreeNode *neel = NULL;
TreeNode *root = NULL;


int main(){

   // Allocate neel node
   neel = (TreeNode*)malloc(sizeof(TreeNode));
   neel->color = BLACK;
   neel->max = INT_MIN;
   neel->highList = NULL;
   neel->left = NULL;
   neel->right = NULL;
   neel->parent = NULL;

   root = neel;


   int numRectanglesMax    = 4471;
   int numRectangles       = 0;
   int boxSizeX            = 1000;
   int boxSizeY            = 1000;
   int rectangularMaxSizeX = 10;
   int rectangularMaxSizeY = 10;
   int rectangularMinSizeX = 1;
   int rectangularMinSizeY = 1;

   int *EventListX         = (int*)malloc(sizeof(int)*numRectanglesMax*2);
   int *EventListY         = (int*)malloc(sizeof(int)*numRectanglesMax*2);

   RectanglesGeneration( numRectanglesMax, &numRectangles, boxSizeX, boxSizeY,
                         rectangularMaxSizeX, rectangularMaxSizeY,
                         rectangularMinSizeX, rectangularMinSizeY,
                         &EventListX, &EventListY );


   printf("Total numRectangles = %d\n", numRectangles);

   int counter = 0;
   int naiveCounter = 0;

   SweepLine( EventListX, EventListY, numRectangles, &counter );

   bool *count = (bool*)calloc(numRectangles, sizeof(bool));
   NaiveCountOverlappingRectangles( count, EventListX, EventListY, numRectangles, &naiveCounter );

   printf("Number of ovrlapping rectangles = %d\n", counter);
   printf("Number of ovrlapping rectangles = %d\n", naiveCounter);

   return 0;
}
