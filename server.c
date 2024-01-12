#include "network.h"
#include "library.h"

#define READ 0
#define WRITE 1

static void sighandler(int signo) {
    if (signo == SIGINT){
		remove( ".p_pipe");
		exit(0);
	}
}

void subserver_logic(int user_socket, int* p_arry){
    int pid = getpid();
    int ibuff;
    err(read(user_socket, &ibuff, sizeof(ibuff)), "read error");
    err(write(user_socket, &pid, sizeof(pid)), "write error");
    printf("User %d connected to subserver %d\n", ibuff, pid);
	
	int fifo = open( ".p_pipe", O_WRONLY);
	err( fifo, "error opening p_pipe");
    
    char buff[BUFFER_SIZE];
    while((read(user_socket, buff, strlen(buff))) > 0) {
        printf( "from %d: %s\n", ibuff, buff);
		write( fifo, buff, strlen( buff));
    }
	close( fifo);
}

int main(int argc, char *argv[] ) {
    signal(SIGINT, sighandler);
    
    int listen_socket = server_setup();
	
	int p_arry[10][2];
	for( int i = 0; i < 10; i++){
		pipe( p_arry[i]);
	}
	int usr = 0;
	
	char* p_pipe = ".p_pipe";
	err( mkfifo( p_pipe, 0644), "error creating WKP");
	
	int fifo = open( p_pipe, O_RDONLY);
	err( fifo, "error opening p_pipe");

    while(1) {
        int user_socket = server_tcp_handshake(listen_socket);

        int f = fork();
        if (f == 0) {
            subserver_logic( user_socket, p_arry[usr++]);
            close(user_socket);
            exit(0);
        }else if (f > 0) {
            close(user_socket);
			
			char buff[ BUFFER_SIZE];
			read( fifo, buff, sizeof( buff));
			printf( "from child: %s\n", buff);
			close( fifo);
        }else err(errno, "forking error");
    }
}