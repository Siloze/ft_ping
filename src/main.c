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
			if (!isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int getStackSize(int *stack, int stopNumber){
	int i = -1;

	while (stack[++i] != stopNumber && stack[i])
		;
	return (i + 1);
}

int checkResponse(int bytesReceiv, int ttl, char *buffer, size_t *flags){

	struct icmp_header icmp = getIcmpHeader(buffer);

	if (bytesReceiv == 0 || (bytesReceiv < 0 && ( errno == EAGAIN || errno == 60)))
		return 1;
	if (buffer[0] && (flags[FLAG_VERBOSE] || (icmp.type == ICMP_ECHOREPLY && icmp.code == 0)))
		return 0;
	if (ttl == 0 || getIpv4Header(buffer).ttl != ttl)
		return 2;
	return 3;
}

short retry(int size ,char *buffer, char *ip, int seq){

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

void printHeader(char *ip, size_t *flags, int fd, struct addrinfo *ai){

	if (flags[FLAG_VERBOSE])
	{
		printf("FT_PING: sock4.fd: %d (socktype: SOCK_RAW), hints.ai_family: AF_UNSPEC\n\nai->ai_family: ", fd);
		printf("%s", ai->ai_family == AF_INET ? "AF_INET" : "AF_INET6");
		printf(", ai->canonname: %s\n", ai->ai_canonname);
	}

	printf("FT_PING: %s: %lu data bytes\n", ip, sizeof(struct icmp_header) + sizeof(struct ip_header) + sizeof(struct mac_header));
}

void printResponse(int *bytes, int ttl, char *buffer, char *ipv4, struct icmp_header sendImcp_header, size_t *flags, int *packetStat, size_t receivTime){
		switch (checkResponse(bytes[1], ttl, buffer, flags))
		{
		case 0:
			printf("%lu bytes from %s: icmp_seq=%d ttl=%d time=%zums\n", sizeof(struct icmp_header) + sizeof(struct ip_header) + sizeof(struct mac_header), ipv4, sendImcp_header.seq, getIpv4Header(buffer).ttl, receivTime);
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
			if (flags[FLAG_VERBOSE] && !flags[FLAG_FLOOD])
				sigHandler(0);
			break;
		}
}

void increaseStack(int *stack, int value){
	stack = realloc(stack, sizeof(int) * getStackSize(stack, -1) + 1);
	stack[getStackSize(stack, -1) - 1] = value;
	stack[getStackSize(stack, -1)] = -1;
}

size_t loop(int *receivBytes, struct msghdr *receiveHeader, char *buffer, char *ipv4, struct icmp_header sendImcp_header, int socket, int **msStack)
{
	size_t receivTime = 0;
	startClock();
	while (getClock() < 1000)
	{
		*receivBytes = recvmsg(socket, receiveHeader, MSG_DONTWAIT);
		if (!retry(*receivBytes, buffer, ipv4, sendImcp_header.seq))
		{
			*msStack = realloc(*msStack, sizeof(int) * getStackSize(*msStack, -1) + 1);
			msStack[0][getStackSize(*msStack, -1) - 1] = getClock();
			msStack[0][getStackSize(*msStack, -1)] = -1;
			// increaseStack(msStack, getClock());
			break;
		}
	}
	stopClock(&receivTime);
	usleep((1000 - receivTime) * 1000);
	return (receivTime);
}

void flood_loop(int *receiveBytes, int *packetReceiv, int socket, struct msghdr *receiveHeader, int **msStack)
{
	size_t time = 0;

	write(1, ".", 1);
	usleep(10000); // 10ms
	startClock();
	*receiveBytes = recvmsg(socket, receiveHeader, MSG_DONTWAIT);
	while (*receiveBytes > 0)
	{
		stopClock(&time);
		// increaseStack(&msStack, time);
		*msStack = realloc(*msStack, sizeof(int) * getStackSize(*msStack, -1) + 1);
		msStack[0][getStackSize(*msStack, -1) - 1] = getClock();
		msStack[0][getStackSize(*msStack, -1)] = -1;
		write(1, "\b \b", 3);
		*packetReceiv += 1;
		*receiveBytes = recvmsg(socket, receiveHeader, MSG_DONTWAIT);
		startClock();
	}
	resetClock();
}

float getStandartDeviation(int *msStack){
	(void)msStack;
	return (1);
	// int averrage = 0;
	// int i = -1;
	// int size = getStackSize(msStack, -1);
	// float standartDeviation = 0;

	// while (msStack[++i] != -1)
	// 	averrage += msStack[i];
	// averrage /= size;
	// i = -1;
	// while (msStack[++i] != -1)
	// 	standartDeviation += pow(msStack[i] - averrage, 2);
	// standartDeviation /= size;
	// return (sqrt(standartDeviation));
}

void printStat(int *packetStat, int *msStack, char *ipv4){
	int averrage = 0;
	int max = 0;
	int min = 99999;

	for (int i = 0; i < getStackSize(msStack, -1) - 1; i++) {
		averrage += msStack[i];
		if (min > msStack[i])
			min = msStack[i];
		if (max < msStack[i])
			max = msStack[i];
	}
	averrage /= getStackSize(msStack, -1);
	printf("\n--- %s ft_ping statistics ---\n", ipv4);
    printf("%d packets transmitted, %d received, %d%% packet loss\n", packetStat[0], packetStat[1], (packetStat[0] - packetStat[1]) * 100 / packetStat[0]);

	if (getStackSize(msStack, -1)){
		printf("rtt min/avg/max/stddev = %d/%d/%d/%d ms\n", min, averrage, max, (int)getStandartDeviation(msStack));
	}
}

int launchPing(int socket, struct addrinfo dest, size_t *flags){

	int ttl = 0;
	char ipv4[INET_ADDRSTRLEN];
	struct msghdr receiveHeader;
	char buffer[MSG_BUFFER_SIZE];
	struct icmp_header sendImcp_header;

	int *msStack = malloc(sizeof(int) * 1);
	int packetStat[2] = {0, 0};
	char packet[sizeof (struct icmp_header)];
	msStack[0] = -1;

	receiveHeader = initMsgHeader(&buffer);
	sendImcp_header = initIcmpHeader(ICMP_ECHO);
	memset(&packet, 1, sizeof(packet));

	ipv4ToString(((struct sockaddr_in *)dest.ai_addr)->sin_addr.s_addr, ipv4);

	struct iovec iov[1];
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	receiveHeader.msg_iov = &iov[0];

	printHeader(ipv4, flags, socket, &dest);

	doRun();
	while (*doRun())
	{
		int bytes[2] = {0, 0};
		size_t receivTime = 0;

		memset(&buffer, 0, MSG_BUFFER_SIZE);
		memcpy(&packet, &sendImcp_header, sizeof(sendImcp_header));

		//-----------PAQUET SEND---------
		bytes[0] = sendto(socket, packet, sizeof(packet), 0, dest.ai_addr, dest.ai_addrlen);
		if (bytes[0] < 0)
			return (fprintf(stderr, "sendto error\n"));

		if (flags[FLAG_FLOOD])
			flood_loop(&bytes[1], &packetStat[1], socket, &receiveHeader, &msStack);
		else
			receivTime = loop(&bytes[1], &receiveHeader, buffer, ipv4, sendImcp_header, socket, &msStack);
		if (!ttl)
			ttl = getIpv4Header(buffer).ttl;

		packetStat[0]++;

		if (!flags[FLAG_FLOOD])
			printResponse(bytes, ttl, buffer, ipv4, sendImcp_header, flags, packetStat, receivTime);
		increaseSequence(&sendImcp_header);

	}
	printStat(packetStat, msStack, ipv4);
	free(msStack);

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
			// rp->ai_canonname = findHost(&argv[1]);
			launchPing(icmp_socket, *rp, flags);
			freeaddrinfo(dest);
			return (0);
        }
    }

	return (1);
}
