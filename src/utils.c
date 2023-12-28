#include "includes/ping.h"

void ipv4ToString(uint32_t ip, char *dest){
	struct in_addr src_addr;

	src_addr.s_addr = ip;
	inet_ntop(AF_INET, &src_addr, dest, INET_ADDRSTRLEN);
}

unsigned short get_checksum(unsigned short *data, size_t length){
    unsigned long sum = 0;
    while (length > 1) {
        sum += *data++;
        length -= 2;
    }
    if (length > 0) {
        sum += *(unsigned char *)data;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

void increaseSequence(struct icmp_header *header)
{
	header->seq++;
	header->checksum = 0;
	header->checksum = get_checksum((unsigned short *)header, sizeof(*header));
}

int socket_error(int errcode){
	if (errcode == 1)
		return (printf("Can't open socket, please sure to have the right\n"));
	return (0);
}

char *findArg(char **argv, char *arg){
	int i = -1;

	while (argv[++i])
		if (!ft_strcmp(argv[i], arg))
			return (argv[i]);
	return (0);
}

char *findHost(char **argv){
	int i = -1;

	while (argv[++i])
		if (argv[i][0] != '-')
			return (argv[i]);
	return (0);
}
