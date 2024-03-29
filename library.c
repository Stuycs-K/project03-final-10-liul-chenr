#include "library.h"

void err(int i, char* message){
  if( i < 0){
      printf("Error: %s - %s\n", message, strerror(errno));
      exit(1);
  }
}

void print_list( struct song_node *n){
	if( n != NULL){
		printf( "\t%s\n", n->name);
		print_list( n->next);
	}
}

/*
	Takes in a character buffer, a song name, and a file type
	Concatenates the song name and the file type together
	ex: extension( buff, "everything_i_own", ".mp3") will store "everything_i_own.mp3" in buff
*/
void extension( char* buff, char* name, char* type){
//	strcpy( buff, name);
//	strcat( buff, type);
    snprintf(buff, 256, "%s%s", name, type);
//    printf("buff: %s\n", buff);
}

/*
	Takes in a string
	Removes the newline at the end
*/
void term( char* line){
	int i = 0;
	while( i < strlen( line)){
		if( line[i] == '\n' || line[i] == '\r')
			line[i] = 0;
		i++;
	}
}

/*
	Takes in a linked list, and a song name
	Creates a linked list with the song name
	Inserts the new struct in front of the struct in the parameter
*/
struct song_node* insert_front( struct song_node *n, char *name){
	struct song_node* newNode = (struct song_node*) malloc( sizeof( struct song_node));
	strcpy( newNode->name, name);
	newNode->next = n;
	return newNode;
}

/*
	Takes in a linked list, and a song name
	Orders the song name into the linked list alphabetically
*/
struct song_node* order( struct song_node *n, char *name){
	
	//inserts the node in front
	struct song_node* newNode = insert_front( n, name);
	
	//if the newNode is the first node in the list, return newNode
	if( newNode->next == NULL)
		return newNode;
	
	//if the newNode is in front of the first node in n, return newNode
	if( strcmp( newNode->name, n->name) < 0)
		return newNode;
	
	struct song_node* front = n;
	struct song_node* here = n;
	
	while( n != NULL){
		
		//if the next node is NULL and newNode is after the current node
		//set the next node to newNode and the node after newNode to NULL
		//return front
		if( n->next == NULL && strcmp( newNode->name, n->name) > 0){
			n->next = newNode;
			newNode->next = NULL;
			return front;
		}
		
		//if newNode goes after the current node
		//set here to be the current node (keeps track of the node prior to the current one)
		if( strcmp( newNode->name, n->name) > 0)
			here = n;
		
		//if newNode goes before the current node
		//set the node after the prior node to newNode and newNode's next node to the current node
		//return front
		else if( strcmp( newNode->name, n->name) < 0){
			here->next = newNode;
			newNode->next = n;
			return front;
		}
		n = n->next;
	}
    
    return newNode;
}

/*
	Takes in a linked list version of the music_library and a song name
	Checks if the song is in the music_library
	Returns 1 if true
			0 if false
*/
int inLibrary( struct song_node* library, char* name){
	while( library != NULL){
		if( strcmp( library->name, name) == 0)
			return 1;
		library = library->next;
	}
	return 0;
}

/*
	Takes in a linked list version of the music_library, a linked list version of the playlist, the name of the playlist, and a song name
	Add the song to the linked list version of playlist, and then write the whole list to the playlist file
	Returns the first node of the linked list
*/
struct song_node* add_song( struct song_node* lib, struct song_node* p_node, char* playlist, char* name, char* id){
	
	if( inLibrary( lib, name) == 0){
		printf( "song not in library\n");
        printf( "pick another song: ");
		char buff[100];
		fgets( buff, 99, stdin);
		buff[ strlen(buff) - 1] = 0;
		printf( "new song: %s\n", buff);
		add_song( lib, p_node, playlist, buff, id);
	}
	else{
		//inserts the song into the linked list playlist
		p_node = order( p_node, name);
		struct song_node* newNode = p_node;
		
		//converts the playlist name to include the .txt extension
		char folder[ strlen( playlist) + 1 + strlen(id)];
		strcpy( folder, id);
		strcat( folder, "/");
		strcat( folder, playlist);
		char pl[ strlen(folder) + 4];
		extension( pl, folder, ".txt");
		
		//opens the playlist file
		// printf( "opening %s\n", playlist);
		int p_file = open( pl, O_WRONLY | O_TRUNC, 0644);
		err( p_file, "p_file failed to open");
		
		//write the linked list playlist into the playlist file
		while( newNode != NULL){
			write( p_file, newNode->name, strlen(newNode->name));
			write( p_file, "\n", 1);
			newNode = newNode->next;
		}
		
		close( p_file);
		return p_node;
	}
    return p_node;
}

