#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>


#ifndef NETWORKING_H
#define NETWORKING_H
#define PORT "19230"
#define BUFFER_SIZE 1024
#define KEY 12091
int server_setup();
int user_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short  *array;
    struct seminfo  *__buf;
};

int create_sem();
int remove_sem();
#endif
