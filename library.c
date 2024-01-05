#include "library.h"

int err(){
    printf("errno %d\n",errno);
    printf("%s\n",strerror(errno));
    exit(1);
}

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

void getMP3names() {
    DIR * d;
    char* PATH = "./music_library/";
    struct dirent *entry;
    char buff[256];
    
    d = opendir(PATH);
    if (d == NULL) err();
    printf("MP3 files:\n");
        
    while((entry = readdir( d ))){
        if (entry->d_type!=4) {
            printf("%s\n",entry->d_name);
//            printf("\t--type: %d\n",entry->d_type);
        }
    }
    closedir(d);
    free(PATH);
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
	printf( "opening %s\n", pl);
	
	int p_file = open( pl, O_WRONLY | O_TRUNC, 0644);
		
	while( newNode != NULL){
		write( p_file, newNode->name, strlen( newNode->name));
		write( p_file, "\n", 1);
		newNode = newNode->next;
	}
	
	close( p_file);
	return newNode;
}

int make_playlist( char* playlist){
	char pl[ strlen( playlist) + 4];
	extension( p1, playlist, ".txt");

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
