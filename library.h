#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>

#ifndef LIBRARY_H
#define LIBRARY_H

struct song_node {
    char name[100];
    struct song_node *next;
	};

int err();
void getMP3names();
void print_list( struct song_node *n);
struct song_node* order( struct song_node *n, char *name);
struct song_node* free_list( struct song_node *n);
struct song_node* add_song( struct song_node* p_node, char* playlist, char* name);
#endif
