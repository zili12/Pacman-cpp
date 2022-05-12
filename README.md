# Pacman-cpp
Pacman game written by Ron Zilberberg

The game will search in the file directory for files contains ".screen" and then convert them into game screens, Then it will run all the screens available or until the player lost.
You can choose to play only specific file by name.

The game can also run from the cmd and has 3 advanced modes: -save, -load, -load[-silent]:

In the -save mode there is a menu and the game is regular, except that all the entities moves are saved into files. Each new game overrides the files of the previous game.

In the -load mode there is no menu, it just run the loaded game as is from the files we saved from playing in save mode, It ignores user inputs.

The -silent option is relevant only for load, The game shall run without printing to screen and just testing that the actual result corresponds to the expected result, with a proper output to screen (test failed / passed). In this mode the program run way faster. 



