#include <netdb.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{	
	if (argc != 2)
	{
		printf("Please, enter host name\n");
		return -1;
	}

	struct hostent* host = NULL;

	host = gethostbyname(argv[1]);

	if (host == NULL)
	{
		printf("Error\n");
		return -1;
	}

	printf("Canonical name: [%s]\n", host->h_name);
	printf("Type: [%s] len: [%d]\n", (host->h_addrtype == AF_INET) ? "ipv4" : "ipv6", host->h_length);

	int i = 0; 

	while (host->h_addr_list[i] != NULL)
	{
		struct in_addr* addr = (struct in_addr*)host->h_addr_list[i];
		printf("%s\n", inet_ntoa(*addr));
		i++;
	}
}
