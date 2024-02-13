#include "includes/ping.h"

struct ip_header getIpv4Header(char * buffer){
	struct ip_header *header = (struct ip_header *)buffer;
	return *header;
}

struct icmp_header getIcmpHeader(char * buffer){
	struct icmp_header *header = (struct icmp_header *)(buffer + sizeof(struct ip_header));
	return *header;
}

char *initIcmpHeader(uint8_t type, size_t dataSize){
	char *data;
	char *buffer;
	struct icmp_header header;

	data = malloc(dataSize * sizeof(char));
	buffer = malloc((sizeof(struct icmp_header) + dataSize) * sizeof(char));

	ft_memset(data, 1, dataSize);

	struct icmp_header tmp;

	tmp.type = type;
	tmp.code = 0;
	tmp.checksum = 0;
	tmp.id = getpid();
	tmp.seq = 0;
	tmp.checksum = 0;

	ft_memcpy(buffer, &tmp, sizeof(tmp));
	ft_memcpy(buffer + sizeof(tmp), data, dataSize);


	header.type = type;
	header.code = 0;
	header.checksum = 0;
	header.id = getpid();
	header.seq = 0;
	header.checksum = get_checksum((unsigned short *)buffer, sizeof(struct icmp_header) + dataSize);

	ft_memcpy(buffer, &header, sizeof(header));
	ft_memcpy(buffer + sizeof(header), data, dataSize);

	free(data);

	return (buffer);
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