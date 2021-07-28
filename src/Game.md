# Game Documentation

## Description:

*Used for Running the Game application*

## Methods

Init:

    - Initializes Gamescreen window and other SDl textures
    
    - Initializes TTF font

Render: [param]: *booleans indicating whether to freeze the screen or not*

    - Render Different Components and entities onto the windowscreen. (Pacman, Ghosts, Maze, Texts, etc.)

Clear:

    - Destroys and frees the SDL_WindowScreen: Called after destructor.

Update:

    - Updates the locations of the entities

EventListener:

    -Handles closing of a window and other interrupts

RenderText: [param] : *string ptr to text, and ints storing locations and size*

    -Renders text in certains locations with certain sizes

RunApplication:

    -Handles State logic: Primary control method of the Game Object

ResetPlayers:

    -Destorys previous entity objects.

IntiializePlayers:

    - Allocates new entity objects for entity pointers to point to.

HandleCollision():

    - Handle state response for collisions between pacman and ghosts

## Getter

IsRunning:
    - [return] : *bool indicating whether the Game object is running or not*
