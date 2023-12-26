#include "ping.h"

void sigHandler(int sig_num)
{
    (void)sig_num;
    *doRun() = 0;
}