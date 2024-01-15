#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>

#ifndef LIBRARY_H
#define LIBRARY_H

struct song_node {
    char name[100];
    struct song_node *next;
	};

struct song_node* getMP3names();
void print_list( struct song_node *n);
void display_playlist(char * playlist);
struct song_node* free_list( struct song_node *n);
struct song_node* add_song( struct song_node* lib, struct song_node* p_node, char* playlist, char* name);
struct song_node* remove_song( struct song_node *p_node, char* playlist, char* name);
void make_playlist( char* buff, char* playlist);
void remove_playlist( struct song_node* p_node, char* playlist);
void remove_all_playlists();
void play_song( char* name);
void play_playlist( char* playlist);
char* shuffle(struct song_node* n);

int inLibrary( struct song_node* library, char* name);
int isPlaylist( char* playlist);

void err(int i, char* message);	
#endif
