
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>

#include <string.h>		// for strcpy, strlen
#include <unistd.h>		// for close
#include <stdlib.h>		// for atoi
#include <errno.h>		// for errno
#include <sysexits.h>		// for EX_USAGE

#define BUFFER_SIZE 1024
#define NAME_SIZE 2048

int handling_client(int c) {
    char buffer[BUFFER_SIZE], name[NAME_SIZE];
    int bytes;

    // Since the stack base is now randomized, print the address of buffer
    printf("buffer = %p\n", buffer);

    strcpy(buffer, "Login : ");
    bytes = send(c, buffer, strlen(buffer), 0);
    if (bytes == -1) {
        perror("send");
        return errno;
    }

    bytes = recv(c, name, sizeof(name), 0);
    if (bytes == -1) {
        perror("recv");
        return errno;
    }

    name[bytes - 1] = '\0';
    sprintf(buffer, "nice to meet you %s\n", name);

    bytes = send(c, buffer, strlen(buffer), 0);
    if (bytes == -1) {
        perror("send");
        return errno;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s port\n", argv[0]);
        exit(EX_USAGE);
    }

    // Let the father not being disturbed by its childs
    signal(SIGCLD, SIG_IGN);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in srv;
    srv.sin_addr.s_addr = INADDR_ANY;
    srv.sin_port = htons((unsigned short int) atol(argv[1]));
    srv.sin_family = AF_INET;

    if (bind(sock, (struct sockaddr *) &srv, sizeof(srv)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(sock, 3) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        int con = accept(sock, NULL, NULL);
        if (con == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == 0) {
            close(sock);

            // The child processes the request
            if (handling_client(con) != 0) {
                fprintf(stderr, "%s: handling failed", argv[0]);
            }

            // The child closes the connection...
            close(con);

            // and exits !
            exit(EXIT_SUCCESS);
        } else if (pid > 0) {
            // The father closes the file descriptor
            close(con);
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

