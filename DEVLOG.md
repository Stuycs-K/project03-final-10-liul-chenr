# Dev Log:

## Regina

### 2024-01-04 - Basic implentation (~1 hr)
-  Convert songs to mp3 files and put them into a folder 
-  Get the socket and fork from lab16 and modify it a bit (will modify logic later on)
-  researching on how to install a music player that works on all devices (sox maybe but don't know how to install on lab machine, don't think we can install?)

### 2024-01-05 - Worked on library (~ 3hrs)
-  Fixed add_song so that it add the song name to the list and then all to a .txt file
-  Created and fixed getMP3names which takes the .mp3 files and turn them into a list of structs. Took some time to get rid of the .mp3 extension when adding it to the list.
-  Tested methods

## Lala

### 2024-01-04 - Started the basic functions of the library (~1 hour)
-  Took some of the functions from project_one (print_list, insert_front, order, free_list) and modified them to fit our version of music library, which mainly involved taking out artist since we don't plan on using it for now. 
-  Created an add_song function which takes in a linked list version of the user's playlist, the name of the playlist, and the name of the song they want to add. The song gets added to the linked list, and then the linked list gets written into a file with the name of the playlist.
-  Created an extension function which takes in a string buffer, a name and a file type. This is mainly to concatenate .txt (or later on .mp3) onto the end of the string the user inputs.

### 2024-01-05 - Brief description
Expanded description including how much time was spent on task.
