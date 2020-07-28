#include "timer.h"

void inittimer(timer* cur_timer) {
    cur_timer->total.tv_sec = cur_timer->total.tv_usec = 0;
    cur_timer->diff.tv_sec = cur_timer->diff.tv_usec = 0;
}

double duration(timer* cur_timer) {
    double duration;

    duration = (cur_timer->total.tv_sec) * 1000000.0;      // sec to us
    duration += (cur_timer->total.tv_usec);      // us

    return duration*1000.0;  //ns
}

void start(timer* cur_timer) {
    gettimeofday(&(cur_timer->t1), NULL);
}

void end(timer* cur_timer) {
    gettimeofday(&(cur_timer->t2), NULL);
    timersub(&cur_timer->t2, &cur_timer->t1, &cur_timer->diff);
    timeradd(&cur_timer->diff, &cur_timer->total, &cur_timer->total);
}

void reset(timer* cur_timer){
    cur_timer->total.tv_sec = cur_timer->total.tv_usec = 0;
    cur_timer->diff.tv_sec = cur_timer->diff.tv_usec = 0;
}

static __always_inline uint64_t rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64_t)hi << 32) | lo;
}

void resetCpu(cpuCycleTimer* newtimer){
    newtimer->count=0;
    newtimer->t1=0;
    newtimer->t2=0;
    newtimer->total=0;
}
void initcpuCycleTimer(cpuCycleTimer* newtimer){
    newtimer->count = 0;
    resetCpu(newtimer);
}
void startCpu(cpuCycleTimer* newtimer){
    newtimer->t1 = rdtsc();
}
void endCpu(cpuCycleTimer* newtimer){
    newtimer->t2 = rdtsc();
    newtimer->total += newtimer->t2 - newtimer->t1;
    newtimer->count++;
}
double durationCpu(cpuCycleTimer* newtimer){ // ns
    return newtimer->total/CPU_FREQUENCY;
}
