#include "library.h"

int main(){
	
	struct song_node* list = NULL;
	
	printf("\nTesting order\n");
	list = order( list, "fish in a birdcage");
	list = order( list, "our last summer");
	list = order( list, "waterfall");
	list = order( list, "chiquitita");
	list = order( list, "before summer");
	list = order( list, "angeleyes");
	list = order( list, "pass on");
	list = order( list, "9 to 5");
	list = order( list, "¿viva la gloria?");
	list = order( list, "american idiot");
	list = order( list, "21 guns");
	list = order( list, "electric love");
	list = order( list, "bang!");
	list = order( list, "3 o'clock things");
	list = order( list, "1997");
	list = order( list, "1984");
	list = order( list, "cold cold man");
	list = order( list, "1984");
	print_list( list);
	printf("-------------------------\n");
	
	printf("\nTesting add_song\n");
	char pl[100];
	make_playlist( pl, "songs");
	list = add_song( list, pl, "animal");
	print_list( list);
	printf("-------------------------\n");
	
	printf("\nTesting free_list\n");
	list = free_list( list);
	printf("list after free_list: [ ");
	print_list( list);
	printf(" ]\n");
	printf("-------------------------\n");
}