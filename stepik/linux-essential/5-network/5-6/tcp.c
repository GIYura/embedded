#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

static void server(void);
static void client(void);

static struct sockaddr_in local;

int main(int argc, char* argv[])
{
	printf("Argument number: %d\n", argc);

	for (int i = 0; i < argc; i++)
	{
		printf("Argument %d %s\n", i, argv[i]);
	}

	printf("Program name: %s\n", argv[0]);

	if (argc != 2)
	{
		printf("Run %s [-s | -c]\n", argv[0]);
		return -1;
	}

	if (strcmp(argv[1], "-s") == 0)
	{
		server();
	}

	if (strcmp(argv[1], "-c") == 0)
	{
		client();
	}

	return 0;
}

static void server(void)
{
	printf("Inside Server\n");

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int clientSocket;

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;
	
	bind(sockfd,(struct sockaddr*)&local, sizeof(local));
	listen(sockfd, 5);
	
	clientSocket = accept(sockfd, NULL, NULL);

	char buff[1024];
	read(clientSocket, buff, sizeof(buff));
	printf("Received: %s\n", buff);
	
	close(clientSocket);
}

static void client(void)
{
	printf("Inside Client\n");

	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(1234);
	local.sin_family = AF_INET;

	connect(socketfd, (struct sockaddr*)&local, sizeof(local));

	char buff[] = "Hello Server\n";
	write(socketfd, buff, strlen(buff) + 1);
	
	printf("Send: %s\n", buff);

	
	close(socketfd);
}
