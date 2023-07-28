#include "sys/time.h"
#include"global.h"


void Reset()
{
   Time = 0;
}

double GetValue()
{
   return Time*1.0e-6;
}

void Start()
{
   struct timeval tv;
   gettimeofday( &tv, NULL );
   Time   = tv.tv_sec*1000000 + tv.tv_usec;
}

void Stop()
{
   struct timeval tv;
   gettimeofday( &tv, NULL );
   Time   = tv.tv_sec*1000000 + tv.tv_usec - Time;
}
