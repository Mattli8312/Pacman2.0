#include "Inky.h"

Inky::Inky(int x, int y, int width, int height, std::string ghostname)
{
    //ctor
    xpos = x;
    ypos = y;
    w = width;
    h = height;
    state_ = INIT;
    name = ghostname;

    sprt_i = sprt_j = 0;
    scatter_i = 29; scatter_j = 1;
    scatter_time = 600;
    dir = 3, vel = GhostVel;
    init_time = 5;
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
    ghost = nullptr;
}

void Inky::TargetSystem(std::vector<int> points){
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
        default: //Chase
            HandleDirection(2 * points[0] - points[2], 2 * points[1] - points[3]);
            break;
    }
}
