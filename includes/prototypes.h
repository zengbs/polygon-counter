#ifndef __PROTOTYPES_H__
#define __PROTOTYPES_H__



bool operator==(const Polygon& lhs, const Polygon& rhs);
template <typename T> bool checkIntOverflow( T a, T b, char operation );
template <typename T> void rightRotate( T *x, T **root );
template <typename T> void leftRotate ( T *x, T **root );
template <typename T> void SwapReference( T& a, T& b );
template <typename T> void InsertTreeNode( T **root, Interval *intervalY, Polygon* polygon, IntervalTreeNode *SubIntervalTreeRootParent );
template <typename T> void DeleteTreeNode( T **root, Interval *interval, Polygon* polygon );
template <typename T> bool isLeftChild( T *node, char const *fileName, int line );
template <typename T> T* allocateTreeNode( T **parent, Interval *intervalY, bool color, int left_root_right);
template <typename T> void printInorder( T *node );
template <typename T> void InorderChecking( T *node );
template <typename T> UINT FindMaxInTree( T *node );
template <typename T> T* inorderSuccessor( T *node );
template <typename T> void CountOverlappingInterval( T *current, Interval *intervalY, Polygon *polygon, UINT *RectangularCounter, UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter );
template <typename T> void SearchTreeNode( T *root, UINT key, T** node );
template <typename T> bool validateBST(T* node, T* prev);
template <typename T> bool isValidBST(T* root);
template <typename T> bool isBalancedUtil(T *root, UINT *maxh, UINT *minh);
template <typename T> bool isBalanced(T *root);
template <typename T> void print2D( T* root);
template <typename T> void print2DUtil(T* root, int space);
void CountIntervalInNode( SubIntervalTreeNode *treeNode, Interval *intervalY, Polygon *testPolygon, UINT *numberCounted, UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter );
bool IsOverlappingIntervals( Interval *interval1, Interval *interval2 );
bool IsTouchingIntervals( Interval *interval1, Interval *interval2 );
void SweepLine( IntervalTreeNode **root, Polygon **polygonArray,
                UINT *EventListX, UINT *EventListY, UINT numRectangles,
                UINT *RectangularCounter, UINT *TouchingCounter, UINT *IntersectedCounter, UINT *DuplicateCounter );
void SwapPointer( void **ptr1, void **ptr2 );
UINT max( UINT a, UINT b, UINT c );
UINT min( UINT a, UINT b, UINT c );
void RectanglesGeneration(
UINT numberRectangles,
UINT boxSizeX, UINT boxSizeY,
UINT rectangularMaxSizeX, UINT rectangularMaxSizeY,
UINT rectangularMinSizeX, UINT rectangularMinSizeY,
UINT rectangleArea,
UINT **EventListX, UINT **EventListY );
void NaiveCountOverlappingRectangles( UINT *EventListX, UINT *EventListY, UINT numRectangles, UINT *counter );
void XorSwap(UINT *x, UINT *y);
void SegregateEvenAndOdd( EventListX_wrapper *wrapper, UINT numRectangles );
void Reset();
double GetValue( unsigned long *Time );
void Stop( unsigned long *Time );
void Start( unsigned long *Time );
void Pixelization( UINT numRectangles, UINT boxSizeX, UINT boxSizeY, UINT *EventListX, UINT *EventListY, UINT *counter );
void ReadRectangularTable( char const *fileName, UINT numRectangles, UINT *EventListX, UINT *EventListY );
void GenerateEventLists( int boxSizeX, int boxSizeY, UINT inputNumberObject,
                         UINT **EventListX, UINT **EventListY, UINT *DuplicateCounter,
                         Polygon ***polygonArray, Polygon ***polygonFullArray );
void NaiveCheckIntersection( Polygon **polygonArray, UINT numberObjects, UINT *IntersectedCounter,
                             UINT *TouchingCounter, UINT *DuplicateCounter, UINT *DisjointCounter );
void detached_or_touching_or_intersection( Polygon_2& poly1, Polygon_2& poly2, int *detachedOrTouchingOrIntersect );
UINT randomNumberInRange( UINT minimum_number, UINT max_number );
void printPolygonList( const std::list<Polygon>& polygonList );
void printPolygon( const Polygon_2& polygon );
void FreePolygonArray( Polygon ***polygonArray, UINT numberPolygons );
#endif
