#include <iostream>
#include <fstream>
#include <type_traits>
#include <limits.h>
#include "../includes/typedef.h"
#include "../includes/global.h"
#include "../includes/macro.h"
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"


UINT max( UINT a, UINT b, UINT c )
{
   UINT d = MAX( a, b );
   return MAX( d, c );
}

UINT min( UINT a, UINT b, UINT c )
{
   UINT d = MIN( a, b );
   return MIN( d, c );
}


template <typename T>
void SwapReference( T& a, T& b )
{
   T temp = a;
   a = b;
   b = temp;
}

void SwapPointer( void **ptr1, void **ptr2 )
{
   void *temp = *ptr1;
   *ptr1 = *ptr2;
   *ptr2 = temp;
}


void XorSwap(UINT *x, UINT *y)
{
  if (x != y)
  {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
  }
}

template <typename T>
bool isLeftChild( T *node, char const *fileName, int line )
{
   if      ( node->parent->left == node ) return true;
   else if ( node->parent->right == node ) return false;
   else { printf( "Error: %s(%d)\n", fileName, line ); exit(EXIT_FAILURE); return false; }
}


template <typename T>
T* allocateTreeNode( T **parent, Interval *intervalY, bool color, int left_root_right)
{
   // Using `new` rather than `malloc` to call a constructor to initializec a C++ object
   T* newNode = new T;

   if ( newNode == NULL ) REPORT_ERROR;

   newNode->left   = (T*)neel;
   newNode->right  = (T*)neel;
   newNode->color  = color;
   newNode->max    = intervalY->high;
   newNode->min    = intervalY->low;

   if constexpr ( std::is_same<T, IntervalTreeNode>::value ){
      newNode->key                 = intervalY->low;
      newNode->maxKeyInSubIntervalTree = intervalY->high;
      newNode->SubIntervalTreeRoot = (SubIntervalTreeNode*)neel;
   }

   if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
      newNode->key       = intervalY->high;
      newNode->counted   = (intervalY->counted) ? 1 : 0;
      newNode->duplicate = 1;
   }



   if ( left_root_right == ROOT_NODE ){
      newNode->parent = (T*)neel;
      *parent         = newNode;
   }
   else if ( left_root_right == LEFT_CHILD ){
      newNode->parent = *parent;
      (*parent)->left = newNode;
   }else{
      newNode->parent  = *parent;
      (*parent)->right = newNode;
   }

   return newNode;
}


template <typename T>
void printInorder( T *node ){

   if ( node == (T*)neel ) return;

   printInorder(node->left);

   std::cout << node->key;

   printInorder(node->right);

}


template <typename T>
void InorderChecking( T *node ){

   if ( node == (T*)neel ) return;


   // Check binary properties
   if (node->left->key  != __UINT_MIN) ASSERT( node->left->key  < node->key );
   if (node->right->key != __UINT_MIN) ASSERT( node->right->key > node->key );

   ASSERT( node->max >= node->key );
   ASSERT( node->min <= node->key );

   if constexpr( std::is_same<T, IntervalTreeNode>::value ){
      UINT max = FindMaxInTree(node->SubIntervalTreeRoot );
      if ( max != node->maxKeyInSubIntervalTree  ){
         std::cout << "max=" << "node->maxKeyInSubIntervalTree=" << max << node->maxKeyInSubIntervalTree << "\n";
      }
      ASSERT( max == node->maxKeyInSubIntervalTree );

      ASSERT( node->SubIntervalTreeRoot->SubIntervalTreeRootParent == node );
   }


   InorderChecking(node->left);
   InorderChecking(node->right);

}


template <typename T>
UINT FindMaxInTree( T *node){

    // Base case
    if (node == (T*)neel)   return __INT_MIN;

    // Return maximum of 3 values:
    // 1) Root's data 2) Max in Left Subtree
    // 3) Max in right subtree
    UINT res = node->key;
    UINT lres = FindMaxInTree(node->left);
    UINT rres = FindMaxInTree(node->right);

    if (lres > res)        res = lres;
    if (rres > res)        res = rres;

    return res;
}


// Only works for the node having both child
template <typename T>
T* inorderSuccessor( T *node ){

   T *current = node->right;

   while( current->left != (T*)neel ){
      current = current->left;
   }

   return current;
}


