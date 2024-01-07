#include "library.h"

int main(){
	
	struct song_node* list = NULL;
	
	// printf("\nTesting order\n");
	// list = order( list, "fish in a birdcage");
	// list = order( list, "our last summer");
	// list = order( list, "waterfall");
	// list = order( list, "chiquitita");
	// list = order( list, "before summer");
	// list = order( list, "angeleyes");
	// list = order( list, "pass on");
	// list = order( list, "9 to 5");
	// list = order( list, "¿viva la gloria?");
	// list = order( list, "american idiot");
	// list = order( list, "21 guns");
	// list = order( list, "electric love");
	// list = order( list, "bang!");
	// list = order( list, "3 o'clock things");
	// list = order( list, "1997");
	// list = order( list, "1984");
	// list = order( list, "cold cold man");
	// list = order( list, "1984");
	// print_list( list);
	// printf("-------------------------\n");
	
	printf("\nTesting make_playlist\n");
	char pl[100];
	make_playlist( pl, "songs");
	printf( "playlist %s made\n", pl);
	
	printf("\nTesting add_song\n");
	list = add_song( list, pl, "da_capo");
	list = add_song( list, pl, "journey_by_the_moonlight");
	// list = add_song( list, pl, "la_vaguelette");
	// list = add_song( list, pl, "lingering_blossom");
	// list = add_song( list, pl, "rubia");
	print_list( list);
	printf("-------------------------\n");
	
	printf("\nTesting free_list\n");
	list = free_list( list);
	printf("list after free_list: [ ");
	print_list( list);
	printf(" ]\n");
	printf("-------------------------\n");
	
	// printf("\nTesting play_song\n");
	// play_song( "rubia");
}