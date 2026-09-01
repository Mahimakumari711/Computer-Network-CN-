/* Name - Mahima Kumari
 * SIC - 24BCSF87
 * Roll No. - 24 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define TRUE 1

int main ()
{
	int soc, chpid, msgsock;
	socklen_t len;
	char buf[1024], buf1[1024];
	struct sockaddr_in server, client;
	socklen_t addrlen = sizeof(client);
	//portno = 5001;

	/*First call to socket() function */
	soc = socket(AF_INET, SOCK_STREAM, 0);

	if(soc < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}

	// ---Configure settings of the server address structure -----
	// Initialize socket structure elements to zero
		//bzero((char *)&serv_addr, sizeof(serv_addr));
	//Set Address family = Internet
		server.sin_family = AF_INET;
	// Set IP address to localhost 
		//serv_addr.sin_addr.s_addr = INADDR_ANY;
		server.sin_addr.s_addr = inet_addr("127.0.0.1");
	//Set port number, using htns function to use proper btype order 
		//serv_addr.sin_port = htons(portno);
		server.sin_port = 0;

	/* Now bind the host address using bind() call. */
		if(bind(soc, (struct sockaddr *) &server, sizeof(server)) < 0)
		{
			perror("ERROR on binding");
			exit(1);
		}

	/* Now start listing for the clients, here process will go in sleep 
	 * mode and will wait for the incoming connection*/
		
		len = sizeof(server);
		
		if(getsockname(soc,(struct sockaddr *) &server, &len))
		{
			perror("\nError in getting port..");
			exit(3);
		}
		printf("\nSocket has port no: %hd\n",htons(server.sin_port));

		listen(soc,5); //Listen on the socket, with 5 max connection requesta queued 
		
		signal(SIGCHLD, SIG_IGN);

		do
		{
			/* Accept actual connection from the client */

			msgsock = accept(soc, (struct sockaddr *) &client,(socklen_t*) &addrlen);
			if(msgsock == -1 )
			{
				perror("\nError in accept..");
				exit(0);
			}
			else
			{
				if((chpid=fork()) == 0)
				{
					close(soc);
					do
					{
						read(msgsock,buf,1024);
						printf("\nMessage from client: %s\n",buf);
						printf("\nMesage to client:");
						scanf("%[^\n]",buf1);
						write(msgsock,buf1,1024);
					}
					while(strcmp(buf1,"bye")!=0);
					close(msgsock);
					exit(0);
				}
				else
					close(msgsock);
			}
		}
		while(TRUE);
		close(soc);
		return 0;
}
