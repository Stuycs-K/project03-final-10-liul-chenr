#include "network.h"
#include "library.h"

static void sighandler(int signo) {
    if (signo == SIGINT) exit(0);
}

void subserver_logic(int user_socket){
    int pid = getpid();
    int ibuff;
    err(read(user_socket, &ibuff, sizeof(ibuff)), "read error");
    err(write(user_socket, &pid, sizeof(pid)), "write error");
    printf("User %d connected to subserver %d\n", ibuff, pid);
    
    char buff[BUFFER_SIZE];
    while((read(user_socket, buff, sizeof(buff))) > 0) {
        
    }
}

int main(int argc, char *argv[] ) {
    signal(SIGINT, sighandler);
    
    int listen_socket = server_setup();

    while(1) {
        int user_socket = server_tcp_handshake(listen_socket);

        int f = fork();
        if (f == 0) {
            subserver_logic(user_socket);
            close(user_socket);
            exit(0);
        }else if (f > 0) {
            close(user_socket);
        }else err(errno, "forking error");
    }
}