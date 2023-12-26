#include "ping.h"

short *doRun(){
	static short run = 1;

	return &run;
}

int checkInput(char **argv){
	int i = 0;
	int j = 0;

	while (argv[i])
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int checkResponse(int bytesReceiv, int ttl, char *buffer, size_t *flags){

	struct icmp_header icmp = getIcmpHeader(buffer);

	if (buffer[0] && (flags[FLAG_VERBOSE] || (icmp.type == ICMP_ECHOREPLY && icmp.code == 0)))
		return 0;
	if (bytesReceiv == 0 || (bytesReceiv < 0 && ( errno == EAGAIN || errno == 60)))
		return 1;
	if (ttl == 0 || getIpv4Header(buffer).ttl != ttl)
		return 2;
	return 3;
}

short loopNext(int size ,char *buffer, char *ip, int seq){

	if (size == -1 && errno == EAGAIN ) //no response
		return 1;

	char ipv4[INET_ADDRSTRLEN];
	ipv4ToString(getIpv4Header(buffer).src_ip, ipv4);
	if (getIcmpHeader(buffer).seq != seq) // is response is not for this seq
		return 1;
	if (size > 0 && strcmp(ip, ipv4)) // is response is not from the good ip
		return 1;
	return 0;
}

int launchPing(int socket, struct addrinfo dest, size_t *flags){

	int ttl = 0;
	char ipv4[INET_ADDRSTRLEN];
	struct msghdr receiveHeader;
	char buffer[MSG_BUFFER_SIZE];
	struct icmp_header sendImcp_header;

	char packet[sizeof (struct icmp_header)];
	int packetStat[2] = {0, 0};

	receiveHeader = initMsgHeader(&buffer);
	sendImcp_header = initIcmpHeader(ICMP_ECHO);
	memset(&packet, 1, sizeof(packet));

	ipv4ToString(((struct sockaddr_in *)dest.ai_addr)->sin_addr.s_addr, ipv4);

	struct iovec iov[1];
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	receiveHeader.msg_iov = &iov[0];

	printf("FT_PING: %s: %lu data bytes\n", ipv4, sizeof(packet) + sizeof(struct ip_header) + sizeof(struct mac_header));

	doRun();
	while (*doRun())
	{
		int bytes[2] = {0, 0};
		size_t receivTime = 0;

		ft_memset(&buffer, 0, MSG_BUFFER_SIZE);
		memcpy(&packet, &sendImcp_header, sizeof(sendImcp_header));


		//-----------PAQUET SEND---------
		startClock();
		bytes[0] = sendto(socket, packet, sizeof(packet), 0, dest.ai_addr, dest.ai_addrlen);
		if (bytes[0] < 0)
			return (fprintf(stderr, "sendto error\n"));
		if (flags[FLAG_FLOOD])
			printf(".");

		while (getClock() < 1000)
		{
			bytes[1] = recvmsg(socket, &receiveHeader, MSG_DONTWAIT);
			if (!loopNext(bytes[1], buffer, ipv4, sendImcp_header.seq))
				break;
		}
		stopClock(&receivTime);

		if (!flags[FLAG_FLOOD])
			usleep((1000 - receivTime) * 1000);

		if (!ttl)
			ttl = getIpv4Header(buffer).ttl;

		packetStat[0]++;

		switch (checkResponse(bytes[1], ttl, buffer, flags))
		{
		case 0:
			if (!flags[FLAG_FLOOD])
				printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%zums\n", sizeof(packet) + sizeof(struct ip_header) + sizeof(struct mac_header), ipv4, sendImcp_header.seq, getIpv4Header(buffer).ttl, receivTime);
			else
				printf("\b");
			packetStat[1]++;
			break;
		case 1:
			printf("Request timeout for icmp_seq %d\n", sendImcp_header.seq);
			if (flags[FLAG_VERBOSE])
				sigHandler(0);
			break;
		case 2:
			printf("TTL expired in transit for icmp_seq %d\n", sendImcp_header.seq);
			if (flags[FLAG_VERBOSE])
				sigHandler(0);
			break;
		default:
			printf("Request error for icmp_seq %d\n", sendImcp_header.seq);
			if (flags[FLAG_VERBOSE])
				sigHandler(0);
			break;
		}

		increaseSequence(&sendImcp_header);

	}

    printf("\n--- %s ft_ping statistics ---\n", ipv4);
    printf("%d packets transmitted, %d received, %d%% packet loss\n", packetStat[0], packetStat[1], (packetStat[0] - packetStat[1]) * 100 / packetStat[0]);

	return 0;
}

size_t *initFlags(char **argv){
	size_t *flags = malloc(sizeof(size_t) * FLAGS_NB);

	flags[FLAG_VERBOSE] = findArg(argv, "-v") ? 1 : 0;
	flags[FLAG_FLOOD] = findArg(argv, "-f") ? 1 : 0;

	return (flags);
}

int main (int argc, char **argv){
	size_t *flags;
	int icmp_socket;
	struct addrinfo *dest;

	flags = initFlags(&argv[1]);

	if (argc < 2)
		return (0);
	if (!checkInput(&argv[1]))
		return(printf("Bad input: ping [-v | -f] <ip/hostname>\n"));
	if (argc > 2 && !memchr(flags, 1, sizeof(size_t) * FLAGS_NB))
		return (printf("Bad flag: [-v | -f]\n"));
	
	signal(SIGINT, sigHandler);

	icmp_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (icmp_socket < 0)
		return (socket_error(errno));
	
	if (getaddrinfo(findHost(&argv[1]), NULL, NULL, &dest) != 0) //get All adresse by hostname & ip
		return (fprintf(stderr, "getaddrinfo error\n"));


	 for (struct addrinfo *rp = dest; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) { // IPv4
			launchPing(icmp_socket, *rp, flags);
			freeaddrinfo(dest);
			return (0);
        }
    }

	return (1);
}
