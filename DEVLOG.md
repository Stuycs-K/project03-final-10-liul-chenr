# Dev Log:

## Regina

### 2024-01-04 - Basic implentation (~1hr)
-  Convert songs to mp3 files and put them into a folder called "music_library"
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

### 2024-01-09 - Mainly working on implementing user commands (~2hrs)
- Shuffle works
- More bugs with getMP3names when reruning client; fixed
- Trying to implement signals; was trying to find a way to pause song (still working on it)
- Subservers and users exchange pid to make sure that they connected
- Added some commands that user can use, still need further testing
- Made a method for listing all commands for user reference; type "see commands" into user input

### 2024-01-10 - Fixing Mac issue (~3hrs)
- Mainly trying to fix problem with mac not being able to run some of the methods properly but WSL could; still fixing so that "add song to playlist" command runs properly
- Added more user commands; added remove playlist to remove the playlist if it exists
- Tested what we have so far on lab machine; it works, just not on mac for some reason

### 2024-01-11 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-12 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-15 - Brief description
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

### 2024-01-08 - Worked on remove_song and testing
- Worked on fixing stack smashing with Regina (~20 min)
- Created remove_song function which takes in a linked list version of a playlist, playlist name, and song name, removes the song from the linked list and file under the playlist name (~20 min)
- Added more songs to music_library (~10 min)
- Tested all library functions (modified add_song to check if a song is in the music library and fixed remove_song) (~20 min)

### 2024-01-09 - Implementation of semaphores
- Modified shuffle() to return a string instead of a struct song_node. (~5 min)
- Discussed with Regina on how to implement music library into a server client format (mainly on how to implement "public playlists") (~20 min)
- Started implementing semaphores into server.c and client.c, need further testing (~30 min)

### 2024-01-10 - Further additions to library.c and modifications to user.c
- Figured out the issue with "add song to playlist" with Regina on her branch (~30 min)
- Updated my own branch to match Regina's (~5 min)
- Made a isPlaylist function to check if a playlist given by the user already exist. (~10 min)
- Made a remove_playlist function, which removes the playlist file and frees the struct song_node* associated with it. (~10 min)
- Modified make_playlist so that making library.txt when getMP3names wouldn't prompt the user for a new playlist name. Might be modified again later. (~10 min)
- Modified "make playlist" so that when a playlist already exist, the user will be prompted for a new playlist. It also adds the name of the playlist to an array that'll keep track of the playlists made. (~10 min)
- Modified "add song to playlist" using what I discussed with Regina earlier in class. Using the array of playlist names, we can keep track of which index in playlists belong to which playlist. Also added two while loops, one will prompt the user for another song if the song doesn't exist in the library and the other will prompt the user for another playlist if the playlist didn't exist. (~10 min)

### 2024-01-11 - Pipes and select
- Added "play playlist" into user.c. (~10 min)
- Modified "make playlist" to ask the user if they want to make a public or private playlist. The name of the playlist getting made is then sent to the server. (~5 min)
- Working on implementing pipes between the server and its subservers using select. For "public playlists" we want the user to send the name of the playlist (and any songs they add to it) to the subserver connected to it. Then the subserver will send the playlist to the main server, which will then keep track of each public playlist each user makes. The server is then supposed to send the information about each playlist to the other subservers, which would then send the information to their users. Work in progress, I'm trying to figure out how select works with pipes. (~1 hour)

### 2024-01-12 - Brief description
Expanded description including how much time was spent on task.

### 2024-01-15 - Brief description
Expanded description including how much time was spent on task.
