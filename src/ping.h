#pragma once

#include "../lib/includes/libft.h"
#include "stdio.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>

void startClock();
void stopClock(size_t *finalTimer);
size_t getClock();