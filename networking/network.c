#include "network.h"
#include "library.h"

/*Create and bind a socket.
* Place the socket in a listening state.
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; // TCP socket
  hints->ai_flags = AI_PASSIVE; // Only needed on the server

  getaddrinfo(NULL, PORT, hints, &results); // Server sets node to NULL
  
  //create the socket
  int userd;//store the socket descriptor here
  userd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    
  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(userd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt  error");
  
  //bind the socket to address and port
    if (bind(userd, results->ai_addr, results->ai_addrlen) == -1) {
        err(errno, "bind error");
    }

  //set socket to listen state
    if (listen(userd, 10) == -1) err(errno, "listen err");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return userd;
}


/*Accept a connection from a user
 *return the to_user socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket){
    int user_socket;

    //accept the user connection
    socklen_t sock_size;
    struct sockaddr_storage user_address;
    sock_size = sizeof(user_address);
    user_socket = accept(listen_socket, (struct sockaddr *)&user_address, &sock_size);
  
    return user_socket;
}

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int user_tcp_handshake(char * server_address) {
    //getaddrinfo
    struct addrinfo *hints, *results;
    hints = calloc(1, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM; // TCP socket
    
    getaddrinfo(server_address, PORT, hints, &results); // Server sets node to NULL
    
    int serverd;//store the socket descriptor here
    //create the socket
    serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
    //connect to the server
    if (connect(serverd, results->ai_addr, results->ai_addrlen) == -1) {
        err(errno, "connect error");
    }
    
    free(hints);
    freeaddrinfo(results);
    
    return serverd;
}

int create_sem(){
	int semid;
	semid = semget( KEY, 10, IPC_CREAT | IPC_EXCL | 0644);
	if( semid == -1){
		semid = semget( KEY, 10, 0);
		int v; 
		for( int i = 0; i < 10; i++){
			v = semctl( semid, i, GETVAL, 0);
			printf( "semctl returned (%d): %d\n", i, v);
		}
	}
	else{
		printf( "sem created\n");
		
		union semun us;
		us.val = 1;
		int r;
		for( int i = 0; i < 10; i++){
			r = semctl( semid, 0, SETVAL, us);
			// printf( "semctl returned (%d): %d\n", i, r);
		}
	}
}

int remove_sem(){
	int semid;
	semid = semget( KEY, 10, IPC_CREAT | 0644);
	for( int i = 0; i < 10; i++){
		semctl( semid, i, IPC_RMID, 0);
		err( semid, "error removing sem");
		// printf( "sem (%d) removed\n", i);
	}
}
