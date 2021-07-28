# Pacman Clone [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/Mattli8312/Pacman2.0/blob/master/LICENSE)

# Introduction

- Based off of the classic arcade video game designed and created by Toru Iwatani, this project was designed and implemented in C++ using the Simple DirectMedia Layer API. The purpose of this project was to explore the use of this API in designing and rendering a pacman clone. To stay true to the original, this clone contains all the features, including scoring, ghost movement, and frame-rates of entities (i.e. the pacman and the ghost);

# Documentation

- [Game]()
- [Player](https://github.com/Mattli8312/Pacman2.0/blob/master/Objects/Player.md)
- [Ghosts](https://github.com/Mattli8312/Pacman2.0/blob/master/Objects/Ghost.md)
- [MazeGraph](https://github.com/Mattli8312/Pacman2.0/blob/master/src/MazeGraph.md)

# Installation/Running

First you will want to install SDL2.0, used for running the game window, SDLImage, for rendering sprites, and SDlttf, for rendering text
    - *Note: Make sure you download and install the 32-bit version, the 64-bit version will not run*

Next, clone this repository into any directory/folder you would like: preferably your C-drive.

```
$ cd /FolderName
$ git clone https://github.com/Mattli8312/Pacman2.0.git
```

If you want to build and run this program, you can use an IDE such as VS or CodeBlocks. You will need to set up the targets for the compiler and
the linker if you choose to do so. 

If you do so, it may be easier to create a Dev directory in your local folder to store the SDL dependencies in and then simply add the necessary linkers and compilers for your IDE. 

``` 
$ cd /LocalCDrive(Username)
$ mkdir DevFolder
$ cp -R SDL2 DevFolder
$ cp -R SDL2_Img DevFolder
$ cp -R SDL2_ttf DevFolder
```

# Potential Bugs

-Some bugs

# TroubleShooting

- @Todo

# License

- @Todo

# Open Source

- @Todo