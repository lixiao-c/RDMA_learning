#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>


typedef struct _timer {
    struct timeval t1;
    struct timeval t2;
    struct timeval diff;
    struct timeval total;
}timer;

void inittimer(timer* cur_timer);
double duration(timer* cur_timer);
void start(timer* cur_timer);
void end(timer* cur_timer);
void reset(timer* cur_timer);


#define CPU_FREQUENCY 2.2 // 2.2 GHz

typedef struct _cpuCycleTimer{
  long long t1, t2, total;
  int count; 
}cpuCycleTimer;

void resetCpu(cpuCycleTimer* newtimer);
void initcpuCycleTimer(cpuCycleTimer* newtimer);
void startCpu(cpuCycleTimer* newtimer);
void endCpu(cpuCycleTimer* newtimer);
double durationCpu(cpuCycleTimer* newtimer);