bool IsOverlappingIntervals( Interval *interval1, Interval *interval2 )
{
   if      ( ( interval1->low < interval2->low  ) && ( interval2->low  < interval1->high ) ) return true;
   else if ( ( interval1->low < interval2->high ) && ( interval2->high < interval1->high ) ) return true;
   else if ( ( interval2->low < interval1->low  ) && ( interval1->low  < interval2->high ) ) return true;
   else if ( ( interval2->low < interval1->high ) && ( interval1->high < interval2->high ) ) return true;
   else return false;
}

bool IsTouchingIntervals( Interval *interval1, Interval *interval2 )
{
   if ( ( interval1->high == interval2->low ) ^ ( interval2->high == interval1->low ) ) return true;
   else return false;
}


bool IsDuplicateIntervals( Interval *interval1, Interval *interval2 )
{
   if ( ( interval1->high == interval2->high ) && ( interval1->low == interval2->low ) ) return true;
   else return false;
}


void CountPolygonInList( Polygon* testPolygon, std::list<Polygon>& polygonsInSameBoundingBox,
                         UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter )
{

   int detachedOrTouchingOrIntersect;

   for ( Polygon& polygonInNode : polygonsInSameBoundingBox )
   {

      Polygon& poly1 = *(testPolygon);
      Polygon& poly2 =   polygonInNode;

      detached_or_touching_or_intersection( *(poly1.polygon), *(poly2.polygon), &detachedOrTouchingOrIntersect );

      if ( detachedOrTouchingOrIntersect == INTERSECT_POLYGONS )
      {
         if ( poly2.countedIntersected == false && poly1.countedIntersected == true )
         {
            (*IntersectedCounter)++;
            poly2.countedIntersected = true;
         }

         else if ( poly2.countedIntersected == true && poly1.countedIntersected == false )
         {
            (*IntersectedCounter)++;
            poly1.countedIntersected = true;
         }

         else if ( poly2.countedIntersected == false && poly1.countedIntersected == false )
         {
            (*IntersectedCounter) += 2;
            poly1.countedIntersected = true;
            poly2.countedIntersected = true;

         }else{ /* Do nothing */ };
      }
      else if ( detachedOrTouchingOrIntersect == TOUCHING_POLYGONS )
      {
         if ( poly2.countedTouching == false && poly1.countedTouching == true )
         {
            (*TouchingCounter)++;
            poly2.countedTouching = true;
         }

         else if ( poly2.countedTouching == true && poly1.countedTouching == false )
         {
            (*TouchingCounter)++;
            poly1.countedTouching = true;
         }

         else if ( poly2.countedTouching == false && poly1.countedTouching == false )
         {
            (*TouchingCounter) += 2;
            poly1.countedTouching = true;
            poly2.countedTouching = true;

         }else{ /* Do nothing */ };
      }
      else if ( detachedOrTouchingOrIntersect == DUPLICATE_POLYGONS )
      {
         if ( poly2.countedDuplicate == false && poly1.countedDuplicate == true )
         {
            (*DuplicateCounter)++;
            poly2.countedDuplicate = true;
         }

         else if ( poly2.countedDuplicate == true && poly1.countedDuplicate == false )
         {
            (*DuplicateCounter)++;
            poly1.countedDuplicate = true;
         }

         else if ( poly2.countedDuplicate == false && poly1.countedDuplicate == false )
         {
            (*DuplicateCounter) += 2;
            poly1.countedDuplicate = true;
            poly2.countedDuplicate = true;

         }else{ /* Do nothing */ };
      }
      else {  /* Do nothing */ };

   }

}

