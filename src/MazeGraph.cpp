#include "MazeGraph.h"
#include <fstream>
#include <iostream>
#include <SDL.h>
#include "Game.h"

std::vector<std::vector<char>> MazeGraph::graph;
std::vector<std::vector<short>> MazeGraph::pellets;
unsigned MazeGraph::x_o;
unsigned MazeGraph::cell_size;
unsigned MazeGraph::width;
unsigned MazeGraph::height;

MazeGraph::MazeGraph()
{
    //ctor
    cell_size = 20;
    width = 0;
    height = 0;
    x_o = 0;
}

MazeGraph::~MazeGraph()
{
    //dtor
}

void MazeGraph::ParseGraphFromFile()
{
    //Erase previous graph
    ClearMaze();
    //Grab Maze.txt file
    std::fstream fin;
    fin.open("src/Maze.txt");
    //debugging window
    if(!fin){
        std::cout<<"[fileparsing]: Error with opening file"<<std::endl;
    }
    else{
        std::cout<<"[fileparsing]: No Errors found"<<std::endl;
    }
    //Read data from file
    std::string line, temp;
    while(fin >> temp){
        getline(fin, line);
        std::vector<char> temp;
        for(unsigned i = 0; i < line.length(); i++){
            if(line[i] != ' ')
                temp.push_back(line[i]);
        }
        graph.push_back(temp);
    }

    /**Now we have to Process the pellets**/
    for(unsigned i = 0; i < graph.size(); i++){
        std::vector<short> temp;
        for(unsigned j = 0; j < graph[0].size(); j++){ /**0 means empty, 1 means pellet, 2 means power pellet**/
            if(graph[i][j] == '.' || graph[i][j] == ',' || (i > 8 && i < 20 && j > 6 && j < 21)) temp.push_back(0);
            else if((!(i-23) || !(i-4))&&(!(j-1)||!(j-26))) temp.push_back(2);
            else temp.push_back(1);
        }
        pellets.push_back(temp);
    }
    height = graph.size() * cell_size;
    width = graph[0].size() * cell_size;
}

void MazeGraph::PrintGraph()
{
    for(auto g: graph){
        for(auto c: g){
            std::cout<<c<<" ";
        }
        std::cout<<std::endl;
    }
}

void MazeGraph::RenderMaze()
{
    cell_size = 24;
    x_o = 400 - graph[0].size()*cell_size/2;
    SDL_Rect desrect;
    for(unsigned i = 0; i < graph.size(); i++){
        for(unsigned j = 0; j < graph[0].size(); j++){
                /**First render the tile map**/
                if(graph[i][j] == '.')
                    SDL_SetRenderDrawColor(Game::renderer, 0, 128, 255, 255);
                if(graph[i][j] == '*')
                    SDL_SetRenderDrawColor(Game::renderer, 255, 192, 203, 255);
                unsigned delx = x_o + j * cell_size, dely = i * cell_size;
                desrect = {(int)(delx), (int)(dely), (int)(cell_size), (int)(cell_size)};
                SDL_RenderFillRect(Game::renderer, &desrect);
                /**Then render the food**/
                bool is_food = true;
                switch(pellets[i][j]){
                    case 1:
                        desrect = {(int)(delx + cell_size/8 *3), (int)(dely + cell_size/8 * 3), (int)(cell_size/4), (int)(cell_size/4)};
                        SDL_SetRenderDrawColor(Game::renderer, 255,255,255,255);
                        break;
                    case 2:
                        desrect = {(int)(delx + cell_size/4), (int)(dely + cell_size/4), (int)(cell_size/2), (int)(cell_size/2)};
                        SDL_SetRenderDrawColor(Game::renderer, 255,255,255,255);
                        break;
                    default:
                        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
                        is_food = false;
                        break;
                }
                if(is_food){
                    SDL_RenderFillRect(Game::renderer, &desrect);
                    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
                }
        }
    }
}

void MazeGraph::ClearMaze()
{
    while(graph.size()){
        graph.pop_back();
    }
}
