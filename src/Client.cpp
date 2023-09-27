#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>

#define SERVER_PORT 8989
#define MAXLINE 4096
#define SA struct sockaddr

void err_and_exit(const char *fmt, ...);

int main(int argc, char **argv) {
    int sockfd, n;
    int sendbytes;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_and_exit("Error creating socket");
    }

    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);

    /*if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        err_and_exit("inet_pton error for %s ", argv[1]);
    }*/

    if (connect(sockfd, (SA *) &servaddr, sizeof servaddr) < 0) {
        err_and_exit("Connect failed");
    }


    while (true) {

        memset(recvline, 0, MAXLINE);
        memset(sendline, 0, MAXLINE);

        std::cout << "Enter a command (or 'quit' to exit): ";
        std::cin.getline(sendline, sizeof sendline);

        if (strcmp(sendline, "quit") == 0) {
            break;
        }

        sendbytes = strlen(sendline);
        sendline[sendbytes++] = '\n';

        if (write(sockfd, sendline, sendbytes) != sendbytes) {
            err_and_exit("Write error");
        }

        n = read(sockfd, recvline, MAXLINE);

        if (n < 0) {
            err_and_exit("Read error");
        }

        std::cout << recvline << '\n';
    }
    close(sockfd);

    return 0;
}

void err_and_exit(const char *fmt, ...) {
    int errno_save;
    va_list ap;

    errno_save = errno;

    va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    std::cout << std::endl;
    fflush(stdout);

    if (errno_save != 0) {
        fprintf(stdout, "(errno = %d) : %s\n", errno_save,
        strerror(errno_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    va_end(ap);

    exit(1);
}
