#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../includes/typedef.h"
#include "../includes/global.h"

// Returns true if two rectangles (l1, r1) and (l2, r2)
// overlap
static bool Overlap(UINT *rec1, UINT *rec2 )
{

    // If one rectangle is on left side of other
    if ( rec1[0] > rec2[1] || rec1[1] < rec2[0] )
        return false;

    // If one rectangle is above other
    if ( rec1[2] > rec2[3] || rec1[3] < rec2[2] )
        return false;

    return true;
}


void NaiveCountOverlappingRectangles( UINT *EventListX, UINT *EventListY, UINT numRectangles, UINT *counter )
{
   UINT rec1[4] = {0};
   UINT rec2[4] = {0};

   bool *count = (bool*)calloc(numRectangles, sizeof(bool));
   if ( count == NULL ) REPORT_ERROR;


   for (UINT i=0; i<numRectangles*2; i += 2){
      rec1[0] = EventListX[i  ];
      rec1[1] = EventListX[i+1];
      rec1[2] = EventListY[i  ];
      rec1[3] = EventListY[i+1];

      for (UINT j=0; j<numRectangles*2; j += 2){
            if (i!=j){
               rec2[0] = EventListX[j  ];
               rec2[1] = EventListX[j+1];
               rec2[2] = EventListY[j  ];
               rec2[3] = EventListY[j+1];

               if ( Overlap(rec1, rec2) && count[i/2] == false ){
#                 ifdef DEBUG
                  printf("rec1[0]=%d, rec1[1]=%d, rec1[2]=%d, rec1[3]=%d\n", rec1[0], rec1[1], rec1[2], rec1[3]);
                  printf("rec2[0]=%d, rec2[1]=%d, rec2[2]=%d, rec2[3]=%d\n", rec2[0], rec2[1], rec2[2], rec2[3]);
#                 endif
                  (*counter)++;
                  count[i/2] = true;
               }
            }
      }

   }

   free(count);

}
