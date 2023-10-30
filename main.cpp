#include <pthread.h>
#include <iomanip>
#include <math.h>
#include <iostream>
#include <boost/format.hpp>
#include <fstream>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <immintrin.h>
#include <vector>
#include <list>
#include <CGAL/Polygon_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>
#include "includes/typedef.h"
#include "includes/global.h"
#include "includes/macro.h"
#include "includes/intervaltree.h"
#include "includes/prototypes.h"


IntervalTreeNode *neel       = NULL;
IntervalTreeNode *root       = NULL;
double time_sweepline1, time_sweepline2, time_sweepline3,
       time_sweepline4, time_sweepline5, time_sweepline6, time_sweepline7;
unsigned long timeUL_sweepline1, timeUL_sweepline2, timeUL_sweepline3,
              timeUL_sweepline4, timeUL_sweepline5, timeUL_sweepline6, timeUL_sweepline7;



int main(int argc, char *argv[]){

   time_t seed = time(NULL);
   srand(seed);

   if ( sizeof(UINT) != BYTE_SIZE_INT  ) REPORT_ERROR;


   // Allocate neel node for IntervalTreeNode
   neel                          = new IntervalTreeNode;
   neel->key                     = __INT_MIN;
   neel->color                   = BLACK_NODE;
   neel->parent                  = NULL;
   neel->left                    = NULL;
   neel->right                   = NULL;
   neel->max                     = __INT_MIN;
   neel->min                     = __INT_MAX;
   neel->maxKeyInSubIntervalTree = __INT_MIN;
   neel->SubIntervalTreeRoot     = (SubIntervalTreeNode*)neel;

   root = neel;

   UINT *EventListX         = NULL;
   UINT *EventListY         = NULL;

#  ifdef QUICK_START
   std::string fileName = "Record__polygonCount_vs_time";
#  else
   std::string fileName = "Record__polygonCount_vs_time__" + std::string(argv[1]);
#  endif
   std::ofstream outputFile(fileName);

   if (!outputFile.is_open()) REPORT_ERROR;


#  ifdef TIMER
   double time_naive, time_pixelization;
   unsigned long timeUL_naive, timeUL_pixelization;
#  endif

#  if   ( defined SAME_SCALE ) || ( defined QUICK_START )
   UINT inputNumberObjects = 1000;
#  elif ( defined SCALING_BIGBOX ) || ( defined SCALING_SMALLBOX )
   UINT inputNumberObjects = 100;
#  endif


#  ifdef QUICK_START
   std::cout << "Generating " << inputNumberObjects  <<  " polygons..." <<  std::endl;
#  endif

#  ifdef QUICK_START
   bool stop = true;
#  else
   bool stop = false;
#  endif


   do
   {
#     ifdef SCALING_BIGBOX
      UINT boxSizeX            = __UINT_MAX;
      UINT boxSizeY            = __UINT_MAX;
#     endif

#     ifdef SCALING_SMALLBOX
      UINT boxSizeX            = 20000;
      UINT boxSizeY            = 20000;
#     endif

#     if  ( defined SAME_SCALE ) || ( defined QUICK_START )
      UINT boxSizeX            = (UINT)(sqrt((double)inputNumberObjects))*100;
      UINT boxSizeY            = (UINT)(sqrt((double)inputNumberObjects))*100;
#     endif

#     ifdef TIMER
      outputFile << "# boxSizeX            = " << boxSizeX            << std::endl;
      outputFile << "# boxSizeY            = " << boxSizeY            << std::endl;
      outputFile << "# Generate wrapper      Sorting               Segregate             Counting              Insertion             Deleteion             SweepLine             Pixelization          Naive" << std::endl;
#     endif

      UINT RectangularCounter = 0;
      UINT DuplicateCounter = 0;
      UINT TouchingCounter = 0;
      UINT IntersectedCounter = 0;

#     ifdef NAIVE
      UINT NaiveDuplicateCounter = 0;
      UINT NaiveTouchingCounter = 0;
      UINT NaiveIntersectedCounter = 0;
      UINT NaiveDisjointCounter = 0;
#     endif

      Polygon **polygonArray     = NULL;
      Polygon **polygonFullArray = NULL;

      GenerateEventLists( boxSizeX, boxSizeY, inputNumberObjects,
                          &EventListX, &EventListY, &DuplicateCounter,
                          &polygonArray, &polygonFullArray );

#     ifdef NAIVE
      UINT NaiveRectangularCounter = 0;
#     endif

#     ifdef PIXELIZATION
      UINT pixelizationCounter = 0;
#     endif

      SweepLine( &root, polygonFullArray, EventListX, EventListY, inputNumberObjects,
                 &RectangularCounter, &TouchingCounter, &IntersectedCounter, &DuplicateCounter );

#     ifdef QUICK_START
      std::cout << "\nEfficient algorithm:" << std::endl
                << "Overlapping/touching bounding box counter = " << RectangularCounter << std::endl
                << "Duplicate counter                         = " << DuplicateCounter << std::endl
                << "Touching counter                          = " << TouchingCounter << std::endl
                << "Intersected counter                       = " << IntersectedCounter << std::endl << std::endl;
#     endif

#     ifdef TIMER
      Start(&timeUL_naive);
#     endif

#     ifdef NAIVE
      NaiveCheckIntersection( polygonFullArray, inputNumberObjects, &NaiveIntersectedCounter,
                         &NaiveTouchingCounter, &NaiveDuplicateCounter, &NaiveDisjointCounter );

      NaiveCountOverlappingRectangles( EventListX, EventListY, inputNumberObjects, &NaiveRectangularCounter );
#     endif

#     ifdef TIMER
      Stop(&timeUL_naive);
      time_naive = GetValue(&timeUL_naive);
#     endif


#     ifdef NAIVE
      std::cout << "Naive algorithm:" << std::endl
                << "Overlapping/touching bounding box counter = " << RectangularCounter << std::endl
                << "Duplicate counter                         = " << NaiveDuplicateCounter << std::endl
                << "Touching counter                          = " << NaiveTouchingCounter << std::endl
                << "Intersected counter                       = " << NaiveIntersectedCounter << std::endl;

      if ( RectangularCounter != NaiveRectangularCounter ||
           DuplicateCounter   != NaiveDuplicateCounter   ||
           TouchingCounter    != NaiveTouchingCounter    ||
           IntersectedCounter != NaiveIntersectedCounter ){
              printf("%lld\n", (long long) seed);
              std::cout << "Fail!" << std::endl;
              REPORT_ERROR;
      }else std::cout << std::endl << "Pass!" << std::endl;
#     else
      std::cout << "Rectangular counter = " << RectangularCounter << std::endl
                << "Duplicate counter = " << DuplicateCounter << std::endl
                << "Touching counter = " << TouchingCounter << std::endl
                << "Intersected counter = " << IntersectedCounter << std::endl << std::endl;
#     endif




#     ifdef TIMER
      Start(&timeUL_pixelization);
#     endif

#     ifdef PIXELIZATION
      Pixelization( inputNumberObjects, boxSizeX, boxSizeY, EventListX, EventListY, &pixelizationCounter );
#     endif

#     ifdef TIMER
      Stop(&timeUL_pixelization);
      time_pixelization = GetValue(&timeUL_pixelization);
#     endif

#     ifdef PIXELIZATION
      if ( RectangularCounter != pixelizationCounter )
         { std::cout << "Fail! " << RectangularCounter << "!=" << pixelizationCounter << "!\n" << std::endl; }
#     endif

#     ifdef TIMER
      outputFile  << boost::format("%21.13e")  % time_sweepline1    << " "
                  << boost::format("%21.13e")  % time_sweepline2    << " "
                  << boost::format("%21.13e")  % time_sweepline3    << " "
                  << boost::format("%21.13e")  % time_sweepline4    << " "
                  << boost::format("%21.13e")  % time_sweepline5    << " "
                  << boost::format("%21.13e")  % time_sweepline6    << " "
                  << boost::format("%21.13e")  % time_sweepline7    << " "
                  << boost::format("%21.13e")  % time_pixelization  << " "
                  << boost::format("%21.13e")  % time_naive         << " "
                  << boost::format("%16llu")   % RectangularCounter << " "
                  << boost::format("%16llu")   % inputNumberObjects << " "
                  << boost::format("%6.4f%%")  % ((float)RectangularCounter/(float)inputNumberObjects*100) << std::endl << std::flush;
#     endif

      _mm_clflush(EventListX);
      _mm_clflush(EventListY);

      free(EventListX);
      free(EventListY);


      FreePolygonArray( &polygonFullArray, inputNumberObjects );

      if ( checkIntOverflow( inputNumberObjects, (UINT)10, '*' )){
         inputNumberObjects = (UINT)__INT_MAX/(UINT)1;
         printf("inputNumberObjects overflow!\n");
         stop = true;
      }else{
#        if   ( defined SAME_SCALE )
         inputNumberObjects *= 1;
#        elif ( defined SCALING_BIGBOX ) || ( defined SCALING_SMALLBOX )
         inputNumberObjects *= 10;
         if ( inputNumberObjects == 1e9 ) break;
#        endif
      }

#     ifndef QUICK_START
      std::cout << boost::format("Calculating %16llu ...")   % inputNumberObjects << std::endl;
#     endif
   }
   while( !stop );

   delete neel;

   outputFile.close();

   return 0;
}
