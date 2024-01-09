#include "library.h"

void err(int i, char* message){
  if( i < 0){
      printf("Error: %s - %s\n", message, strerror(errno));
      exit(1);
  }
}

void print_list( struct song_node *n){
	if( n != NULL){
		printf( "Song: %s\n", n->name);
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
    printf("buff: %s\n", buff);
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


//get the song names of all mp3 in the music library
struct song_node* getMP3names(struct song_node* list) {
    DIR * d;
    char* PATH = "./music_library/";
    struct dirent *entry;
    char buff[256];
    
    d = opendir(PATH);
    if (d == NULL) err(errno, "open directory error");
    
    char * library_playlist;
    make_playlist(library_playlist, "musiclib");
    printf("%s created\n", library_playlist);
    
    char* librarypath;
    snprintf(librarypath, 256, "%s%s", library_playlist, ".txt");
    printf("librarypath: %s\n", librarypath);
    
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
                print_list(list);
                
//                printf("library playlist: %s\n", library_playlist);
                
                int file = open(librarypath, O_WRONLY);
                err(file, "file error");
                
                write(file, songname, strlen(songname));
                write(file, "\n", 1);
                close(file);
            }
        }
    }
    closedir(d);
    
    return list;
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
	Takes in a linked list version of the playlist, the name of the playlist, and a song name
	Add the song to the song_node version of playlist, and then write the whole list to the playlist file
	Returns the first node of the linked list
*/
struct song_node* add_song( struct song_node* p_node, char* playlist, char* name){
	
	//inserts the song into the linked list playlist
    p_node = order( p_node, name);
	struct song_node* newNode = p_node;
    
    //converts the playlist name to include the .txt extension
    char pl[ strlen( playlist) + 4];
    extension( pl, playlist, ".txt");
    
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

/*
	Takes in a char buffer and a playlist name
	Creates a text file using the playlist name
*/
void make_playlist( char* buff, char* playlist){
    
    //converts the playlist name to include the .txt extension
    char pl[ strlen( playlist) + 4];
    extension( pl, playlist, ".txt");
    //printf( "%s\n", pl);
	
	//create the file using the playlist name
	int file = open( pl, O_CREAT | O_EXCL, 0644);
	if( file == -1){
		
		//if the file already exist, prompt the user for a new name
		printf( "playlist already exist\n");
        printf("choose another name: ");
		fgets( buff, 99, stdin);
		buff[ strlen(buff) - 1] = 0;
		printf( "new name: %s\n", buff);
		char nbuff[100];
		make_playlist( nbuff, buff);
	}
	else
		//copy the playlist name into the char buffer
		strcpy( buff, playlist);
	
	close( file);
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
    printf( "command: %s\n", songpath);
	
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

void play_playlist( char* playlist){
	
	char pl[ strlen( playlist) + 4];
	extension( pl, playlist, ".txt");
	
	FILE* p_file = fopen( pl, "r");
	if( p_file == NULL){
		printf( "playlist does not exist\n");
		char buff[100];
		fgets( buff, 99, stdin);
		buff[ strlen(buff) - 1] = 0;
		printf( "playing from %s\n", buff);
		play_playlist( buff);
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

struct song_node* shuffle(struct song_node* n){
    struct song_node *list;
    list = n;
    int size = 0;
    while(n = n->next) {
        size++;
    }
}
