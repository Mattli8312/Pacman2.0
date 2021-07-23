#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

Player * player;
Blinky * blinky;
Pinky * pinky;
Inky * inky;
Clyde * clyde;


SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
    window = nullptr;
    player = nullptr;
    maze = nullptr;
}

Game::~Game()
{
    /**@todo**/
    if(player) delete player;
    if(maze) delete maze;
    if(blinky) delete blinky;
    if(pinky) delete pinky;
    if(inky) delete inky;
    if(clyde) delete clyde;

    player = nullptr;
    maze = nullptr;
    blinky = nullptr;
    pinky = nullptr;
    inky = nullptr;
    clyde = nullptr;
}
void Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        //SDL_SetRenderDrawColor(renderer, 0,255,255,255);
    }
    if(!IMG_Load("Sprites/Pacman1.png")){
        printf("IMG load: %s \n", IMG_GetError());
    }
    if(!IMG_Load("Sprites/Pacman2.PNG")){
        printf("bullet load: %s \n", IMG_GetError());
    }
    maze = new MazeGraph;
    maze->ParseGraphFromFile();
    maze->RenderMaze();
    player = new Player(MazeGraph::x_o + MazeGraph::cell_size * 12, MazeGraph::cell_size * 23, MazeGraph::cell_size, MazeGraph::cell_size);
    blinky = new Blinky(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::cell_size * 11, 24, 24, "Blinky0");
    pinky = new Pinky(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::cell_size * 11, 24, 24, "Pinky0");
    inky = new Inky(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::cell_size * 11, 24, 24, "Inky0");
    clyde = new Clyde(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::cell_size * 11, 24, 24, "Clyde0");
    blinky->InitializeGhost();
    pinky->InitializeGhost();
    inky->InitializeGhost();
    clyde->InitializeGhost();
    /**Testing Pathfinding**/
    //maze->PrintGraph();
    running = true;
}

void Game::Update()
{
    player->HandleEventListener();
    player->HandleMovement();

    blinky->HandleMovement();
    pinky->HandleMovement();
    inky->HandleMovement();
    clyde->HandleMovement();
    blinky->TargetSystem({player->GetXPos(), player->GetYPos()});
    pinky->TargetSystem({player->GetXPos(), player->GetYPos(), player->GetDir()});
    inky->TargetSystem({player->GetXPos(), player->GetYPos(), blinky->GetXPos(), blinky->GetYPos()});
    clyde->TargetSystem({player->GetXPos(), player->GetYPos()});
}

void Game::Render()
{
    SDL_RenderClear(renderer);

    maze->RenderMaze();
    player->HandleDisplay();
    blinky->HandleDisplay();
    pinky->HandleDisplay();
    inky->HandleDisplay();
    clyde->HandleDisplay();

    SDL_RenderPresent(renderer);
}
void Game::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Game::EventListener()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT)
        running = false;
}

bool Game::IsRunning()
{
    return running;
}

