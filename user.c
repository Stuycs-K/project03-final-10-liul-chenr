#include "network.h"
#include "library.h"

int pause = 0;

static void sighandler(int signo) {
    if (signo == SIGINT) exit(0);
    if (signo == SIGUSR1) {
        if (pause) {
            
            paused = 0;
        }else{
            
            paused = 1;
        }
    }
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

void command_library() {
    printf("List of Commands:\n")
    printf("\tplay song\n");
    printf("\tmake playlist\n");
    printf("\tadd song to playlist\n");
//    printf("\t\n");
}

void userLogic(int server_socket){
    int pid = getpid();
    int serverpid;
    err(write(server_socket, &pid, sizeof(pid)), "write error");
    err(read(server_socket, &serverpid, sizeof(serverpid)), "read error");
    printf("User %d connected to subserver %d\n", pid, serverpid);
    printf("Music Library Songs:\n");
    struct song_node* list = NULL;
    list = getMP3names(list);
    print_list(list);
    printf("\n");
    while(1) {
        char buff[256];
        printf("Give a command: ");
        fgets(buff, sizeof(buff), stdin);
        check(buff);

        if(strcmp(buff, "play song") == 0) {
            
        }else if(strcmp(buff, "make playlist") == 0) {
            
        }else if(strcmp(buff, "add song to playlist") == 0) {
            
        }
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
    
//    printf("IP: %s\n", IP);
    int server_socket = user_tcp_handshake(IP);
    
    userLogic(server_socket);
    close(server_socket);
}
