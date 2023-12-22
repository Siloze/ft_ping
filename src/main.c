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

void printOutput(int bytesSend, int bytesReceiv, int time, char *buffer, int seq){

	char ipv4[INET_ADDRSTRLEN];
	struct ip_header ip = getIpv4Header(buffer);
	struct icmp_header icmphdr = getIcmpHeader(buffer);

	if (bytesReceiv == 0 || (bytesReceiv < 0 && ( errno == EAGAIN || errno == 60)))
		printf("Ping timeout | ");
	else if (bytesReceiv < 0)
		printf("Ping error %d | ", errno);
	else if (!(icmphdr.type == ICMP_ECHOREPLY && icmphdr.code == 0))
		printf("bad icmp response | ");
	else
	{
		ipv4ToString(ip.src_ip, ipv4);
		printf("ttl=%d | Ping response from: '%s' | bytes=%lu ", ip.ttl, ipv4, bytesSend + sizeof(struct ip_header));
	}
	printf("seq=%d time=%dms\n", seq, time);

}

short loopNext(int size ,char *buffer, char *ip, int seq){

	if (size == -1 && errno == EAGAIN) //no response
		return 1;

	char ipv4[INET_ADDRSTRLEN];

	ipv4ToString(getIpv4Header(buffer).src_ip, ipv4);
	if (getIcmpHeader(buffer).seq != seq) // is response is not for this seq
		return 1;
	if (size > 0 && strcmp(ip, ipv4)) // is response is not from the good ip
		return 1;
	return 0;
}

int loop(int socket, char *ipv4, struct addrinfo dest){

	char buffer[1024];
	struct msghdr receiveHeader;
	struct icmp_header sendImcp_header;

	receiveHeader = initMsgHeader();
	sendImcp_header = initIcmpHeader(ICMP_ECHO);

	struct iovec iov[1];
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	receiveHeader.msg_iov = &iov[0];

	while (1)
	{
		int bytesSend = 0;
		int bytesReceiv = 0;
		size_t receivTime = 0;
		startClock();

		ft_memset(&buffer, 0, 1024);
		bytesSend = sendto(socket, &sendImcp_header, sizeof(sendImcp_header), 0, dest.ai_addr, dest.ai_addrlen);
		if (bytesSend < 0)
			return (fprintf(stderr, "sendto error\n"));

		while (getClock() < 1000)
		{
			bytesReceiv = recvmsg(socket, &receiveHeader, MSG_DONTWAIT);
			if (!loopNext(bytesReceiv, buffer, ipv4, sendImcp_header.seq))
				break;;
		}
		stopClock(&receivTime);

		usleep((800 - receivTime) * 1000);

		printOutput(bytesSend, bytesReceiv, receivTime, buffer, sendImcp_header.seq);

		increaseSequence(&sendImcp_header);
	}
	return 0;
}

int main (int argc, char **argv){

	if (argc < 2)
		return (0);
	//-------------SOCKET INIT-----------
	int icmp_socket;
	struct addrinfo *dest;

	icmp_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
		if (icmp_socket < 0)
		return (fprintf(stderr, "socket error\n"));
	
	if (getaddrinfo(argv[1], NULL, NULL, &dest) != 0)
		return (fprintf(stderr, "getaddrinfo error\n"));

	// freeaddrinfo(dest);
	loop(icmp_socket, argv[1], *dest);

	return (1);
}
