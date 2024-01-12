#include "network.h"
#include "library.h"

int paused = 0;

static void sighandler(int signo) {
    if (signo == SIGINT) exit(0);
//    if (signo == SIGUSR1) {
//        if (paused) {
//
//            paused = 0;
//        }else{
//            
//            paused = 1;
//        }
//    }
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

//type "see commands" to get here
void command_library() {
    printf("List of Commands:\n");
    printf("\tdisplay playlists\n"); //done
    printf("\tdisplay songs in playlist\n"); //done
    printf("\tplay song\n"); //done
    printf("\tplay playlist\n"); //done
    printf("\tcreate playlist\n"); //done
    printf("\tadd song to playlist\n"); //done
    printf("\tremove playlist\n"); //modified, need testing
    printf("\tremove song from playlist\n"); //done
    printf("\tshuffle\n"); //done
//    printf("\t\n");
}

void userLogic(int server_socket){
    int pid = getpid();
    int serverpid;
    err(write(server_socket, &pid, sizeof(pid)), "write error");
    err(read(server_socket, &serverpid, sizeof(serverpid)), "read error");
    printf("User %d connected to subserver %d\n\n", pid, serverpid);
    printf("music library longs:\n");
    struct song_node* list = NULL;
    list = getMP3names(list);
    print_list(list);
    
    struct song_node* playlists[5];
    for (int i=0; i<sizeof(playlists); i++) playlists[i]=NULL;
    int iOfplist = 0;

	char* playlistf[5];
    int plSize = 5;
	int iOfpl = 0;
	
    while(1) {
        // list = getMP3names(list);
//        print_list(list);
        char cmd[256];
	printf( "\ntype 'see commands' to see the available commands\n");
        printf("give a command: ");
        fgets(cmd, sizeof(cmd), stdin);
        check(cmd);
        printf("\n");
        
        if(strcmp(cmd, "see commands") == 0) {

            command_library();

        }else if(strcmp(cmd, "display playlists") == 0) {
            
            printf("all playlists:\n");
            printf("\tlibrary\n");
            for( int i = 0; playlistf[i] != NULL; i++){
                printf("\t%s\n", playlistf[i]);
            }
            
        }else if(strcmp(cmd, "display songs in playlist") == 0) {
            
            char plname[100];
            printf("give playlist name: ");
            fgets(plname, sizeof(plname), stdin);
            check(plname);

            while( isPlaylist( plname) == 0){
                printf( "%s is not a valid playlist\n", plname);
                printf( "give a new playlist: ");
                fgets(plname, sizeof(plname), stdin);
                check(plname);
            }
            
            for( int i = 0; playlistf[i] != NULL; i++){
                if( strcmp( playlistf[i], plname) == 0)
                    iOfplist = i;
            }
            
            struct song_node* plist = playlists[iOfplist];
            printf("\n%s songs:\n", plname);
            print_list(plist);
            
        }else if(strcmp(cmd, "play song") == 0) {
            
            printf("music library songs:\n");
            print_list(list);
            printf("\ngive song name: ");
            fgets(cmd, sizeof(cmd), stdin);
            check(cmd);
            play_song(cmd);
            
        }else if( strcmp( cmd, "play playlist") == 0){
            
            printf( "give playlist name: ");
            fgets( cmd, sizeof( cmd), stdin);
            check( cmd);
            while( isPlaylist( cmd) == 0){
                printf( "playlist does not exist\n");
                printf( "please give a new playlist: ");
                fgets( cmd, sizeof( cmd), stdin);
                check( cmd);
            }
            play_playlist( cmd);
            
        }else if(strcmp(cmd, "create playlist") == 0) {
            
            printf("give playlist name: ");
            fgets(cmd, sizeof(cmd), stdin);
            check(cmd);
			while( isPlaylist( cmd) == 1){
				printf( "playlist already exist\n");
				printf( "please give a new playlist name: ");
				fgets(cmd, sizeof(cmd), stdin);
				check(cmd);
			}
            
            char buff[100];
            make_playlist(buff, cmd);
            printf("playlist '%s' created\n", cmd);
            playlistf[ iOfpl++] = buff;
            
        }else if(strcmp(cmd, "add song to playlist") == 0) {

            char sname[100];
            printf("music library songs:\n");
            printf("list: %s\n", list->name);
            print_list(list);
            
            printf("\n");
            printf("give song name: ");
            fgets(sname, sizeof(sname), stdin);
            check(sname);
//            printf("sname: %s\n", sname);
            
			while( inLibrary( list, sname) == 0){
				printf( "%s is not in the library\n", sname);
				printf( "give a new song name: ");
				fgets(sname, sizeof(sname), stdin);
				check(sname);
//				printf("sname: %s\n", sname);
			}
            
            char plname[100];
            printf("give playlist name: ");
            fgets(plname, sizeof(plname), stdin);
            check(plname);
//            printf("plname: %s\n", plname);

			while( isPlaylist( plname) == 0){
				printf( "%s is not a valid playlist\n", plname);
				printf( "give a new playlist: ");
				fgets(plname, sizeof(plname), stdin);
				check(plname);
//				printf("plname: %s\n", plname);
			}
			
			for( int i = 0; playlistf[i] != NULL; i++){
				if( strcmp( playlistf[i], plname) == 0)
					iOfplist = i;
			}
            
            struct song_node* plist = playlists[iOfplist];
            plist = add_song(list, plist, plname, sname);
            printf("song '%s' added to playlist '%s'\n", sname, plname);
            playlists[iOfplist] = plist;

        }else if (strcmp(cmd, "remove playlist") == 0) {

            printf("give playlist name: ");
            fgets(cmd, sizeof(cmd), stdin);
            check(cmd);
            
            while( isPlaylist( cmd) == 0){
                printf( "%s is not a valid playlist\n", cmd);
                printf( "give a new playlist: ");
                fgets(cmd, sizeof(cmd), stdin);
                check(cmd);
                printf("plname: %s\n", cmd);
            }
            
            for( int i = 0; playlistf[i] != NULL; i++){
                if( strcmp( playlistf[i], cmd) == 0)
                    iOfplist = i;
            }
            
            remove_playlist(playlists[iOfplist], playlistf[iOfplist]);
            printf("playlist '%s' removed\n", cmd);
            for(int i = iOfplist; i < plSize - 1; i++) {
                playlistf[i] = playlistf[i + 1];
                playlists[i] = playlists[i + 1];
            }
            playlistf[plSize - 1] = NULL;
            playlists[plSize - 1] = NULL;
            iOfpl--;
            
        }else if (strcmp(cmd, "remove song from playlist") == 0) {

            char plname[256];
            printf("give playlist name: ");
            fgets(plname, sizeof(plname), stdin);
            check(plname);

            while( isPlaylist( plname) == 0){
				printf( "%s is not a valid playlist\n", plname);
				printf( "give a new playlist: ");
				fgets(plname, sizeof(plname), stdin);
				check(plname);
//				printf("plname: %s\n", plname);
			}
            
            for( int i = 0; playlistf[i] != NULL; i++){
                if( strcmp( playlistf[i], plname) == 0)
                    iOfplist = i;
            }
            
            struct song_node* plist = playlists[iOfplist];
            
            char sname[256];
            printf("give song name: ");
            fgets(sname, sizeof(sname), stdin);
            check(sname);

            while( inLibrary( plist, sname) == 0){
				printf( "%s is not in the playlist %s\n", sname, plname);
				printf( "give a new song name: ");
				fgets(sname, sizeof(sname), stdin);
				check(sname);
//				printf("sname: %s\n", sname);
			}
            
            remove_song(plist, plname, sname);
            printf("song '%s' removed from playlist '%s'\n", sname, plname);
            
        }else if (strcmp(cmd, "shuffle") == 0) {
            
            char plname[256];
            printf("give playlist name: ");
            fgets(plname, sizeof(plname), stdin);
            check(plname);
            
            if (strcmp(plname, "library") == 0) {
                char* s = shuffle(list);
                play_song(s);
            }else {
                while( isPlaylist( plname) == 0){
                    printf( "%s is not a valid playlist\n", plname);
                    printf( "give a new playlist: ");
                    fgets(plname, sizeof(plname), stdin);
                    check(plname);
//                    printf("plname: %s\n", plname);
                }
                
                for( int i = 0; playlistf[i] != NULL; i++){
                    if( strcmp( playlistf[i], plname) == 0)
                        iOfplist = i;
                }
                
                char* s = shuffle(playlists[iOfplist]);
                play_song(s);
            }
            
        }else printf("command not found\n");
    }
}

int main(int argc, char *argv[] ) {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
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
