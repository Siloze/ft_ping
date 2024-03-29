#include "includes/ping.h"

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

int getStackSize(int *stack, int stopNumber){
	int i = -1;

	while (stack[++i] != stopNumber && stack[i])
		;
	return (i + 1);
}

short retry(int size ,char *buffer, char *ip, int seq){
	char ipv4[INET_ADDRSTRLEN];

	if (size == -1 && errno == EAGAIN ) //no response
		return 1;
	ipv4ToString(getIpv4Header(buffer).src_ip, ipv4);
	if (getIcmpHeader(buffer).seq != seq) // is response is not for this seq
		return 1;
	if (size > 0 && ft_strcmp(ip, ipv4)) // is response is not from the good ip
		return 1;
	return 0;
}

void printHeader(char *ip, size_t *flags){
	
	int id = getpid();
	printf("FT_PING: %s: %d data bytes", ip, PACKET_SIZE);
	if (flags[FLAG_VERBOSE])
		printf(", id 0x%.4x = %d\n", id, id);
	else
		printf("\n");
}

int checkResponse(int bytesReceiv, int ttl, char *buffer, size_t *flags){

	struct icmp_header icmp = getIcmpHeader(buffer);

	if (bytesReceiv == 0 || (bytesReceiv < 0 && ( errno == EAGAIN || errno == 60)))
		return 1;
	if (buffer[0] && (flags[FLAG_VERBOSE] || (icmp.type == ICMP_ECHOREPLY && icmp.code == 0)))
		return 0;
	if (icmp.type != ICMP_ECHOREPLY || icmp.code != 0)
		return 3;
	if (ttl == 0 || getIpv4Header(buffer).ttl != ttl)
		return 2;
	return 3;
}

void printResponse(int *bytes, int ttl, char *buffer, char *ipv4, struct icmp_header *sendImcp_header, size_t *flags, int *packetStat, size_t receivTime, char *hostname){
		switch (checkResponse(bytes[1], ttl, buffer, flags))
		{
		case 0:
			printf("%lu bytes from %s (%s): icmp_seq=%d ttl=%d time=%zums\n", bytes[1] - sizeof(struct icmp_header) - sizeof(struct mac_header), hostname, ipv4, sendImcp_header->seq, getIpv4Header(buffer).ttl, receivTime);
			packetStat[1]++;
			break;
		case 1:
			printf("Request timeout for icmp_seq %d\n", sendImcp_header->seq);
			if (flags[FLAG_VERBOSE])
				sigHandler(0);
			break;
		case 2:
			printf("TTL expired in transit for icmp_seq %d\n", sendImcp_header->seq);
			if (flags[FLAG_VERBOSE])
				sigHandler(0);
			break;
		case 3:
			printf("Bad response for icmp_seq %d\n", sendImcp_header->seq);
			if (flags[FLAG_VERBOSE])
				sigHandler(0);
			break;
		default:
			printf("Request error for icmp_seq %d\n", sendImcp_header->seq);
			if (flags[FLAG_VERBOSE] && !flags[FLAG_FLOOD])
				sigHandler(0);
			break;
		}
}

void increaseStack(int **stack, int value){
	int stackSize = getStackSize(*stack, -1);
	*stack = realloc(*stack, sizeof(int) * stackSize + 1);
	stack[0][stackSize - 1] = value;
	stack[0][stackSize] = -1;
}

size_t loop(int *receivBytes, struct msghdr *receiveHeader, char *buffer, char *ipv4, struct icmp_header *sendImcp_header, int socket, int **msStack)
{
	size_t receivTime = 0;
	startClock();
	while (getClock() < 1000)
	{
		*receivBytes = recvmsg(socket, receiveHeader, MSG_DONTWAIT);
		if (!retry(*receivBytes, buffer, ipv4, sendImcp_header->seq))
		{
			increaseStack(msStack, getClock());
			break;
		}
	}
	stopClock(&receivTime);
	for (int i = 0; i < 1000 && *doRun(); i += 1)
		usleep((1000 - receivTime));
	return (receivTime);
}

void flood_loop(int *packetReceiv, int socket, struct msghdr *receiveHeader, int **msStack)
{
	size_t time = 0;

	write(1, ".", 1);
	usleep(10000); // 10ms
	startClock();
	while (recvmsg(socket, receiveHeader, MSG_DONTWAIT) > 0)
	{
		usleep(10000); // 10ms
		stopClock(&time);
		increaseStack(msStack, time);
		write(1, "\b \b", 3);
		*packetReceiv += 1;
		startClock();
	}
	resetClock();
}

float getStandartDeviation(int *msStack){
	int averrage = 0;
	int i = -1;
	int size = getStackSize(msStack, -1);
	float standartDeviation = 0;

	while (msStack[++i] != -1)
		averrage += msStack[i];
	averrage /= size;
	i = -1;
	while (msStack[++i] != -1)
		standartDeviation += pow(msStack[i] - averrage, 2);
	standartDeviation /= size;
	return (sqrt(standartDeviation));
}