/* 
	Takes in a linked list version of the playlist, the name of the playlist and a song name
	Removes the song from the linked list version of the playlist, and then writes the whole list to the playlist file
	Returns the first node of the linked list
*/
struct song_node* remove_song( struct song_node *p_node, char* playlist, char* name, char* id){
	struct song_node* remove = p_node;
	struct song_node* f = NULL;
	
	while( remove != NULL){
		if( strcmp( remove->name, name) == 0){
			if( f == NULL) p_node = p_node->next;
			else f->next = remove->next;
			free( remove);
			
			// printf( "writing to file\n");
			//converts the playlist name to include the .txt extension
			char folder[ strlen( playlist) + 1 + strlen(id)];
			strcpy( folder, id);
			strcat( folder, "/");
			strcat( folder, playlist);
			char pl[ strlen(folder) + 4];
			extension( pl, folder, ".txt");
			
			//opens the playlist file
			// printf( "opening %s\n", playlist);
			int p_file = open( pl, O_WRONLY | O_TRUNC, 0644);
			err( p_file, "p_file failed to open");
			
			//write the linked list playlist into the playlist file
			struct song_node* p = p_node;
			while( p_node != NULL){
				write( p_file, p_node->name, strlen( p_node->name));
				write( p_file, "\n", 1);
				p_node = p_node->next;
			}
			
			close( p_file);
					
			return p;
		}
		f = remove;
		remove = remove->next;
	}
	
	return p_node;
}

/*
	Takes in a playlist name
	Checks if the playlist exist
	Returns 1 if true
			0 if false
*/
int isPlaylist( char* playlist, char* id){
	char folder[ strlen( playlist) + 1 + strlen(id)];
	strcpy( folder, id);
	strcat( folder, "/");
	strcat( folder, playlist);
	char pl[ strlen(folder) + 4];
	extension( pl, folder, ".txt");
	
	DIR* d;
	d = opendir( id);
	if( d == NULL)
		return 0;
	
	int file = open( pl, O_CREAT | O_EXCL, 0644);
	if( file == -1){
		close( file);
		return 1;
	}
	
	close( file);
	remove( pl);
	return 0;
}

void display_playlist(char * playlist, char* id) {
    if(isPlaylist(playlist, id) == 1) {
        char buff[256];
        extension(buff, playlist, ".txt");
//        printf("buff: %s\n", buff);
        int file = open(buff, O_RDONLY);
        
        char rbyte[256];
        int bytesRead;
        bytesRead = read(file, rbyte, sizeof(rbyte));
        printf("\t%s", rbyte);
        while((bytesRead = read(file, rbyte, sizeof(rbyte))) > 0) {
            rbyte[bytesRead-1] = '\0';
            printf("\t%s", rbyte);
        }
        close(file);
    }else printf("playlist doesn't exist\n");
}


/*
	Takes in a linked list version of the playlist, and the playlist name
	Removes the playlist file and frees the linked list associated with the playlist.
*/
void remove_playlist( struct song_node* p_node, char* playlist, char* id){
	if( strcmp( playlist, "library") == 0)
		printf( "library cannot be removed\n");
	else if( isPlaylist( playlist, id) == 1){
		char folder[ strlen( playlist) + 1 + strlen(id)];
		strcpy( folder, id);
		strcat( folder, "/");
		strcat( folder, playlist);
		char pl[ strlen(folder) + 4];
		extension( pl, folder, ".txt");
		
		remove( pl);
		free_list( p_node);
	}
	else{
		printf( "%s does not exist\n", playlist);
	}
}

// removes all created playlists
void remove_all_playlists( char* id){
	DIR* d;
	d = opendir( id);
	if( d == NULL) printf( "error opening dir %s\n", strerror( errno));
	struct dirent *entry;
	
	char buff[256];
	char* line;
	char* token;
	char PATH[ 256];
	strcpy( PATH, id);
	strcat( PATH, "/");
	
	while( entry = readdir( d)){
		sprintf( buff, "%s", entry->d_name);
		line = buff;
		token = strsep( &line, ".");
		// printf( "line: %s\n", line);
		
		if( line != NULL && strcmp( line, "txt") == 0){
			strcat( PATH, entry->d_name);
			remove( PATH);
		}
	}
	
	closedir( d);
}

