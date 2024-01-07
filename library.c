#include "library.h"

void print_list( struct song_node *n){
	if( n != NULL){
		printf( "Song: %s\n", n->name);
		print_list( n->next);
	}
}

void extension( char* buff, char* name, char* type){
	strcpy( buff, name);
	strcat( buff, type);
}

struct song_node* insert_front( struct song_node *n, char *name){
	struct song_node* newNode = (struct song_node*) malloc( sizeof( struct song_node));
	strcpy( newNode->name, name);
	newNode->next = n;
	return newNode;
}

struct song_node* order( struct song_node *n, char *name){
	struct song_node* newNode = insert_front( n, name);
	
	if( newNode->next == NULL)
		return newNode;
	if( strcmp( newNode->name, n->name) < 0)
		return newNode;
	
	struct song_node* front = n;
	struct song_node* here = n;
	
	while( n != NULL){
		if( n->next == NULL && strcmp( newNode->name, n->name) > 0){
			n->next = newNode;
			newNode->next = NULL;
			return front;
		}
		
		if( strcmp( newNode->name, n->name) > 0)
			here = n;
		else if( strcmp( newNode->name, n->name) < 0){
			here->next = newNode;
			newNode->next = n;
			return front;
		}
		n = n->next;
	}
}

struct song_node* add_song( struct song_node* p_node, char* playlist, char* name){
	struct song_node* newNode = order( p_node, name);
	
	char pl[ strlen( playlist) + 4];
	extension( pl, playlist, ".txt");
	
	// printf( "opening %s\n", playlist);
	int p_file = open( pl, O_WRONLY | O_TRUNC, 0644);
	err( p_file, "p_file failed to open");
		
	while( newNode != NULL){
		write( p_file, newNode->name, strlen( newNode->name));
		write( p_file, "\n", 1);
		newNode = newNode->next;
	}
	
	close( p_file);
	return newNode;
}

void make_playlist( char* buff, char* playlist){
	char pl[ strlen( playlist) + 4];
	extension( pl, playlist, ".txt");
	printf( "%s\n", pl);

	int file = open( pl, O_CREAT | O_EXCL, 0644);
	if( file == -1){
		printf( "playlist already exist\n");
		fgets( buff, 99, stdin);
		buff[ strlen(buff) - 1] = 0;
		printf( "new name: %s\n", buff);
		char nbuff[100];
		make_playlist( nbuff, buff);
	}
	else
		strcpy( buff, playlist);
	
	close( file);
}

void play_song( char* name){
	char song[ 14 + strlen( name) + 4];
	extension( song, "music_library/", name);
	extension( song, song, ".mp3");
	printf( "command: %s\n", song);
	
	char* cmdargv[1];
	cmdargv[0] = "mpg123";
	cmdargv[1] = song;
	
	pid_t p;
	p = fork();
	err( p, "forking err");
	if( p == 0){
		printf( "playing: %s\n\n", name);
		execvp( cmdargv[0], cmdargv);
		err( errno, "execvp err");
	}
	else{
		int status;
		pid_t id = wait( &status);
		err( status, "wait err");
	}
}

struct song_node* free_list( struct song_node *n){
	while( n != NULL){
		struct song_node* node = n;
		n = n->next;
		free( node);
	}
	return NULL;
}

void err(int i, char* message){
  if( i < 0){
	  printf("Error: %s - %s\n", message, strerror(errno));
  	exit(1);
  }
}