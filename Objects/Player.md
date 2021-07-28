# Player Documentation

## Description:

*Used for rendering the Pacman Player on the screen and handeling the game logic for pacman*

## Methods

HandleDisplay: 

    - Handles the rendering of the pacman onto the window screen.

    - Handles which spritesheet object, stored in a 2-D vector of GameObjects, to render specified by the direction and the fps.

HandleEventListener:

    - Utilizes SDL to interface the user with the pacman's direction

HandleMovement:

    - Utilizes Collision detections to move the Pacman sprite in its direction

    - Calls HasCollided method

HandleReset: 

    -Used by Game Object when resetting the player object to it's original location

HasCollided: [param] : *short storing player dir*

    -[return]: *boolean indicating whether player collided or not*

## Getters

IsEnergized:

    - [return]: *boolean indicating whether player ate energizer*

GetXPos:

    - [return]: *int storing player's x position*

GetYPos:

    - [return]: *int storing player's y position*

GetDir:

    - [return]: *int storing player's direction*

GetScore:

    - [return]: *int storing player's score*

## Setters

SetEnergized:

    -[param]: *bool storing value to set energized to*

SetAIndx:

    -[param]: *int storing value to set a_indx to*

AddScore:

    -[param]: *int storing value to add to score*