#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define TRUE 1

int main()
{
	int sockfd;
	char buf[1024];
	struct sockaddr_in server, client;
	socklen_t client_addr_len = sizeof(client), server_addr_len;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("\nError in opening socket");
		exit(1);
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htons(INADDR_ANY);
	server.sin_port = htons(7777);
	if(bind(sockfd, (struct sockaddr *)&server, sizeof(server)))
	{
		perror("\nError in bind...");
		exit(2);
	}
	/*Not required as port is assigned manually*/
	/*server_addr_len = sizeof(server);
	if(getsockname(sockfd, (struct sockaddr *)&server, &server_addr_len))
	{
		perror("\nError in getting port... ");
		exit(3);
	}*/
	printf("\nSocket has port #%hd \n", ntohs(server.sin_port));
	while(1)
	{
		bzero(buf, 1024);
		if(recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client, &client_addr_len) < 0)
		{
			printf("Invalid Datagram Received\n");
		}
		printf("Received: %s \n", buf);
	}
	close(sockfd);
	return 0;
}
