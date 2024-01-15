# Final Project Proposal

## Group Members:

Regina Chen, Lala Liu
       
# Intentions:

Making a playable music library that can play mp3 files.
    
# Intended usage:

Users will be shown a list of mp3 files from the music library and using a command to choose a song of their choice to play in the terminal through the installed mpg123 audio player. There will be other commands that the user can use such as create playlists, remove playlists/songs, listening to a randomly chosen song from a given playlist, etc. If a song can't be found, it will ask the user to choose another song. 
  
# Technical Details:

We will be working with mp3 files and finding information about these files to create playlists made out of linked lists. The lists of songs will be written into their individual files corresponding to their playlist names. The playlists will be stored by allocating memory. We will also be using sockets so that multiple users can connects. Newly created playlists will be added into an array to keep track of all the existing playlists. This is also for users to know which playlists they have access to and can proceed accordingly using the different commands. Commands include shuffle, play song, play playlists, display, remove songs, remove playlists, etc.
    
# Intended pacing:

- Adding mp3 songs to library - Regina, 1/4
- Set up server and client connection - Regina 1/5
- Set up library commands (file of song names, add/remove, playlist making, etc) - Lala for now, 1/5
- Testing play feature - Lala, 1/8
- Signals - Lala, 1/8
- Forking - Regina, 1/8
- Public playlist - tbd, 1/9-1/10
- Collaboration playlist - tbd if we get everything as intended (extra?)