void printStat(int *packetStat, int *msStack, char *ipv4){
	int total = 0;
	int max = 0;
	int min = 99999;

	for (int i = 0; i < getStackSize(msStack, -1) - 1; i++) {
		total += msStack[i];
		if (min > msStack[i])
			min = msStack[i];
		if (max < msStack[i])
			max = msStack[i];
	}
	printf("\n--- %s ft_ping statistics ---\n", ipv4);
    printf("%d packets transmitted, %d received, %d%% packet loss\n", packetStat[0], packetStat[1], (packetStat[0] - packetStat[1]) * 100 / packetStat[0]);

	if (getStackSize(msStack, -1)){
		printf("rtt min/avg/max/stddev = %d/%d/%d/%d ms\n", min, total / getStackSize(msStack, -1), max, (int)getStandartDeviation(msStack));
	}
}

int launchPing(int socket, struct addrinfo dest, size_t *flags, char *hostname){

	int ttl = 0;
	char ipv4[INET_ADDRSTRLEN];
	struct msghdr receiveHeader;
	char buffer[MSG_BUFFER_SIZE];
	char *sendImcp_header;

	int *msStack = malloc(sizeof(int) * 1);
	int packetStat[2] = {0, 0};

	receiveHeader = initMsgHeader(&buffer);
	sendImcp_header = initIcmpHeader(ICMP_ECHO, PACKET_SIZE);

	ipv4ToString(((struct sockaddr_in *)dest.ai_addr)->sin_addr.s_addr, ipv4);

	struct iovec iov[1];
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);
	receiveHeader.msg_iov = &iov[0];

	msStack[0] = -1;

	doRun();
	while (*doRun())
	{
		ft_memset(&buffer, 0, MSG_BUFFER_SIZE);

		int bytes[2] = {0, 0};
		size_t receivTime = 0;

		bytes[0] = sendto(socket, sendImcp_header, sizeof(struct icmp_header) + PACKET_SIZE, 0, dest.ai_addr, dest.ai_addrlen);
		if (bytes[0] < 0)
		{
			perror("sendto: ");
			break;
		}

		if (flags[FLAG_FLOOD])
			flood_loop(&packetStat[1], socket, &receiveHeader, &msStack);
		else
			receivTime = loop(&bytes[1], &receiveHeader, buffer, ipv4, (struct icmp_header *)sendImcp_header, socket, &msStack);
		if (!ttl)
			ttl = getIpv4Header(buffer).ttl;

		packetStat[0]++;

		if (!flags[FLAG_FLOOD])
			printResponse(bytes, ttl, buffer, ipv4, (struct icmp_header *)sendImcp_header, flags, packetStat, receivTime, hostname);
		increaseSequence(&sendImcp_header);
	}
	printStat(packetStat, msStack, ipv4);
	free(msStack);
	free(sendImcp_header);

	return 0;
}

size_t *initFlags(char **argv){
	size_t *flags = malloc(sizeof(size_t) * FLAGS_NB);

	flags[FLAG_VERBOSE] = findArg(argv, "-v") ? 1 : 0;
	flags[FLAG_FLOOD] = findArg(argv, "-f") ? 1 : 0;
	flags[FLAG_HELP] = findArg(argv, "-?") ? 1 : 0;

	return (flags);
}

int main (int argc, char **argv){
	size_t *flags;
	int icmp_socket;
	struct addrinfo *dest;


	if (argc < 2)
		return (0);

	flags = initFlags(&argv[1]);

	if (flags[FLAG_HELP])
		return (printf("Usage: ping [-v | -f] <ip/hostname>\n"));
	if (!checkInput(&argv[1]))
		return(printf("Bad input: ping [-v | -f] <ip/hostname>\n"));
	if (argc > 2 && !ft_memchr(flags, 1, sizeof(size_t) * FLAGS_NB))
		return (printf("Bad flag: [-v | -f]\n"));
	
	signal(SIGINT, sigHandler);

	icmp_socket = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (icmp_socket < 0)
		return (printf("Error: socket creation failed, please make sure to have the right to create a socket\n"));
	
	if (getaddrinfo(findHost(&argv[1]), NULL, NULL, &dest) != 0) //get All adresse by hostname & ip
		return (printf("Error: wrong hostname or ip, or no internet connection\n"));

	 for (struct addrinfo *rp = dest; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) { // IPv4
			char ipv4[INET_ADDRSTRLEN];
			char hostname[NI_MAXHOST];

			ipv4ToString(((struct sockaddr_in *)rp->ai_addr)->sin_addr.s_addr, ipv4);

			printHeader(ipv4, flags);

			getnameinfo(rp->ai_addr, rp->ai_addrlen, hostname, NI_MAXHOST, NULL, 0, 0);
	
			launchPing(icmp_socket, *rp, flags, hostname);

			freeaddrinfo(dest);
			return (0);
        }
    }

	return (1);
}
