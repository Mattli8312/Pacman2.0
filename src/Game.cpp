#include "Game.h"
#include "Player.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

#include <SDL_ttf.h>

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
    maze = new MazeGraph;
    maze->ParseGraphFromFile();
    maze->RenderMaze();
    player = new Player(MazeGraph::x_o + MazeGraph::cell_size * 12, MazeGraph::cell_size * 23, MazeGraph::cell_size * 3 / 2, MazeGraph::cell_size * 3 / 2);
    blinky = new Blinky(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::cell_size * 11, 32, 32, "Blinky");
    pinky = new Pinky(MazeGraph::x_o + MazeGraph::cell_size * 13, MazeGraph::cell_size * 13, 32, 32, "Pinky");
    inky = new Inky(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::cell_size * 13, 32, 32, "Inky");
    clyde = new Clyde(MazeGraph::x_o + MazeGraph::cell_size * 15, MazeGraph::cell_size * 13, 32, 32, "Clyde");
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
    std::vector<Ghost*> ghosts = {blinky};//, pinky, inky, clyde};
    if(player->IsEnergized()){
        for(auto g: ghosts){
            if(g->IsChase() || g->IsScattered()){
                g->SetStateFright();
                g->HandleSpeedChange(2);
            }
        }
        player->SetEnergized(false);
    }
    else{
        blinky->TargetSystem({player->GetXPos(), player->GetYPos()});
        //pinky->TargetSystem({player->GetXPos(), player->GetYPos(), player->GetDir()});
        //inky->TargetSystem({player->GetXPos(), player->GetYPos(), blinky->GetXPos(), blinky->GetYPos()});
        //clyde->TargetSystem({player->GetXPos(), player->GetYPos()});
    }
    player->HandleEventListener();
    player->HandleMovement();
    for(auto g: ghosts){
        g->HandleMovement();
    }
}

void Game::Render()
{
    SDL_RenderClear(renderer);
    /**Clear Previous frame**/
    maze->RenderMaze();
    player->HandleDisplay();
    blinky->HandleDisplay();
    pinky->HandleDisplay();
    inky->HandleDisplay();
    clyde->HandleDisplay();
    RenderText();
    /**Update frame**/
    SDL_RenderPresent(renderer);
}

void Game::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::RenderText(){
        //this opens a font style and sets a size
    if(TTF_Init() == -1){
        std::cout<<"[TTF]: Init Failed"<<std::endl;
    }
    std::string msg("SCORE: " + std::to_string(player->GetScore()));
    TTF_Font* Sans = TTF_OpenFont("src/arial/arial.ttf", 40);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, &msg[0], {255,255,255});
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect = {20,20,100,20};
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
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

void Game::HandleCollision()
{
    std::vector<Ghost*> ghosts = {blinky, inky, pinky, clyde};
    for(auto g: ghosts){
        if(std::abs(player->GetXPos() - g->GetXPos()) < (int)MazeGraph::cell_size/4){
            if(std::abs(player->GetYPos() - g->GetYPos()) < (int)MazeGraph::cell_size/4){
                if(!g->IsFrightened() && !g->IsEatened()){
                    std::cout<<"Collided"<<std::endl;
                }
                else if(g->IsFrightened()){
                    SDL_Delay(500);
                    g->SetStateEat();
                    std::cout<<"Eatened"<<std::endl;
                }
            }
        }
    }
}
