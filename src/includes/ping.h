#pragma once

#include "../../Lib/src/includes.h"
#include "stdio.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <sys/time.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <math.h>

#define PACKET_SIZE 58
#define MSG_BUFFER_SIZE 1024

#define FLAGS_NB 2
#define FLAG_VERBOSE 0
#define FLAG_FLOOD 1

struct mac_header{
    uint8_t dst_mac[6];
    uint8_t src_mac[6];
    uint16_t type;
};

struct ip_header{
	uint8_t version:4;
	uint8_t ihl:4;
	uint8_t service;
	uint16_t len;
	uint16_t id;
	uint16_t flags:3;
	uint16_t frag_offset:13;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t checksum;
	uint32_t src_ip;
	uint32_t dst_ip;
};


struct icmp_header {
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t seq;
};

struct ip_header getIpv4Header(char * buffer);
struct icmp_header getIcmpHeader(char * buffer);
void startClock();
void stopClock(size_t *finalTimer);
size_t getClock();
void resetClock();
void sigHandler(int sig_num);
struct icmp_header initIcmpHeader(uint8_t type);
struct msghdr initMsgHeader(char (*buffer)[MSG_BUFFER_SIZE]);

void ipv4ToString(uint32_t ip, char *dest);
unsigned short get_checksum(unsigned short *data, size_t length);
void increaseSequence(struct icmp_header *header);
int socket_error(int errcode);

char *findArg(char **argv, char *arg);
char *findHost(char **argv);

short *doRun();
