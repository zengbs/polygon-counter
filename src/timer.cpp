#include <stdlib.h>
#include <sys/time.h>




double GetValue( unsigned long *Time )
{
   return (*Time)*1.0e-6;
}

void Start( unsigned long *Time )
{
   struct timeval tv;
   gettimeofday( &tv, NULL );
   *Time   = tv.tv_sec*1000000 + tv.tv_usec;
}

void Stop( unsigned long *Time )
{
   struct timeval tv;
   gettimeofday( &tv, NULL );
   *Time   = tv.tv_sec*1000000 + tv.tv_usec - *Time;
}
