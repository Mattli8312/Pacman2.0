#include "Blinky.h"

Blinky::Blinky(int x, int y, int width, int height, std::string ghostname)
{
    xpos = x;
    ypos = y;
    w = width;
    h = height;
    state_ = SCATTER;
    name = ghostname;

    target_i = target_j = 0;
    scatter_i = 1; scatter_j = 26;
    scatter_time = 600;
    dir = 1, vel = 2;
}


Blinky::~Blinky()
{
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


void Blinky::TargetSystem(std::vector<int> points){

    switch(state_){
        case SCATTER:
            HandleDirection(scatter_j * MazeGraph::cell_size + MazeGraph::x_o, scatter_i * MazeGraph::cell_size);
            if(!scatter_time--){
                state_ = CHASE;
                std::cout<<"Chasing"<<std::endl;
                scatter_time = 300;
            }
            break;
        default:
            HandleDirection(points[0], points[1]);
            break;
    }
}
