# MazeGraph Documentation

## Description:

*Used for rendering the Pacman MazeGraph on the screen*

## Methods

ParseGraphFromFile:

    - Reads from Maze.txt file and stores graph structurein a 2-D vector of characters.
    - Also stores the location of the food pellets in a 2-D vector of shorts.

PrintGraph:

    -Method used for printing the 2-D graph vector to the console.
    
    -Mainly used for debugging

RenderMaze:

    - Used for rendering the maze onto the screen. 

RenderCellWell:

    - Renders four segments in North, South, East, and West of the center cell it is looking at.

    -Utilized by the RenderMaze method

ClearMaze:

    - Resets the graph and pellet structures to be empty.

    - Used by the ParseGraphFromFile method