# Final Project Proposal

## Group Members:

Regina Chen, Lala Liu
       
# Intentions:

Making a playable music library that can play mp3 files.
    
# Intended usage:

Users will be displayed with the list mp3 files avaliable in the folder organized aphabetically by song title. Then user input will input a song title and then the shell will play that song on the terminal. If the song can's be found, terminal will tell user to chose again. There's also going to be an option to chose a mp3 file by random.
  
# Technical Details:

We will be working with mp3 files and using sockets with a main server forking subservers when users connect. The subserver will be listening to the commands of its user and process accordingly. We will also be using allocating memory to make playlists (files) with an array of mp3 names in each one; array will be size of total mp3 to keep it consistant. Users can add or remove songs from the playlists that they have access to by reading the array of the file (playlist), modifying it, and write it back into file. There is also going to be a command for chosing a mp3 by random (shuffle). Signals will be added to pause, play, and skip the song.
    
# Intended pacing:

- Adding mp3 songs to library - Regina, 1/4
- Set up server and client connection - Regina 1/5
- Set up library commands (file of song names, add/remove, playlist making, etc) - Lala for now, 1/5
- Testing play feature - Lala, 1/8
- Signals - Lala, 1/8
- Forking - Regina, 1/8
- Public playlist - tbd, 1/9-1/10
- Collaboration playlist - tbd if we get everything as intended (extra?)
