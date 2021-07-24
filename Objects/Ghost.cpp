#include "Ghost.h"
#include "stdio.h"

Ghost::Ghost(){
    xpos = ypos = 0;
    target_i = target_j = 0;
    scatter_i = scatter_j = 0;
    w = h = dir = vel = 0;
    state_ = SCATTER;
    ghost = nullptr;
}


Ghost::Ghost(int x, int y, int width, int height, std::string name)
{
    /**@nothing**/
}

Ghost::~Ghost()
{
    //dtor
}

void Ghost::InitializeGhost()
{
    for(int i = 0; i < 1; i++){
        std::vector<GameObject*> temp;
        for(int j = 1; j < 3; j++){
            const char * filename;
            std::string file("Sprites/" + name + "/0.png");
            filename = &file[0];
            if(!IMG_Load(filename))
                printf("Error: %s", IMG_GetError());
            temp.push_back(new GameObject(filename, xpos, ypos, w, h));
        }
        GhostSheet.push_back(temp);
    }

    ghost = GhostSheet[0][0];
}


void Ghost::HandleDisplay()
{
    if(ghost != nullptr){
        ghost->Update(xpos - MazeGraph::cell_size/4, ypos - MazeGraph::cell_size/4);
        ghost->Render();
    }
}

void Ghost::HandleDirection(int x, int y, bool random)
{
    /**Parameters**/
    target_i = y / MazeGraph::cell_size;
    target_j = (x - MazeGraph::x_o) / MazeGraph::cell_size;
    int j = (xpos - MazeGraph::x_o) / MazeGraph::cell_size;
    int i = ypos / MazeGraph::cell_size;
    int prev_dir = dir;
    /**Random Selection**/
    std::vector<short> directions;
    if(!((xpos - MazeGraph::x_o)%MazeGraph::cell_size) && !(ypos%MazeGraph::cell_size)){
        if(MazeGraph::graph[i][j] == '+'){
            int dist_;
            int min_dist = -1;
            if(i - 1 > -1 && MazeGraph::graph[i-1][j] != '.' && prev_dir != 2){ //Checking direction up;
                dist_ = (target_i - (i - 1)) * (target_i - (i - 1)) + (target_j - j) * (target_j - j);
                directions.push_back(4);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 4;
                }
            }
            if(j - 1 > -1 && MazeGraph::graph[i][j-1] != '.' && prev_dir != 1){ //Checking direction left;
                dist_ = (target_i - i) * (target_i - i) + (target_j - (j - 1)) * (target_j - (j - 1));
                directions.push_back(3);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 3;
                }
            }
            if(i + 1 < (int)MazeGraph::graph.size() && MazeGraph::graph[i+1][j] != '.' && prev_dir != 4){ //Check direction down
                dist_ = (target_i - (i + 1)) * (target_i - (i + 1)) + (target_j - j) * (target_j - j);
                directions.push_back(2);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 2;
                }
            }
            if(j + 1 < (int)MazeGraph::graph.size() && MazeGraph::graph[i][j+1] != '.' && prev_dir != 3){ //Check direction right
                dist_ = (target_i - i) * (target_i - i) + (target_j - (j + 1)) * (target_j - (j + 1));
                directions.push_back(1);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 1;
                }
            }
            if(random){
                dir = directions[rand() % directions.size()];
            }
        }
    }
}


void Ghost::HandleMovement()
{
    switch(dir){
        case 1:
            if((xpos >= (int)(MazeGraph::graph[0].size()-1) * (int)MazeGraph::cell_size + (int)MazeGraph::x_o)){
                xpos = MazeGraph::x_o;
            }
            else
                xpos += vel;
            break;
        case 2:
            ypos += vel; break;
        case 3:
            if(!(xpos - MazeGraph::x_o)){
                xpos = MazeGraph::x_o + MazeGraph::cell_size * (MazeGraph::graph[0].size()-1);
            }
            else
                xpos -= vel;
            break;
        default:
            ypos -= vel; break;

    }
}

int Ghost::GetXPos(){
    return xpos;
}

int Ghost::GetYPos(){
    return ypos;
}

void Ghost::SetStateFright()
{
    /**Rotate the direction 180**/
    //Directions 1 2 3 4
    if(state_ != FRIGHT)
        dir = (dir + 2) % 4;
    state_ = FRIGHT;
}


void Ghost::TargetSystem(std::vector<int> points)
{
    /**@Nothing**/
}
