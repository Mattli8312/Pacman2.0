#include "Clyde.h"
#include <math.h>

Clyde::Clyde(int x, int y, int width, int height, std::string ghostname)
{
    xpos = x;
    ypos = y;
    w = width;
    h = height;
    state_ = SCATTER;
    name = ghostname;

    scatter_i = 29; scatter_j = 26;
    scatter_time = 600;
    dir = 3, vel = 2;
}

Clyde::~Clyde()
{
    //dtor
    if(ghost) delete ghost;
    for(unsigned i = 0; i < GhostSheet.size(); i++){
        for(unsigned j = 0; j < GhostSheet[0].size(); j++){
            if(GhostSheet[i][j]) delete GhostSheet[i][j];
            GhostSheet[i][j] = nullptr;
        }
    }
    std::cout<<"Freed!"<<std::endl;
    ghost = nullptr;
}

void Clyde::TargetSystem(std::vector<int>points)
{
    switch(state_){
        case SCATTER:
            HandleDirection(scatter_j * MazeGraph::cell_size + MazeGraph::x_o, scatter_i *  MazeGraph::cell_size);
            if(!scatter_time--){
                state_ = CHASE;
                std::cout<<"Chasing"<<std::endl;
                scatter_time = 600;
            }
            break;
        default:
            float dist = std::sqrt(std::pow(xpos - points[0], 2) + std::pow(ypos - points[1], 2));
            if(dist < MazeGraph::cell_size * 8){
                HandleDirection(scatter_j * MazeGraph::cell_size + MazeGraph::x_o, scatter_i *  MazeGraph::cell_size);
            }
            else HandleDirection(points[0], points[1]);
    }
}
