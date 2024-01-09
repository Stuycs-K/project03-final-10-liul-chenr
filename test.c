#include "library.h"

int main(){

	struct song_node* list = NULL;
	
    
// printf("\nTesting free_list\n");
// list = free_list( list);
// printf("list after free_list: [ ");
// print_list( list);
// printf(" ]\n");
// printf("-------------------------\n");

	list = getMP3names(list);
//    printf("printing...\n");
    print_list(list);
	
	 printf("\nTesting make_playlist\n");
	 char pl[100];
	 make_playlist( pl, "songs");
	 printf( "playlist %s made\n", pl);
	
	 printf("\nTesting add_song\n");
	 list = add_song( list, pl, "da_capo");
	 list = add_song( list, pl, "journey_by_the_moonlight");
	 list = add_song( list, pl, "la_vaguelette");
	 list = add_song( list, pl, "lingering_blossom");
	 list = add_song( list, pl, "rubia");
	 print_list( list);
	 printf("-------------------------\n");
	 
//	 printf("\nTesting remove_song\n");
//	 list = remove_song( list, pl, "rubia");
//	 print_list( list);
//	 printf("-------------------------\n");

	 printf("\nTesting play_song\n");
	 play_song( "da_capo");

//	 printf("\nTesting play_playlist\n");
//	 play_playlist( "songs");
	
	list = free_list( list);
}

