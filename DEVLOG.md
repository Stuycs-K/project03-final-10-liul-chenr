# Dev Log:

## Regina

### 2024-01-04 - Basic implentation (~1hr)
-  Convert songs to mp3 files and put them into a folder 
-  Get the socket and fork from lab16 and modify it a bit (will modify logic later on)
-  researching on how to install a music player that works on all devices (sox maybe but don't know how to install on lab machine, don't think we can install?)

### 2024-01-05 to 2024-01-07 - Worked on library (~3hrs)
-  Fixed add_song so that it add the song name to the list and then all to a .txt file
-  Created and fixed getMP3names which takes the .mp3 files and turn them into a list of structs. Took some time to get rid of the .mp3 extension when adding it to the list.
-  Tested methods

### 2024-01-08 - Still working on library methods (~2.5hrs)
-  Fixed the execvp part of add_song so that it works on macOS by adding a NULL at the end of cmdargv
-  Added more songs to the music library
-  Started on the shuffle method which chose a song randomly from a playlist and play it
-  Fixed getMP3names so that it can add the .mp3 file names into the .txt file "library"

### 2024-01-09 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-10 - Brief description
Expanded description including how much time was spent on task.

## Lala

### 2024-01-04 - Started the basic functions of the library (~1 hour)
-  Took some of the functions from project_one (print_list, insert_front, order, free_list) and modified them to fit our version of music library, which mainly involved taking out artist since we don't plan on using it for now. 
-  Created an add_song function which takes in a linked list version of the user's playlist, the name of the playlist, and the name of the song they want to add. The song gets added to the linked list, and then the linked list gets written into a file with the name of the playlist.
-  Created an extension function which takes in a string buffer, a name and a file type. This is mainly to concatenate .txt (or later on .mp3) onto the end of the string the user inputs.

### 2024-01-05 to 2024-01-07 - Worked on play functions of the library
- Looked at music players that can work with the lab machines with Regina. (01/05, ~11 min)
- Created a make_playlist function which takes in a char buffer and a playlist name, and creates a file with that name. If the file already exist, the user will be prompted for a new name. (01/05, ~30 min)
- Created a play_song function which takes in a song name and plays it using mpg123, execvp and forking. (01/06, ~15 min)
- Found an issue with add_song, attempted to fix it but wasn't able to. Regina took over it on 01/07. (01/06, ~25 min)
- Placed comments on the functions I did to make it more readable. (01/07, ~5 min)
- Created a play_playlist function which takes in a playlist name, reads the file with that name and calls play_song for every line it reads (01/07, ~10 min) 
- Stack smashing detected while testing play_playlist. play_song also has stack smashing detected. Will work on it Monday (01/07, ~5 min)

### 2024-01-08 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-09 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-10 - Brief description
Expanded description including how much time was spent on task.
