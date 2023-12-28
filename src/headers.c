#include "includes/ping.h"

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


struct msghdr initMsgHeader(char (*buffer)[MSG_BUFFER_SIZE])
{
	struct msghdr header;

	header.msg_name = NULL;
	header.msg_namelen = 0;
	header.msg_iovlen = 1;
	header.msg_control = NULL;
	header.msg_controllen = 0;

	struct iovec iov[1];
	iov[0].iov_base = *buffer;
	iov[0].iov_len = sizeof(*buffer);
	header.msg_iov = &iov[0];
	return (header);
}