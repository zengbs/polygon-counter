#include <iostream>
#include <vector>
#include <list>
#include <CGAL/Polygon_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>
#include "includes/macro.h"
#include "includes/typedef.h"
#include "includes/intervaltree.h"

// https://doc.cgal.org/latest/Boolean_set_operations_2/group__boolean__do__intersect.html


#define INSIDE_POLYGON  (1<<0)
#define OUTSIDE_POLYGON (1<<1)
#define ON_POLYGON      (1<<2)

void check_inside (Point_2 pt, Point_2 *pgn_begin, Point_2 *pgn_end, K traits, int *insideOutsideOnPolygon )
{

   switch (CGAL:: bounded_side_2(pgn_begin, pgn_end, pt, traits)) {

      // The point is inside the polygon
      case CGAL::ON_BOUNDED_SIDE:
      *insideOutsideOnPolygon = INSIDE_POLYGON;
      break;

      // The point is on the polygon boundary
      case CGAL::ON_BOUNDARY:
      *insideOutsideOnPolygon = ON_POLYGON;
      break;

      // The point is outside the polygon
      case CGAL::ON_UNBOUNDED_SIDE:
      *insideOutsideOnPolygon = OUTSIDE_POLYGON;
      break;

   }
}


Segment_2 getEdge( const Polygon_2 &poly, size_t index ){

   if ( index >= poly.size() ) REPORT_ERROR;

   auto vit = poly.vertices_begin();
   std::advance(vit, index);

   auto next = vit;
   ++next;

   if ( next == poly.vertices_end() ){
        next = poly.vertices_begin();
   }

   return Segment_2( *vit, *next );

}


// do_intersect(poly1, poly2)      : determines whether two polygons intersect in their interior.
// do_intersect(segment1, segment2): determines whether two segments have common points.

void detached_or_touching_or_intersection( Polygon_2& poly1, Polygon_2& poly2, int *detachedOrTouchingOrIntersect )
{

   Segment_2 segment1, segment2;

   // Duplicate
   bool DuplicateSegment_2 = false;

   if ( poly1.size() == poly2.size() ){

      for (size_t i=0; i<poly1.size(); i++){

         segment1 = getEdge( poly1, i );
         segment2 = getEdge( poly2, i );


         DuplicateSegment_2  = segment1.source() == segment2.source() && segment1.target() == segment2.target();
         DuplicateSegment_2 |= segment1.source() == segment2.target() && segment1.target() == segment2.source();

         if ( !DuplicateSegment_2 ) break;
      }
   }

   if ( DuplicateSegment_2 ){
      *detachedOrTouchingOrIntersect = DUPLICATE_POLYGONS;
      return;
   }

       // Ensure counter-clockwise orientation
    if (poly1.orientation() != CGAL::COUNTERCLOCKWISE) {
        poly1.reverse_orientation();
    }

    if (poly2.orientation() != CGAL::COUNTERCLOCKWISE) {
        poly2.reverse_orientation();
    }


   if ( CGAL::do_intersect( poly1, poly2 ) ){
      *detachedOrTouchingOrIntersect = INTERSECT_POLYGONS;
      return;
   }

   bool insidePoly  = false;
   bool onPoly      = false;
   bool outsidePoly = true;

   // O(V)
   for ( Polygon_2::Vertex_iterator it = poly1.vertices_begin(); it != poly1.vertices_end(); ++it){

      Point_2 vertex = *it;

      // O(V)
      switch (CGAL:: bounded_side_2( poly2.vertices_begin(), poly2.vertices_end(), vertex, K())) {

         // The point is inside the polygon
         case CGAL::ON_BOUNDED_SIDE:
            insidePoly |= true;
            outsidePoly &= false;
         break;

         // The point is on the polygon boundary
         case CGAL::ON_BOUNDARY:
            onPoly |= true;
            outsidePoly &= false;
         break;

         // The point is outside the polygon
         case CGAL::ON_UNBOUNDED_SIDE:
            outsidePoly &= true;
         break;

      }

      if ( insidePoly ) break;

   }

   if ( !insidePoly ){

      // O(V)
      for ( Polygon_2::Vertex_iterator it = poly2.vertices_begin(); it != poly2.vertices_end(); ++it){

         Point_2 vertex = *it;

         // O(V)
         switch (CGAL:: bounded_side_2( poly1.vertices_begin(), poly1.vertices_end(), vertex, K())) {

            // The point is inside the polygon
            case CGAL::ON_BOUNDED_SIDE:
               insidePoly |= true;
               outsidePoly &= false;
            break;

            // The point is on the polygon boundary
            case CGAL::ON_BOUNDARY:
               onPoly |= true;
               outsidePoly &= false;
            break;

            // The point is outside the polygon
            case CGAL::ON_UNBOUNDED_SIDE:
               outsidePoly &= true;
            break;

         }

         if ( insidePoly ) break;

      }

   }


   if ( outsidePoly ){
      *detachedOrTouchingOrIntersect = DISJOINT_POLYGONS;
      return;
   }

   else if ( onPoly && !outsidePoly ){
      *detachedOrTouchingOrIntersect = TOUCHING_POLYGONS;
   }else REPORT_ERROR;


}
