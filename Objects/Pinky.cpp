#include "Pinky.h"

Pinky::Pinky(int x, int y, int width, int height, std::string ghostname)
{
    xpos = start_x = x;
    ypos = start_y = y;
    w = width;
    h = height;
    state_ = INIT;
    name = ghostname;

    sprt_i = sprt_j = 0;
    scatter_i = 1; scatter_j = 1;
    scatter_time = fright_time = 600;
    dir = 3, vel = GhostVel;
    init_time = 3;
}

Pinky::~Pinky()
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

void Pinky::TargetSystem(std::vector<int> points)
{
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
        default: // Chase
            switch(points[2]){
                case 0:
                    points[0] += 4 * MazeGraph::cell_size;
                    break;
                case 1:
                    points[1] += 4 * MazeGraph::cell_size;
                    break;
                case 2:
                    points[0] -= 4 * MazeGraph::cell_size;
                    break;
                default:
                    points[1] -= 4 * MazeGraph::cell_size;
                    break;
            }
            HandleDirection(points[0], points[1]);
            break;
    }
}
