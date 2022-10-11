# Cub3D
Cub3D is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It's aim is to explore ray-casting. The goal is to make a dynamic view inside a maze, in which the player will have to find their way.
this game is written in C, and uses the "miniLibX", a graphic library of 42 Network.

## Basic requirements
* The program displays the image in a window and respects the following rules:
  * The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
  * The W, A, S, and D keys must allow you to move the point of view through the maze.
  * Pressing ESC must close the window and quit the program cleanly.
  * Clicking on the red cross on the window’s frame must close the window and quit the program cleanly
* The program must take as a first argument a scene description file with the .cub extension.
  * The map must be composed of only 6 possible characters: 0 for an empty space, 1 for a wall, and N,S,E or W for the player’s start position and spawning orientation.
  * The map must be closed/surrounded by walls, if not the program must return an error.
  * Except for the map content, each type of element can be separated by one or more empty line(s).
  * Except for the map content which always has to be the last, each type of element can be set in any order in the file.
  * Except for the map, each type of information from an element can be separated by one or more space(s).
  * The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. You must be able to parse any kind of map, as long as it respects the rules of the map.
* Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as:
  * North texture: NO ./path_to_the_north_texture
    * identifier: NO
    * path to the north texure
  * South texture: SO ./path_to_the_south_texture
    * identifier: SO
    * path to the south texure
  * West texture: WE ./path_to_the_west_texture
    * identifier: WE
    * path to the west texure
  * East texture: EA ./path_to_the_east_texture
    * identifier: EA
    * path to the east texure
  * Floor color: F 220,100,0
    * identifier: F
    * R,G,B colors in range [0,255]: 0, 255, 255
  * Ceilling color: C 220,100,0
    * identifier: C
    * R,G,B colors in range [0,255]: 0, 255, 255
* If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.

## Bonus requirements
* Wall collisions.
* A minimap system.
* Doors which can open and close.
* animated sprite.
* Rotate the point of view with the mouse.

## Usage
This program has an additional difficulty to compile, as it doesn't use a standar C graphic library, but one that 42 uses. In order to compile, you must do the following:
1. If you are on Mac or Linux, you can just compile with the Makefile (thanks to [ManMartin](https://github.com/Manmartin) for the help on how to make this makefile). There will be warnings because of the Minilibx library:
	* make: it compiles directly
    * make re: if the project is already compiled, it does it again
    * make clean. Deletes all .o files but the executables remain
    * make fclean: deletes all .o files and the executables
2. In windows it's more complicated. Refer to [this guide](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#compilation-on-macos) in order to be able to compile
