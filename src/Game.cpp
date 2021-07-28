#include "Game.h"
#include "Player.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

#include <SDL_ttf.h>

/**Entities**/
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
    blinky = nullptr;
    pinky = nullptr;
    inky = nullptr;
    clyde = nullptr;
    maze = nullptr;

    state_ = INIT;
}

Game::~Game()
{
    /**@todo**/
    ResetPlayers();
}
void Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow("PacmanClone", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
    }
    InitializePlayers();
    /**Testing Pathfinding**/
    //maze->PrintGraph();
    running = true;
}

void Game::RunApplication(){
    switch(state_){
        case GAME:
            {
                EventListener();
                HandleCollision();
                Update();
                Render();
                break;
            }
        case FINISH:
            {
                if(fps > 100){
                    state_ = RESET;
                    fps = 0;
                }
                else{
                    Render(true);
                    fps++;
                }
                break;
            }
        case RESET:
            {
                std::vector<Ghost*> ghosts = {blinky, inky, clyde, pinky};
                maze->ParseGraphFromFile();
                player->HandleReset();
                for(auto g: ghosts)
                {
                    g->HandleReset();
                }
                state_ = INIT;
                break;
            }
        case INIT:{
                Render();
                SDL_Delay(3000);
                state_ = GAME;
                break;
            }
        default: break;
    }
}

void Game::ResetPlayers(){
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

void Game::InitializePlayers(){
    maze = new MazeGraph;
    maze->ParseGraphFromFile();
    maze->RenderMaze(false);
    player = new Player(MazeGraph::x_o + MazeGraph::cell_size * 13, MazeGraph::y_o + MazeGraph::cell_size * 23, MazeGraph::cell_size * 3 / 2, MazeGraph::cell_size * 3 / 2);
    blinky = new Blinky(MazeGraph::x_o + MazeGraph::cell_size * 13, MazeGraph::y_o + MazeGraph::cell_size * 11, 32, 32, "Blinky");
    pinky = new Pinky(MazeGraph::x_o + MazeGraph::cell_size * 13, MazeGraph::y_o + MazeGraph::cell_size * 13, 32, 32, "Pinky");
    inky = new Inky(MazeGraph::x_o + MazeGraph::cell_size * 11, MazeGraph::y_o + MazeGraph::cell_size * 13, 32, 32, "Inky");
    clyde = new Clyde(MazeGraph::x_o + MazeGraph::cell_size * 15, MazeGraph::y_o + MazeGraph::cell_size * 13, 32, 32, "Clyde");
    blinky->InitializeGhost();
    pinky->InitializeGhost();
    inky->InitializeGhost();
    clyde->InitializeGhost();
}

void Game::Update()
{
    /**Handle the fright time**/
    std::vector<Ghost*> ghosts= {blinky, pinky, inky, clyde};
    /**Handle Fright time**/
    if(Ghost::fright_time < 400){
        Ghost::fright_time--;
    }
    if(Ghost::fright_time <= 0){
        for(auto g: ghosts) {
            if(!g->IsEatened()){
                g->SetStateChase();
            }
        }
        Ghost::fright_time = 400;
    }
    /**Handle entity movements**/
    if(player->IsEnergized()){
        Ghost::fright_time = 399; /**Begin the offset**/
        ghost_points = 200;
        for(auto g: ghosts){
            if(g->IsScattered() || g->IsChase()){
                g->SetStateFright();
                g->HandleSpeedChange(2);
            }
        }
        player->SetEnergized(false);
    }
    else{
        blinky->TargetSystem({player->GetXPos(), player->GetYPos()});
        pinky->TargetSystem({player->GetXPos(), player->GetYPos(), player->GetDir()});
        inky->TargetSystem({player->GetXPos(), player->GetYPos(), blinky->GetXPos(), blinky->GetYPos()});
        clyde->TargetSystem({player->GetXPos(), player->GetYPos()});
    }
    player->HandleEventListener();
    player->HandleMovement();
    for(auto g: ghosts){
        g->HandleMovement();
    }
    /**Handle completion of level**/
    if(MazeGraph::food_count < 1){
        std::cout<<"Lvl complete"<<std::endl;
        state_ = FINISH;
        player->SetAIndx(2);
    }
}

void Game::Render(bool complete, bool eaten, std::string ghostname)
{
    std::vector<Ghost*> ghosts = {blinky, pinky, inky, clyde};
    SDL_RenderClear(renderer);
    /**Clear Previous frame**/
    /**
    *Render entities and Maze
    **/
    maze->RenderMaze(complete);
    if(!complete){
        for(auto g: ghosts)
            if(ghostname != g->GetName())
                g->HandleDisplay();
    }
    if(!eaten)
        player->HandleDisplay();
    else{
        std::string pts(std::to_string(ghost_points));
        RenderText(&pts[0], player->GetXPos(), player->GetYPos(), 20, 20);
    }
    /**
    *Render Text
    **/
    std::string msg("1UP            " + std::to_string(player->GetScore()));
    std::string hs_msg("HIGH SCORE     89260");
    RenderText(&msg[0],(int)MazeGraph::x_o,10,200,20);
    RenderText(&hs_msg[0], 420, 10, 300, 20);
    /**Update frame**/
    SDL_RenderPresent(renderer);
}

void Game::Clear()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::RenderText(const char* txt, int x, int y, int w, int h){
        //this opens a font style and sets a size
    if(TTF_Init() == -1){
        std::cout<<"[TTF]: Init Failed"<<std::endl;
    }
    TTF_Font* Sans = TTF_OpenFont("src/arial/arial.ttf", 60);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, &txt[0], {255,255,255});
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect Message_rect = {x,y,w,h};
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
                    /**@todo!**/
                    Render(true);
                    SDL_Delay(500);
                    state_ = RESET;
                }
                else if(g->IsFrightened()){
                    Render(false, true, g->GetName());
                    SDL_Delay(500);
                    player->AddScore(ghost_points);
                    g->SetStateEat();
                    g->HandleSpeedChange(6);
                    ghost_points *= 2;
                }
            }
        }
    }
}