/*
	Takes in a char buffer and a playlist name
	Creates a text file using the playlist name
*/
void make_playlist( char* buff, char* playlist, char* id){
    
	DIR* d;
	d = opendir( id);
	if( d == NULL)
		mkdir( id, 0755);
	
    //converts the playlist name to include the .txt extension
    char folder[ strlen( playlist) + 1 + strlen(id)];
	strcpy( folder, id);
	strcat( folder, "/");
	strcat( folder, playlist);
	char pl[ strlen(folder) + 4];
	extension( pl, folder, ".txt");
    // printf( "%s\n", pl);
    
	//create the file using the playlist name
	int file = open( pl, O_CREAT | O_EXCL, 0644);
    err(file, "open file error");
    //copy the playlist name into the char buffer
    strcpy( buff, playlist);
	
	close( file);
	closedir( d);
}

//get the song names of all mp3 in the music library
struct song_node* getMP3names() {
    DIR * d;
    char* PATH = "./music_library/";
    struct dirent *entry;
    char buff[256];
    struct song_node* list;
    list = NULL;
    
    d = opendir(PATH);
    if (d == NULL) err(errno, "open directory error");
    
    char librarypath[270] = "library.txt";
//    printf("librarypath: %s\n", librarypath);
    
    int file = open( librarypath, O_CREAT | O_TRUNC, 0644);
    err(file, "open file error");
    close(file);
    
    while((entry = readdir( d ))){
        if (entry->d_type!=4) {
            char songname[sizeof(entry->d_name) - 3];
            strncpy(songname, entry->d_name, sizeof(songname) - 1);
            songname[sizeof(songname) - 1] = '\0';

            // Find and remove the ".mp3"
            char* rm = strstr(songname, ".mp3");
            if (rm != NULL) {
                *rm = '\0';
                
                list = order(list, songname);
//                print_list(list);
//                printf("\n");
            }
        }
    }
    closedir(d);
    
    struct song_node* cpylist = list;
    file = open(librarypath, O_WRONLY);
    err(file, "file error");
    
    while(cpylist != NULL){
        write(file, cpylist->name, strlen(cpylist->name));
        write(file, "\n", 1);
        cpylist = cpylist->next;
    }
    
    close(file);

    return list;
}

/*
	Takes in a song name
	Plays the song using mpg123
*/
void play_song( char* name){
	
	//adds music_library/ and .mp3 onto the song name
	char song[ 14 + strlen( name)];
//    printf("size: %d\n", strlen(song));
	extension( song, "music_library/", name);
    char songpath[strlen(song)+4];
	extension( songpath, song, ".mp3");
//    printf( "command: %s\n", songpath);
	
	char* cmdargv[3];
	cmdargv[0] = "mpg123";
	cmdargv[1] = songpath;
    cmdargv[2] = NULL;
	
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
		// printf( "child process done\n");
	}
}

/* 
	Takes in a playlist name
	Gets each song name in the playlist and plays it
*/
void play_playlist( char* playlist, char* id){
	
	char folder[ strlen( playlist) + 1 + strlen(id)];
	strcpy( folder, id);
	strcat( folder, "/");
	strcat( folder, playlist);
	char pl[ strlen(folder) + 4];
	extension( pl, folder, ".txt");
	
	FILE* p_file = fopen( pl, "r");
	if( p_file == NULL){
		printf( "playlist does not exist\n");
		char buff[100];
		fgets( buff, 99, stdin);
		buff[ strlen(buff) - 1] = 0;
		printf( "playing from %s\n", buff);
		play_playlist( buff, id);
	}
	
	char song[100];
	while( fgets( song, 100, p_file) != NULL){
		term( song);
		// printf( "%s\n", song);
		play_song( song);
	}
}

/*
	Takes in a linked list
	Frees each node in the list
*/
struct song_node* free_list( struct song_node *n){
	while( n != NULL){
		struct song_node* node = n;
		n = n->next;
		free( node);
	}
	return NULL;
}

int genRan() {
    int random;
    int r_file=open("/dev/random", O_RDONLY, 0);
    err(r_file, "open file error");
    ssize_t rbyte=read(r_file, &random, sizeof(random));
    err(rbyte, "read error");
    close(r_file);
    if (random<0) random *= -1;
    return random;
}

//chose a random song in the given list
char* shuffle(struct song_node* n){
    if (n == NULL) return NULL;
    struct song_node *list;
    list = n;
    
    //get size of list
    int size = 1;
    while(n->next != NULL) {
        n = n->next;
        size++;
    }
    
    //chose a random song
    int random = genRan() % size;
    for (int i=0; i<random; i++) {
        list = list->next;
    }
    
    return list->name;
}
