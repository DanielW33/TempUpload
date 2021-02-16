#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "check.h"
//Modified:
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>
//Finish Modified

int x[5] = {1,2,3,4,5};

void allocate()
{
    //Modified code area:
    printf("Allocate\n");
    struct timeval start, end, UStart, UEnd;
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    long int MRSS; 
    start = usage.ru_stime;
    UStart = usage.ru_utime;
    //End modified code

    int i;
    int *p;
    for(i =1 ; i<1000000 ; i++)
    {
      p = malloc(500 * sizeof(int));
      if(func(i)) { free (p);}
    }

    
    //Modified Code Below:
    long int Signals = usage.ru_nsignals;
    long int IVContext = usage.ru_nivcsw;
    long int VContext = usage.ru_nvcsw;
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_stime;
    MRSS = usage.ru_maxrss;
    UEnd = usage.ru_utime;
    //long int Signals = usage.ru_nsignals;
    printf("System\n");
    printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
    printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
    printf("User\n");
    printf("Started at %ld.%lds\n", UStart.tv_sec, UStart.tv_usec);
    printf("Ended at %ld.%lds\n", UEnd.tv_sec, UEnd.tv_usec);
    printf("Maximum resident set size: %ld\n", MRSS);
    printf("Signals received: %ld\n",Signals); 
    printf("Involuntary Context Switch: %ld\n", IVContext);
    printf("Voluntary Context Switch: %ld\n", VContext);
}

void allocate1()
{
  //Modified Code begins:
  printf("Allocate1");
  struct timeval start, end;
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  start = usage.ru_stime;
  //End Modified Code
  
  int i;
  int *p;
  for (i=1 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    if(i & 1)
      free (p);
  }
  
  //Begin Modified Code: 
  getrusage(RUSAGE_SELF, &usage);
  end = usage.ru_stime;
  printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
  printf("Ended at: %ls.%lds\n", end.tv_sec, end.tv_usec);

}

void allocate2()
{
  //Modified code begins:
  printf("Allocate2");
  struct timeval start, end;
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  start = usage.ru_stime;
  //End Modified Code
 
  int i;
  int *p;
  for (i=1 ; i<300000 ; i++)
  {
    p = malloc(10000 * sizeof(int));
    free (p);
  }

  //Begin Modified Code
  getrusage(RUSAGE_SELF, &usage);
  long int MRSS = usage.ru_maxrss;
  end = usage.ru_stime;
  printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
  printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
  printf("Maximum resident set size: %ld\n",MRSS);
}


int main(int argc, char const *argv[]) {
  //Modified code begins:
  struct timeval start, end, UStart, UEnd;
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  start = usage.ru_stime;
  UStart = usage.ru_utime;
  //End Modified Code

  int i;
  int *p;
  printf("Executing the code ......\n");
  allocate();

  for (i=0 ; i<10000 ; i++)
  {
    p = malloc(1000 * sizeof(int));
    free (p);
  }

  //Begin Modified Code
  long int Signals = usage.ru_nsignals;
  long int VContext = usage.ru_nvcsw;
  long int IVContext = usage.ru_nivcsw;
  getrusage(RUSAGE_SELF, &usage);
  long int MRSS = usage.ru_maxrss;
  //long int Signals = usage.ru_nsignals;
  end = usage.ru_stime;
  UEnd = usage.ru_utime;
  printf("Main\n");
  printf("System\n");
  printf("Started at: %ld.%lds\n", start.tv_sec, start.tv_usec);
  printf("Ended at: %ld.%lds\n", end.tv_sec, end.tv_usec);
  printf("User\n");
  printf("Started at: %ld.%lds\n", UStart.tv_sec, UStart.tv_usec);
  printf("Ended at: %ld.%lds\n",UEnd.tv_sec, UEnd.tv_usec);
  printf("Maximum resident set size: %ld\n", MRSS);
  printf("Signals received: %ld\n", Signals);
  printf("Involuntary Context Switch: %ld\n",IVContext);
  printf("Voluntary Context Switch: %ld\n", VContext); 

  printf("Program execution successfull\n");
  return 0;
}
