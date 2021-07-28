# Player Documentation

## Description:

*Used for rendering the Ghosts on the screen and handeling the game logic for pacman*

## Methods

InitializeGhost:

    -Used for initializing members such as the 2d ghost sprite sheet, state, etc.

HandleDisplay: 

    - Handles the rendering of the ghost onto the window screen.

    - Handles which spritesheet object, stored in a 2-D vector of GameObjects, to render specified by the direction and the fps.

Handle Direction: [param]: *ints containing x and y target, and boolean indicating whether we're selecting directions or not*

    - When we reach a node of the graph stored in MazeGraph(indicated by '+' character), the ghost will choose a direction which will move the ghost the closest in Euclidean distance to the target.

HandleMovement:

    - Moves the ghost sprite in it's direction. Doesn't utilize collision detection. 

    - Can teleport between two tunnels like pacman

HandleSpeedChange: [param]: *int containing new speed value*

    - Movement of all entities in based on modular arithmetic, hence, this method ensures that shifting the velocity won't affect this by shifting the position before shifting the velocity if necessary.

HandleReset:

    -Resets Ghost to original positions and states

## States

Init:
    
    - Movement is soley up and down during the init state.

Scatter:

    - All Ghosts target systems are set to the four corners of the maze.

    - Calls Handledirection

Frighten:

    - Directions of ghosts are randomized. Speed is reduced to 2.f

Eaten:

    - Ghosts target the center/base of the maze. Speed in increased to 6.f

## Getters

GetName:

    - [return]: *string with ghost's name*

GetXPos:

    - [return]: *int storing player's x position*

GetYPos:

    - [return]: *int storing player's y position*

IsFrightened:

    - [return]: *bool indicating if ghost's state is FRIGHT*

IsEatened:

    - [return]: *bool indicating if ghost's state is EATEN*

IsChase:

    - [return]: *bool indicating if ghost's state is CHASE*

IsInit:

    - [return]: *bool indicating if ghost's state is INIT*

IsScattererd:

    - [return]: *bool indicating if ghost's state is SCATTER*

## Setters

SetStateFright:

    - Sets state_ value equal to FRIGHT

SetStateEat:

    - Sets state_ value equal to EAT

SetStateChase:

    - Sets state_ value equal to CHASE

## Virtual Method

TargetSystem: [param]: *vector of points*

    - Depending of the ghost type, this method will alter it's target system based on the pacman's location and the other ghosts' locations. 