#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 80

const char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\
			 Content-Length: 12\r\n\
			 Hello HTTP!";

int main(int argc, const char* argv[])
{
	int listenfd, connfd;
	struct sockaddr_in  serveaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serveaddr, 0, sizeof(serveaddr));
	serveaddr.sin_family = AF_INET;
	serveaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveaddr.sin_port = htons(PORT);	

	bind(listenfd, (struct sockaddr *)&serveaddr, sizeof(serveaddr));
	listen(listenfd, 80);

	while(1) {
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
		write(connfd ,response, sizeof(response));
		close(connfd);
	}

	return 0;
}
