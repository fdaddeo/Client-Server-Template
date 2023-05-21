// D'Addeo Filippo [339643]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include <unistd.h>
#include <netdb.h>

char *host_name = "127.0.0.1";
int port = 8080;


/**
 * 
 * Creates a Socket object.
 * 
 * @return int The Socket file descriptor.
 * 
**/
int createSocket() 
{

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) 
	{

		perror("Error opening socket\n");
		exit(1);
	}

	return sockfd;
}


int main(int argc, char *argv[]) 
{

	struct sockaddr_in serv_addr;
 	struct hostent* server;

	int sockfd;

	int measurementNumber;
	int waitingTime;
	int executorNumber;

    // Define Struct for message.
	itemType msg;
	
	if (argc < 3) 
	{
		printf("Usage: %s args\n", argv[0]);
		exit(1);
	}

	srand(time(NULL));

	if ((server = gethostbyname(host_name)) == 0) 
	{

		perror("Error resolving local host\n");
		exit(1);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = ((struct in_addr *)(server->h_addr))->s_addr;
	serv_addr.sin_port = htons(port);

    /* Socket creation */
    sockfd = createSocket();		

    /* Connection to the hub */
    if (connect(sockfd, (void*)&serv_addr, sizeof(serv_addr)) == -1) 
    {
    
        perror("Error connecting to socket\n");
        exit(1);
    }

	/* Iterative connection to the hub */
    while (1)
	{
		/* Send the message */
		if (send(sockfd, &msg, sizeof(msg), 0) == -1) 
		{

			perror("Error on send\n");
			exit(1);
		}
		
		/* Receive message from server */
		if (recv(sockfd, &executorNumber, sizeof(executorNumber), 0) == -1) 
		{

			perror("Error in receiving response from server\n");
			exit(1);
		}
	}

    /* Close the connection */
    close(sockfd);

	printf("\nTerminated\n");

	return 0;
}

