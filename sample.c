#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>     // For sockaddr_in6, inet_pton
#include <sys/socket.h>

int main() {
    int sockfd;
    struct sockaddr_in6 server_addr;

    // 1. Create IPv6 socket
    sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
        printf("Hello\n");
    }

    // 2. Prepare the sockaddr_in6 structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin6_family = AF_INET6;                          // IPv6
    server_addr.sin6_port = htons(8080);                         // Port number
    server_addr.sin6_addr = in6addr_any;                         // Any interface

    // 3. Bind the socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("IPv6 Server listening on port 8080...\n");

    close(sockfd);
    return 0;
}
