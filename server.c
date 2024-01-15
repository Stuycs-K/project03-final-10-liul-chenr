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
    
//    char buff[BUFFER_SIZE];
//    while((read(user_socket, buff, sizeof(buff))) > 0) {
//        
//    }
}

int main(int argc, char *argv[] ) {
    signal(SIGINT, sighandler);
    
    int listen_socket = server_setup();
    
    fd_set read_fds;

    char buff[1025]="";

    while(1) {
        
        FD_ZERO(&read_fds);
        FD_SET(listen_socket,&read_fds);
        int i = select(listen_socket+1, &read_fds, NULL, NULL, NULL);
        
        // if socket
        if (FD_ISSET(listen_socket, &read_fds)) {
            //accept the connection
            int user_socket = server_tcp_handshake(listen_socket);
            subserver_logic(user_socket);
            close(user_socket);
        }

    }
}
