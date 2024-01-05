#include "networking.h"
#include "library.h"

static void sighandler(int signo) {
    if (signo == SIGINT) exit(0);
}

void sigpipe_handler(int signo) {
    if (signo == SIGPIPE) exit(0);
}

void check(char *d) {
    int i=0;
    while (d[i] != '\0') {
        if (d[i] == '\n' || d[i] == '\r') d[i]=0;
        i++;
    }
}

void userLogic(int server_socket){
    int pid = getpid();
    while(1) {
        char buff[BUFFER_SIZE];

        printf("User %d write to server: ", pid);
        fgets(buff, sizeof(buff), stdin);
        check(buff);
        if (write(server_socket, buff, sizeof(buff)) == -1) {
            err(errno, "write error");
        }
        if (read(server_socket, buff, sizeof(buff)) == 0) {
//            printf("server exit");
            exit(0);
        }
        printf("User %d read from server: %s\n", pid, buff);
    }
}

int main(int argc, char *argv[] ) {
    signal(SIGINT, sighandler);
    signal(SIGPIPE, sigpipe_handler);
    
    char* IP = "127.0.0.1";
//    printf("argc: %d\n", argc);
    if(argc>1){
      IP=argv[1];
    }
    
    printf("IP: %s\n", IP);
    int server_socket = user_tcp_handshake(IP);
    printf("User connected.\n");
    userLogic(server_socket);
    close(server_socket);
}
