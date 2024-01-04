# Final Project Proposal

## Group Members:

Regina Chen, Lala Liu
       
# Intentions:

Making a playable music library that can play mp3 files.
    
# Intended usage:

Users will be shown a list of mp3 files avaliable in a folder organized aphabetically by song title. Then the user will input a song title and then the shell will play that song on the terminal. If the song can't be found, the shell will ask the user to choose another song. The user can also make their own "playlists," made out of songs from the avliable mp3 files, and play a song from there. The user can also play a mp3 file by random.
  
# Technical Details:

We will be working with mp3 files and using sockets with a main server which will fork subservers when users connect. The subserver will be listening to the commands of its user and process accordingly. We will also be using allocating memory to make playlists (files) with an array of mp3 names in each one; the array will be size of the total number of mp3 files to keep it consistant. Users can add or remove songs from the playlists that they have access to by reading the array of the file (playlist), modifying it, and writing it back into the file. There is also going to be a command for choosing a mp3 file by random (shuffle). Forking and execvp will be used to play the songs through the terminal. Signal handling will also be added to pause, play, and skip the song.
    
# Intended pacing:

- Adding mp3 songs to library - Regina, 1/4
- Set up server and client connection - Regina 1/5
- Set up library commands (file of song names, add/remove, playlist making, etc) - Lala for now, 1/5
- Testing play feature - Lala, 1/8
- Signals - Lala, 1/8
- Forking - Regina, 1/8
- Public playlist - tbd, 1/9-1/10
- Collaboration playlist - tbd if we get everything as intended (extra?)
