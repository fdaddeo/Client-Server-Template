#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <netdb.h>

int port = 8000;

int main() 
{

	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;

	int numberOfSensors;

    // Define Struct for message.
	itemType msg;

	/* Socket creation */
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if (sockfd == -1) 
	{

		perror("Error opening socket\n");
		exit(1);
	}
	
	int options = 1;

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &options, sizeof (options)) < 0) 
	{
		
		perror("Error on setsockopt\n");
		exit(1);
	}

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	/* Address bindind to socket */
	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) 
	{

		perror("Error on binding\n");
		exit(1);
	}
	
	/* Maximum number of connection kept in the socket queue */
	if (listen(sockfd, 20) == -1) 
	{

		perror("Error on listen\n");
		exit(1);
	}

	socklen_t address_size = sizeof(cli_addr);

	while(1) 
	{
        int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &address_size);      
		
		if (newsockfd == -1) 
		{

			perror("Error on accept\n");
			exit(1);
		}
		
		/* Receive a message from the Hub or from an actuator */
		if (recv(newsockfd, &msg, sizeof(msg), 0) == -1) 
		{

			perror("Error on receive\n");
			exit(1);
		}

		/* Save the Socket File Descriptor */
		msg.sockfd = newsockfd;

        /*
            TODO: handle your message.
        */
	}

	close(sockfd);

	return 0;
}