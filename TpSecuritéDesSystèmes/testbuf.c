#include <stdio.h>
#include <string.h>		// for strcpy, strlen
#include <unistd.h>		// for close
#include <stdlib.h>		// for atoi
#include <errno.h>		// for errno
#include <sysexits.h>		// for EX_USAGE

#define BUFFER_SIZE 1024
#define NAME_SIZE 2048

int handlingclient(int c) {
    char buffer[BUFFER_SIZE], name[NAME_SIZE];
    int bytes;

    strcpy(buffer, "Login : ");
    bytes = write(1, buffer, strlen(buffer));
    if (bytes == -1) {
        perror("send");
        return errno;
    }

    bytes = read(0, name, sizeof(name));
    if (bytes == -1) {
        perror("recv");
        return errno;
    }

    name[bytes - 1] = '\0';
    sprintf(buffer, "nice to meet you %s\n", name);

    bytes = write(1, buffer, strlen(buffer));
    if (bytes == -1) {
        perror("send");
        return errno;
    }
}

int main(int argc, char ** argv) {
    return handlingclient(0);
}

