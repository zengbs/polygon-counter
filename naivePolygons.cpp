#include "includes/intervaltree.h"
#include "includes/prototypes.h"

void NaiveCheckIntersection( Polygon **polygonArray, UINT numberObjects, UINT *IntersectedCounter,
                             UINT *TouchingCounter, UINT *DuplicateCounter, UINT *DisjointCounter )
{

   int detachedOrTouchingOrIntersect;


   for ( UINT i=0; i<numberObjects; i++ ){
      for ( UINT j=i+1; j<numberObjects; j++ ){
         Polygon& poly1 = *(polygonArray[i]);
         Polygon& poly2 = *(polygonArray[j]);

         poly1.countedIntersected = false;
         poly2.countedIntersected = false;
         poly1.countedTouching    = false;
         poly2.countedTouching    = false;
         poly1.countedDuplicate   = false;
         poly2.countedDuplicate   = false;
         poly1.countedDisjoint    = false;
         poly2.countedDisjoint    = false;
      }
   }


   for ( UINT i=0; i<numberObjects; i++ ){
      for ( UINT j=i+1; j<numberObjects; j++ ){

         Polygon& poly1 = *(polygonArray[i]);
         Polygon& poly2 = *(polygonArray[j]);


         detached_or_touching_or_intersection( *(poly1.polygon), *(poly2.polygon), &detachedOrTouchingOrIntersect );

         switch ( detachedOrTouchingOrIntersect ){

            case INTERSECT_POLYGONS: // 1
               if ( !poly1.countedIntersected ) (*IntersectedCounter)++;
               if ( !poly2.countedIntersected ) (*IntersectedCounter)++;
               poly1.countedIntersected = true;
               poly2.countedIntersected = true;
               break;

            case TOUCHING_POLYGONS: // 2
               if ( !poly1.countedTouching ) (*TouchingCounter)++;
               if ( !poly2.countedTouching ) (*TouchingCounter)++;
               poly1.countedTouching = true;
               poly2.countedTouching = true;
               break;

            case DUPLICATE_POLYGONS: // 8
               if ( !poly1.countedDuplicate ) (*DuplicateCounter)++;
               if ( !poly2.countedDuplicate ) (*DuplicateCounter)++;
               poly1.countedDuplicate = true;
               poly2.countedDuplicate = true;
               break;

            case DISJOINT_POLYGONS: // 4
               if ( !poly1.countedDisjoint ) (*DisjointCounter)++;
               if ( !poly2.countedDisjoint ) (*DisjointCounter)++;
               poly1.countedDisjoint = true;
               poly2.countedDisjoint = true;
               break;
         }
      }
   }

}
