#ifndef __INTERVALTREE_H___
#define __INTERVALTREE_H___


#include <stdbool.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <CGAL/Polygon_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>
#include "typedef.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Creator_uniform_2<int, Point_2> Creator;
typedef CGAL::Random_points_in_square_2<Point_2, Creator> Point_generator;

class Polygon {
   public:
      Polygon_2 *polygon;
      bool countedTouching;
      bool countedIntersected;
      bool countedDisjoint;
      bool countedDuplicate;
};


typedef struct Interval{
   UINT low;
   UINT high;
   bool counted;
} Interval;


struct SubIntervalTree {
   UINT key; // high-end of interval
   bool color;
   SubIntervalTreeNode *parent;
   SubIntervalTreeNode *left;
   SubIntervalTreeNode *right;
   UINT max;
   UINT min;
   UINT counted;
   UINT duplicate;
   IntervalTreeNode *SubIntervalTreeRootParent;
   std::list<Polygon> polygonsInSameBoundingBox;
};


struct IntervalTree {
   UINT key; // low-end of interval
   bool color;
   IntervalTreeNode *parent;
   IntervalTreeNode *left;
   IntervalTreeNode *right;
   UINT max;
   UINT min;
   UINT maxKeyInSubIntervalTree;
   SubIntervalTreeNode *SubIntervalTreeRoot;
};

struct EventListX_wrapper_structure{
   UINT EventListX;
   UINT KeyX;
   Polygon* polygon;
};


#endif
