#include "library.h"

// int list_songs(){
	// int lib_file;

	// lib_file = open( "song_library.txt", O_WRONLY | O_CREAT, 0644);
	// err( errno, "lib_file not opened");
// }

void print_list( struct song_node *n){
	if( n != NULL){
		printf( "Song: %s\n", n->name);
		print_list( n->next);
	}
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