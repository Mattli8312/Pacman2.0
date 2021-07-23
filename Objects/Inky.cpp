#include "Inky.h"

Inky::Inky(int x, int y, int width, int height, std::string ghostname)
{
    //ctor
    xpos = x;
    ypos = y;
    w = width;
    h = height;
    state_ = SCATTER;
    name = ghostname;

    scatter_i = 29; scatter_j = 1;
    scatter_time = 3000;
    dir = 3, vel = 2;
}

Inky::~Inky()
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

void Inky::TargetSystem(std::vector<int> points){
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
            HandleDirection(2 * points[0] - points[2], 2 * points[1] - points[3]);
            break;
    }
}