void CountIntervalInNode( SubIntervalTreeNode *treeNode, Interval *intervalY,
                          Polygon *testPolygon, UINT *numberCounted,
                          UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter )
{


   Interval intervalYNode;

   intervalYNode.low  = treeNode->min;
   intervalYNode.high = treeNode->key;

   UINT nonCounted = (treeNode->duplicate) - (treeNode->counted);
   bool overlap  = IsOverlappingIntervals( intervalY, &intervalYNode );
        overlap |= IsTouchingIntervals( intervalY, &intervalYNode );
   bool duplicate = IsDuplicateIntervals( intervalY, &intervalYNode );

#  ifdef DEBUG
   printf("+++++++++++++++++\n");
   printf("A: intervalY->counted = %d\n", intervalY->counted );
   printf("A: intervalY    : [%d, %d]\n", intervalY->low,       intervalY->high );
   printf("A: intervalYNode: [%d, %d]\n", intervalYNode.low,    intervalYNode.high );
   printf("overlap = %d, duplicate=%d\n", overlap, duplicate );
   printf("+++++++++++++++++\n");
#  endif

   if ( duplicate && intervalY->counted == true ){
      (treeNode->counted)++;
   }

   if ( duplicate && intervalY->counted == false ){
      (treeNode->counted)++;
      intervalY->counted = true;
      (*numberCounted)++;
#     ifdef DEBUG
      printf("numberCounted: %d --> %d\n", (*numberCounted)-1, *numberCounted );
#     endif
#     ifdef DEBUG
      printf("====== Case0 =====\n");
      printf("A: intervalY    : [%d, %d]\n", intervalY->low,       intervalY->high );
      printf("A: intervalYNode: [%d, %d]\n", intervalYNode.low,    intervalYNode.high );
      printf("==================\n");
#     endif
   }

   if ( duplicate || overlap )
      CountPolygonInList( testPolygon, treeNode->polygonsInSameBoundingBox, TouchingCounter, IntersectedCounter, DuplicateCounter );

   if ( overlap   && intervalY->counted == false ){
      intervalY->counted = true;
      (*numberCounted)++;
#     ifdef DEBUG
      printf("numberCounted: %d --> %d\n", (*numberCounted)-1, *numberCounted );
#     endif
#     ifdef DEBUG
      printf("====== Case1 =====\n");
      printf("A: intervalY    : [%d, %d]\n", intervalY->low,       intervalY->high );
      printf("A: intervalYNode: [%d, %d]\n", intervalYNode.low,    intervalYNode.high );
      printf("==================\n");
#     endif
   }


   // nonCounted always equals to 1
   if ( ( overlap || duplicate ) && nonCounted > 0 ){
      (*numberCounted) += nonCounted;
      treeNode->counted = duplicate ? treeNode->duplicate+1 : treeNode->duplicate;
#     ifdef DEBUG
      printf("numberCounted: %d --> %d\n", (*numberCounted)-nonCounted, *numberCounted );
#     endif
#     ifdef DEBUG
      printf("====== Case2 =====\n");
      printf("A: intervalY    : [%d, %d]\n", intervalY->low,       intervalY->high );
      printf("A: intervalYNode: [%d, %d]\n", intervalYNode.low,    intervalYNode.high );
      printf("==================\n");
#     endif
   }

}


template <typename T>
void CountOverlappingInterval( T *current, Interval *intervalY, Polygon* polygon, UINT *RectangularCounter,
                               UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter )
{

   if ( current == (T*)neel ) return;

   if constexpr ( std::is_same<T, IntervalTreeNode>::value )
      CountOverlappingInterval( current->SubIntervalTreeRoot, intervalY, polygon,
                                RectangularCounter, TouchingCounter, IntersectedCounter, DuplicateCounter );


   if constexpr ( std::is_same<T, SubIntervalTreeNode>::value )
      CountIntervalInNode( current, intervalY, polygon,
                           RectangularCounter, TouchingCounter,
                           IntersectedCounter, DuplicateCounter );

   if ( current->left != (T*)neel && current->left->max >= intervalY->low ){
      CountOverlappingInterval( current->left, intervalY, polygon, RectangularCounter, TouchingCounter, IntersectedCounter, DuplicateCounter );
#     ifdef DEBUG
      printf("Go to left\n");
#     endif
   }

   if ( current->right != (T*)neel && current->right->min <= intervalY->high ){
      CountOverlappingInterval( current->right, intervalY, polygon, RectangularCounter, TouchingCounter, IntersectedCounter, DuplicateCounter );
#     ifdef DEBUG
      printf("Go to right\n");
#     endif
   }

}



template <typename T>
void SearchTreeNode( T *root, UINT key, T** node )
{
   T *current = root;

#  ifdef DEBUG
   if (current == (T*)neel) {printf("key=%d\n", key); exit(1);}
#  endif

   while( current->key != key ){
      current = ( current->key > key ) ? ( current->left ) : ( current->right );
      if ( current == (T*)neel ) REPORT_ERROR;
   }

   *node = current;

}

// ====== Print the structure of tree on 2D plane =======================
// ======================================================================
#define COUNT 20

