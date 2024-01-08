#include "networking.h"
#include "library.h"

static void sighandler(int signo) {
    if (signo == SIGINT) exit(0);
}

//void rot13(char * str) {
//    int i=0;
//    while (i < strlen(str)) {
//        if (str[i]>96 && str[i]<123) str[i] = (str[i] - 97 + 13) % 26 + 97;
//        else if (str[i]>64 && str[i]<91) str[i] = (str[i] - 65 + 13) % 26 + 65;
//        i++;
//    }
//}

void subserver_logic(int user_socket){
//    int pid = getpid();
//    char buff[BUFFER_SIZE];
//    while((read(user_socket, buff, sizeof(buff))) > 0) {
////        sleep(1);
//        printf("subserver %d read from user: %s\n", pid, buff);
//        rot13(buff);
//        if (write(user_socket, buff, sizeof(buff)) == -1) {
//            err(errno, "write error");
//        }
//    }
    
    
}

int main(int argc, char *argv[] ) {
    signal(SIGINT, sighandler);
    
    int listen_socket = server_setup();

    while(1) {

        int user_socket = server_tcp_handshake(listen_socket);
        printf("A new user connected.\n");

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
