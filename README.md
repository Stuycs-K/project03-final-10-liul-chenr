[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/SQs7pKlr)
# Music Player

### Group Name: The Pandas
Group Members: Regina, Lala
       
### Project Description:

This is a music player that plays mp3 files through the terminal. It allows the user to connect to a server and interact with the program through a variety of commands.
  
### Instructions:

How does the user install/compile/run the program.

To install mpg123 audio player:
- for linux/WSL:
  - sudo apt-get install mpg123
- for macOS:
  - /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  - brew install mpg123

How does the user interact with this program?

Setup:
1. Open at least two terminals
2. 'make' or 'make compile' on any one terminal
3. './server' on one terminal
4. './user' on the other terminals
5. 'see commands' to see all avaliable commands

List of commands: 
- display playlists: show all avaliable playlists (including 'library' and any playlists created by user)
- display songs in playlist: user gives a playlist from the list of playlists and it will show all songs in that playlist
- play song: user chose a song from the list given and terminal will play it (press 'q' to exit song)
- play playlist: user chose a playlist from the list given and terminal will play through all the songs in it alphabetically (press 'q' to go to next song)
- create playlist: user input a new playlist name and it creates an empty playlist with that given name
- add song to playlist: user chose a playlist and gives a song name from the music library and it will add that song to the chosen playlist (note: if playlist or song name doesn't exist, it will ask user to input another name)
- remove playlist: user inputs a playlist name and it removes that playlist (it doesn't do anything if playlist doesn't exist)
- remove song from playlist: user inputs a playlist name and a song name and removes that song from the given playlist (it doesn't do anything if playlist or song doesn't exist)
- shuffle: user imputs a playlist name and it will chose a random song from that given playlist and play
