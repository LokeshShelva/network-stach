#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct addrinfo hints, *serinfo, *i;
  char ipstr[INET6_ADDRSTRLEN];

  if (argc != 2) {
    fprintf(stderr, "usage: %s hostname\n", argv[0]);
    return 1;
  }

  memset(&hints, 0, sizeof hints);

  hints.ai_family = AF_UNSPEC;     // Any IP protocol
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;     // Fills my ip details

  int err = getaddrinfo(argv[1], "8000", &hints, &serinfo);
  if (err != 0) {
    fprintf(stderr, "gai error: %s\n", gai_strerror(err));
    return 1;
  }

  printf("Adresses for %s\n", argv[1]);

  for (i = serinfo; i != NULL; i = i->ai_next) {
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;
    void *addr;

    // IPv4
    if (i->ai_family == AF_INET) {
      ipv4 = (struct sockaddr_in *)i->ai_addr;
      addr = &(ipv4->sin_addr);
    } else {
      ipv6 = (struct sockaddr_in6 *)i->ai_addr;
      addr = &(ipv6->sin6_addr);
    }

    inet_ntop(i->ai_family, addr, ipstr, sizeof ipstr);
    printf("- %s\n", ipstr);
  }

  freeaddrinfo(serinfo);
  return 0;
}
