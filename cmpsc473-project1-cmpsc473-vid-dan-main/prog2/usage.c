#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdio.h>

int main(){
struct rusage usage;
struct timeval start, end;
int i, j , k = 0;

getrusage(RUSAGE_SELF, &usage);
start = usage.ru_stime;
for(i = 0; i < 100000; i++){
for(j = 0; j < 100000; j++){
k += 1;
}
}
getrusage(RUSAGE_SELF, &usage);
end = usage.ru_stime;

printf("Started at: %ld.%lds\n", start.tv sec, start.tv usec);
printf("Ended at: %ld.%lds\n", end.tv sec, end.tv usec);
return 0; 
}
