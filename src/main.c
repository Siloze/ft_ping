#include "ping.h"

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


void printIpAddress(struct ip_header *ip){
struct in_addr src_addr, dest_addr;

	src_addr.s_addr = ip->src_ip;
	dest_addr.s_addr = ip->dst_ip;

	char src_ip[INET_ADDRSTRLEN];
	char dest_ip[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &src_addr, src_ip, INET_ADDRSTRLEN);
	inet_ntop(AF_INET, &dest_addr, dest_ip, INET_ADDRSTRLEN);

	printf("src ip : %s\n", src_ip);
	printf("dest ip : %s\n", dest_ip);
}

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

struct msghdr initMsgHeader()
{
	struct msghdr header;

	header.msg_name = NULL;
	header.msg_namelen = 0;
	header.msg_iovlen = 1;
	header.msg_control = NULL;
	header.msg_controllen = 0;
	return (header);
}

struct ip_header getIpv4Header(char * buffer){
	struct ip_header *header = (struct ip_header *)buffer;
	return *header;
}

struct icmp_header getIcmpHeader(char * buffer){
	struct icmp_header *header = (struct icmp_header *)(buffer + sizeof(struct ip_header));
	return *header;
}

struct icmp_header initIcmpHeader(uint8_t type){
	struct icmp_header header;

	header.type = type;
	header.code = 0;
	header.checksum = 0;
	header.id = getpid();
	header.seq = 0;
	header.checksum = get_checksum((unsigned short *)&header, sizeof(header));

	return (header);
}

void increaseSequence(struct icmp_header *header)
{
	header->seq++;
	header->checksum = 0;
	header->checksum = get_checksum((unsigned short *)header, sizeof(*header));
}


int main (int argc, char **argv){
	if (argc < 2)
		return (0);

	//-------------SOCKET INIT-----------
	int icmp_socket;
	size_t receivTime;
	char buffer[1024];
	struct addrinfo *dest;
	struct msghdr receiveHeader;
	struct icmp_header sendImcp_header;

	icmp_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (icmp_socket < 0)
		return (fprintf(stderr, "socket error\n"));
	

	if (getaddrinfo(argv[1], NULL, NULL, &dest) != 0)
		return (fprintf(stderr, "getaddrinfo error\n"));

	sendImcp_header = initIcmpHeader(ICMP_ECHO);
	receiveHeader = initMsgHeader();

	struct iovec iov[1];
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	receiveHeader.msg_iov = &iov[0];

	while (1)
	{

		if (sendto(icmp_socket, &sendImcp_header, sizeof(sendImcp_header), 0, dest->ai_addr, dest->ai_addrlen) < 0)
			return (fprintf(stderr, "sendto error\n"));
	
		startClock();
		size_t receivSize = recvmsg(icmp_socket, &receiveHeader, sizeof(buffer));
		stopClock(&receivTime);

		usleep((1000 - receivSize) * 1000);

		struct ip_header ip = getIpv4Header(buffer);
		struct icmp_header icmphdr = getIcmpHeader(buffer);

		char ipv4[INET_ADDRSTRLEN];

		ipv4ToString(ip.src_ip, ipv4),
		
		increaseSequence(&sendImcp_header);
	
		ft_memset(&buffer, 0, 1024);
	
		printf("Ping response | bites=%zu from='%s' icmp_seq=%d time=%zums\n", receivSize, ipv4, icmphdr.seq, receivTime);
	}

	//---------------GETTING INFOS----------------

	// if (icmp_header->type == ICMP_ECHOREPLY && icmp_header->code == 0) //IS RESPONSE IS ECHO RETURN
	// {
	
	// }


	freeaddrinfo(dest);


	return (1);
}
