#include "library.h"

int main(){

	printf("\nMaking library file\n");
	struct song_node* list = NULL;
	list = getMP3names(list);
	printf("printing...\n");
    print_list(list);
	printf("-------------------------\n");
	
	 printf("\nTesting make_playlist\n");
	 char songs[100];
	 struct song_node* pl = NULL;
	 make_playlist( songs, "songs");
	 printf( "playlist %s made\n", songs);
	 
	 char rand[100];
	 struct song_node* pll = NULL;
	 make_playlist( rand, "library"); //should prompt for a new name; rename random
	 printf( "playlist %s made\n", rand);
	 printf("-------------------------\n");

	 printf("\nTesting add_song\n");
	 pl = add_song( list, pl, songs, "journey_by_the_moonlight");
	 pl = add_song( list, pl, songs, "la_vaguelette");
	 pl = add_song( list, pl, songs, "the_magic_8");
	 pl = add_song( list, pl, songs, "camelia"); //should prompt for a new name; use "da_capo"
	 pl = add_song( list, pl, songs, "the_reason_why");
	 pl = add_song( list, pl, songs, "rubia");
	 print_list( pl);
	 printf("-------------------------\n");
	 
//	 printf("\nTesting remove_song\n");
//	 list = remove_song( list, pl, "rubia");
//	 print_list( list);
//	 printf("-------------------------\n");

//	 printf("\nTesting play_song\n");
//	 play_song( "da_capo");

//	 printf("\nTesting play_playlist\n");
//	 play_playlist( "songs");
	
	
	printf("\nTesting free_list\n");
	list = free_list( list);
	printf("list after free_list: [ ");
	print_list( list);
	printf(" ]\n");
	printf("-------------------------\n");
	pl = free_list( pl);
	pll = free_list( pll);
}