// Function to print binary tree in 2D
// It does reverse inorder traversal
template <typename T>
void print2DUtil(T* root, int space)
{
    // Base case
    if (root == NULL){
        std::cout << std::endl;
        return;
    }

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";

    if ( root != (T*)neel )
    {
       if constexpr( std::is_same<T, IntervalTreeNode>::value )
          std::cout << "[" << root->key << ",](" << root->max << "," << root->min << ")" << std::endl;
    }

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
template <typename T>
void print2D( T* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}



void ReadRectangularTable( char const *fileName, UINT numRectangles, UINT *EventListX, UINT *EventListY )
{

  std::ifstream inputFile;
  inputFile.open( fileName, std::fstream::in );
  if (!inputFile.is_open()) REPORT_ERROR;

  for( UINT i=0; i<numRectangles*2; i += 2 )
    inputFile >> EventListX[i] >> EventListX[i+1] >> EventListY[i] >> EventListY[i+1];

  inputFile.close();

}


template <typename T>
bool checkIntOverflow( T a, T b, char operation )
{
  bool overflow = false;

  if (operation == '+')
  {
     if constexpr( std::is_same<T, INT>::value ){
        if ( ( b > (T)0 ) && ( a > (T)__INT_MAX-b ) ) overflow = true;
        if ( ( b < (T)0 ) && ( a < (T)__INT_MIN-b ) ) overflow = true;
     }

  }
  else if (operation == '*')
  {
     if constexpr( std::is_same<T, UINT>::value ){
        if (  b != (T)0 && a > (T)__UINT_MAX / b  )    overflow = true;
        if (  b != (T)0 && a < (T)__UINT_MIN / b  )    overflow = true;
     }

  }
  else
  {
     printf("Unsupport operation!\n");
     REPORT_ERROR;
  }

  return overflow;
}


void printPolygonList( const std::list<Polygon>& polygonList ){

   for ( const Polygon& poly : polygonList ){
      for ( auto vertex = (poly.polygon)->vertices_begin(); vertex != (poly.polygon)->vertices_end(); ++vertex ){
         std::cout << " (" << vertex->x() << ", " <<vertex->y() << ")" << std::endl;
      }
   }

}

void printPolygon( const Polygon_2& polygon ){

   for ( auto vertex = polygon.vertices_begin(); vertex != polygon.vertices_end(); ++vertex ){
      std::cout << " (" << vertex->x() << ", " <<vertex->y() << ")" << std::endl;
   }

}


void FreePolygonArray( Polygon ***polygonArray, UINT numberPolygons ){

   for ( UINT i=0; i<numberPolygons; i++ ){
      delete (*polygonArray)[i]->polygon;
      delete (*polygonArray)[i];
   }

   delete[] *polygonArray;
}




template bool checkIntOverflow<UINT>( UINT, UINT, char );
template bool checkIntOverflow<INT>(  INT,  INT, char );
template bool isLeftChild<IntervalTreeNode>( IntervalTreeNode *node, char const *fileName, int line );
template bool isLeftChild<SubIntervalTreeNode>( SubIntervalTreeNode *node, char const *fileName, int line );
template IntervalTreeNode*    allocateTreeNode( IntervalTreeNode **parent, Interval *intervalY, bool color, int left_root_right );
template SubIntervalTreeNode* allocateTreeNode( SubIntervalTreeNode **parent, Interval *intervalY, bool color, int left_root_right );
template void printInorder( IntervalTreeNode *node );
template void printInorder( SubIntervalTreeNode *node );
template void InorderChecking( IntervalTreeNode *node );
template void InorderChecking( SubIntervalTreeNode *node );
template UINT FindMaxInTree( IntervalTreeNode *node );
template UINT FindMaxInTree( SubIntervalTreeNode *node );
template IntervalTreeNode*    inorderSuccessor( IntervalTreeNode *node );
template SubIntervalTreeNode* inorderSuccessor( SubIntervalTreeNode *node );
template void CountOverlappingInterval( IntervalTreeNode    *current, Interval *intervalY, Polygon *polygon, UINT *RectangularCounter, UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter );
template void CountOverlappingInterval( SubIntervalTreeNode *current, Interval *intervalY, Polygon *polygon, UINT *RectangularCounter, UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter );
template void SearchTreeNode( IntervalTreeNode *root, UINT key, IntervalTreeNode** node );
template void SearchTreeNode( SubIntervalTreeNode *root, UINT key, SubIntervalTreeNode** node );
template void print2DUtil(IntervalTreeNode* root, int space);
template void print2DUtil(SubIntervalTreeNode* root, int space);
template void print2D( IntervalTreeNode* root);
template void print2D( SubIntervalTreeNode* root);
template void SwapReference( Polygon& poly1, Polygon& poly2 );
