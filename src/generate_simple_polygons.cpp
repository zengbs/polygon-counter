#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"

typedef K::FT FT;

// Custom hash function for Polygon_2
struct Polygon2Hash {
    std::size_t operator()(const Polygon_2& poly) const {

        // Use a hash function for the vertices of the polygon
        std::size_t seed = 0;
        for (auto v = poly.vertices_begin(); v != poly.vertices_end(); ++v) {
            seed ^= std::hash<double>()(CGAL::to_double(v->x())) ^ std::hash<double>()(CGAL::to_double(v->y()));
        }
        return seed;
    }
};


// Function to generate a random simple polygon within a specified range.
void GenerateRandomSimplePolygon(int boxSizeX, int boxSizeY, Polygon_2& simplePolygon, UINT inputNumberObject)
{

    int numPoints = 11;

    // Vector to store the generated points.
    std::vector<Point_2> points;


    // Generate random rectangulars in the specified range.
    UINT rectangularWidth  = randomNumberInRange( 1, 20 );
    UINT rectangularHeight = randomNumberInRange( 1, 20 );

    UINT rectangularXL     = randomNumberInRange( 0, boxSizeX - rectangularWidth  );
    UINT rectangularXR     = rectangularXL + rectangularWidth;
    UINT rectangularYB     = randomNumberInRange( 0, boxSizeY - rectangularHeight );
    UINT rectangularYT     = rectangularYB + rectangularHeight;


    // Generate random points in the random rectangulars
    for (int i = 0; i < numPoints; ++i) {
       int x = randomNumberInRange( rectangularXL, rectangularXR );
       int y = randomNumberInRange( rectangularYB, rectangularYT );
       points.push_back(Point_2(x, y));
    }


    // Remove duplicate points.
    points.erase(std::unique(points.begin(), points.end()), points.end());


    // Compute the convex hull
    std::vector<Point_2> convexHullPoints;
    CGAL::convex_hull_2(points.begin(), points.end(), std::back_inserter(convexHullPoints));

    // Ensure counterclockwise order
    if ( convexHullPoints.size() > 3 ){
       if( CGAL::right_turn( convexHullPoints[0], convexHullPoints[1], convexHullPoints[2] ) ){
          std::reverse(convexHullPoints.begin(), convexHullPoints.end());
       }
    }



    for( const Point_2& vertex : convexHullPoints ){
       simplePolygon.push_back(vertex);
    }


    bool isSimple = CGAL::is_simple_2( simplePolygon.vertices_begin(), simplePolygon.vertices_end(), K() );


    if ( !isSimple ) REPORT_ERROR;


}


void FindBoundingBox( std::vector<Point_2> simplePolygon, UINT *xL, UINT *xR, UINT *yB, UINT *yT )
{

    // Compute and print the bounding box of the polygon.
    FT min_x = simplePolygon[0].x();
    FT max_x = simplePolygon[0].x();
    FT min_y = simplePolygon[0].y();
    FT max_y = simplePolygon[0].y();

    for (const Point_2& p : simplePolygon) {
        min_x = std::min(min_x, p.x());
        max_x = std::max(max_x, p.x());
        min_y = std::min(min_y, p.y());
        max_y = std::max(max_y, p.y());
    }

    *xL = static_cast<UINT>(CGAL::to_double(min_x));
    *xR = static_cast<UINT>(CGAL::to_double(max_x));
    *yB = static_cast<UINT>(CGAL::to_double(min_y));
    *yT = static_cast<UINT>(CGAL::to_double(max_y));

}

void GenerateEventLists( int boxSizeX, int boxSizeY, UINT inputNumberObject,
                         UINT **EventListX, UINT **EventListY, UINT *DuplicateCounter,
                         Polygon ***polygonArray, Polygon ***polygonFullArray )
{

   UINT xL, xR, yB, yT;

   *EventListX = (UINT*)calloc(inputNumberObject*2, sizeof(UINT));
   *EventListY = (UINT*)calloc(inputNumberObject*2, sizeof(UINT));


   UINT j = 0;

   *polygonFullArray = new Polygon*[inputNumberObject];

   for (int i=0; i<(int)inputNumberObject; i++)
   {
      std::vector<Point_2> points;
      Polygon_2 simplePolygon;

      if ( i <= 2 || i%((int)(0.1*inputNumberObject)) != 0 )
      {
         GenerateRandomSimplePolygon( boxSizeX, boxSizeY, simplePolygon, inputNumberObject );

         // Make sure the number of vertices is greater than 2
         if ( simplePolygon.size() <= 2 ) { --i; continue; }

      }else{
         int index = i/2;
         simplePolygon = *((*polygonFullArray)[index]->polygon);
      }

      for ( auto vertex = simplePolygon.vertices_begin(); vertex != simplePolygon.vertices_end(); vertex++ )
         points.push_back(*vertex);

      (*polygonFullArray)[i]                     = new Polygon;
      (*polygonFullArray)[i]->polygon            = new Polygon_2( points.begin(), points.end() );
      (*polygonFullArray)[i]->countedTouching    = false;
      (*polygonFullArray)[i]->countedIntersected = false;
      (*polygonFullArray)[i]->countedDisjoint    = false;
      (*polygonFullArray)[i]->countedDuplicate   = false;

      FindBoundingBox( points, &xL, &xR, &yB, &yT );

      (*EventListX)[j  ] = xL;
      (*EventListX)[j+1] = xR;
      (*EventListY)[j  ] = yB;
      (*EventListY)[j+1] = yT;

      j += 2;

   } // for (int i=0; i<(int)inputNumberObject; i++)

}
