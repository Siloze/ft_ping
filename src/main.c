#include "../lib/src/includes.h"
#include "stdio.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int ft_ping(char **arg){
	struct in_addr ipv4;
	
	if (inet_pton(AF_INET, arg[0], &ipv4) != 1)
		return (printf("Invalid ip : %s\n", arg[0]));

	socket(PF_INET, SOCK_DGRAM, 1);
	return (1);
}

int testConnect(char **arg){

	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_flags = 0;
	hints.ai_protocol = 1; //ICMP
	
	int err = getaddrinfo(arg[0], NULL, &hints, &result);
	if (err != 0)
		return (printf("getaddrinfo: %s\n", gai_strerror(err)));
	
	for (struct addrinfo *rp = result; rp != NULL; rp = rp->ai_next){
		printf("a struct\n");
	}
	return (1);
}

int main (int argc, char **argv){
	if (argc < 2)
		return (0);
	return (testConnect(++argv));
}

