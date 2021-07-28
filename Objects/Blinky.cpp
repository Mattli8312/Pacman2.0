#include "Blinky.h"

Blinky::Blinky(int x, int y, int width, int height, std::string ghostname)
{
    xpos = x;
    ypos = y;
    w = width;
    h = height;
    state_ = SCATTER;
    name = ghostname;

    sprt_i = sprt_j = 0;
    target_i = target_j = 0;
    scatter_i = 1; scatter_j = 26;
    scatter_time = fright_time = 600;
    dir = init_time = 0, vel = GhostVel;
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
    ghost = nullptr;
}


void Blinky::TargetSystem(std::vector<int> points){
    switch(state_){
        case SCATTER:
            Scatter();
            break;
        case FRIGHT:
            Frighten();
            break;
        case EATEN:
            Eaten();
            break;
        case INIT:
            Init();
            break;
        default:
            HandleDirection(points[0], points[1]);
            break;
    }
}
