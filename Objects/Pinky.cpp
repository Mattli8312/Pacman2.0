#include "Pinky.h"

Pinky::Pinky(int x, int y, int width, int height, std::string ghostname)
{
    xpos = x;
    ypos = y;
    w = width;
    h = height;
    state_ = SCATTER;
    name = ghostname;

    scatter_i = 1; scatter_j = 1;
    scatter_time = 3000;
    dir = 3, vel = 2;
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
    std::cout<<"Freed!"<<std::endl;
    ghost = nullptr;
}

void Pinky::TargetSystem(std::vector<int> points)
{
    switch(state_){
        case SCATTER:
            HandleDirection(scatter_j * MazeGraph::cell_size + MazeGraph::x_o, scatter_i * MazeGraph::cell_size);
            if(!scatter_time--){
                state_ = CHASE;
                scatter_time = 300;
            }
            break;
        default:
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
