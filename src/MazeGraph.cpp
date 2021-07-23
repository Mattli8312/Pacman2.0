#include "MazeGraph.h"
#include <fstream>
#include <iostream>
#include <SDL.h>
#include "Game.h"

std::vector<std::vector<char>> MazeGraph::graph;
std::vector<std::vector<short>> MazeGraph::visited;
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
            if(line[i] != ' ') temp.push_back(line[i]);
        }
        graph.push_back(temp);
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
                if(graph[i][j] == '.')
                    SDL_SetRenderDrawColor(Game::renderer, 0, 128, 255, 255);
                if(graph[i][j] == '*')
                    SDL_SetRenderDrawColor(Game::renderer, 255, 192, 203, 255);
                unsigned delx = x_o + j * cell_size, dely = i * cell_size;
                desrect = {(int)(delx), (int)(dely), (int)(cell_size), (int)(cell_size)};
                SDL_RenderFillRect(Game::renderer, &desrect);
                SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        }
    }
}

void MazeGraph::ClearMaze()
{
    while(graph.size()){
        graph.pop_back();
    }
}
