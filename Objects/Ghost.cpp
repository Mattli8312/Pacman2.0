#include "Ghost.h"
#include "stdio.h"

Ghost::Ghost(){
    xpos = ypos = sprt_i = sprt_j = 0;
    target_i = target_j = 0;
    scatter_i = scatter_j = 0;
    scatter_time = fright_time = 0;
    w = h = dir = vel = 3;
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
    /**Used for resetting the ghost**/
    start_x = xpos;
    start_y = ypos;
    prev_dir = dir;
    prev_init_time = init_time;
    for(int i = 0; i < 4; i++){
        std::vector<GameObject*> temp;
        for(int j = 0; j < 2; j++){
            const char * filename;
            std::string file("Sprites/" + name + "/" + std::to_string(i*2 + j) + ".png");
            filename = &file[0];
            temp.push_back(new GameObject(filename, xpos, ypos, w, h));
        }
        std::string file("Sprites/Assets/Eaten" + std::to_string(i) + ".png");
        temp.push_back(new GameObject(&file[0], xpos, ypos, w, h));
        GhostSheet.push_back(temp);
    }
    const char* filename = "Sprites/Assets/Frightened0.png";
    const char* filename2 = "Sprites/Assets/Frightened1.png";
    GhostSheet.push_back({new GameObject(filename, xpos, ypos, w, h), new GameObject(filename2, xpos, ypos, w, h)});
    ghost = GhostSheet[sprt_i][sprt_j];
}


void Ghost::HandleDisplay()
{
    if(ghost != nullptr){
        ghost->Update(xpos - MazeGraph::cell_size/4, ypos - MazeGraph::cell_size/4);
        ghost->Render();
    }
    switch(state_){
        case FRIGHT:
            if(sprt_i != 4) sprt_i = 4;
            if(fright_time <= 100 && !(fright_time%5)){
                sprt_j = sprt_j ? 0 : 1;
            }
            break;
        case EATEN:
            if(sprt_j != 3) sprt_j = 3;
            sprt_i = dir;
            break;
        default:
            if(sprt_i != dir) sprt_i = dir;
            if(!fps--){
                fps = 10; sprt_j = (sprt_j + 1) % 2;
            }
    }
    ghost = GhostSheet[sprt_i][sprt_j];
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
        if(MazeGraph::graph[i][j] == '+' || (MazeGraph::graph[i][j] == '*' && state_ == EATEN)){
            int dist_;
            int min_dist = -1;
            if(i - 1 > -1 && MazeGraph::graph[i-1][j] != '.' && prev_dir != 1){ //Checking direction up;
                dist_ = (target_i - (i - 1)) * (target_i - (i - 1)) + (target_j - j) * (target_j - j);
                directions.push_back(3);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 3;
                }
            }
            if(j - 1 > -1 && MazeGraph::graph[i][j-1] != '.' && prev_dir != 0){ //Checking direction left;
                dist_ = (target_i - i) * (target_i - i) + (target_j - (j - 1)) * (target_j - (j - 1));
                directions.push_back(2);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 2;
                }
            }
            if(i + 1 < (int)MazeGraph::graph.size() && MazeGraph::graph[i+1][j] != '.' && prev_dir != 3){ //Check direction down
                dist_ = (target_i - (i + 1)) * (target_i - (i + 1)) + (target_j - j) * (target_j - j);
                directions.push_back(1);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 1;
                }
            }
            if(j + 1 < (int)MazeGraph::graph.size() && MazeGraph::graph[i][j+1] != '.' && prev_dir != 2){ //Check direction right
                dist_ = (target_i - i) * (target_i - i) + (target_j - (j + 1)) * (target_j - (j + 1));
                directions.push_back(0);
                if(min_dist == -1 || dist_ < min_dist){
                    min_dist = dist_;
                    dir = 0;
                }
            }
            if(random){
                dir = directions[rand() % directions.size()];
            }
        }
    }
}

void Ghost::HandleSpeedChange(int new_speed){
    switch(dir){
        case 0:
            while((xpos - MazeGraph::x_o) % new_speed) xpos ++;
            break;
        case 1:
            while(ypos % new_speed) ypos++;
            break;
        case 2:
            while((xpos - MazeGraph::x_o) % new_speed) xpos --;
            break;
        default:
            while(ypos % new_speed) ypos --;
            break;
    }
    vel = new_speed;
}

void Ghost::HandleMovement()
{
    switch(dir){
        case 0:
            if((xpos >= (int)(MazeGraph::graph[0].size()-1) * (int)MazeGraph::cell_size + (int)MazeGraph::x_o)){
                xpos = MazeGraph::x_o;
            }
            else
                xpos += vel;
            break;
        case 1:
            ypos += vel;
            break;
        case 2:
            if(!(xpos - MazeGraph::x_o)){
                xpos = MazeGraph::x_o + MazeGraph::cell_size * (MazeGraph::graph[0].size()-1);
            }
            else
                xpos -= vel;
            break;
        default:
            ypos -= vel;
            break;
    }
}

void Ghost::HandleReset(){
    xpos = start_x;
    ypos = start_y;
    dir = prev_dir;
    init_time = prev_init_time;
    state_ = name == "Blinky" ? SCATTER : INIT;
}

void Ghost::Init(){
    if(!(ypos % MazeGraph::cell_size) && !((xpos - MazeGraph::x_o) % MazeGraph::cell_size)){
        int i_ = ypos / MazeGraph::cell_size;
        int j_ = (xpos - MazeGraph::x_o) / MazeGraph::cell_size;
        if(MazeGraph::graph[i_][j_] == '+'){
            if(dir == 3 && init_time) init_time--;
            if(init_time) dir = (dir + 2) % 4;
            else if(j_ < 13) dir = 0;
            else if(j_ > 13) dir = 2;
            else dir = 3;
        }
        if(MazeGraph::graph[i_][j_] == '*'){
            switch(scatter_j){
                case 1: dir = 2;
                default: dir = 0;
            }
            state_ = SCATTER;
        }
    }
}

void Ghost::Scatter()
{
    HandleDirection(scatter_j * MazeGraph::cell_size + MazeGraph::x_o, scatter_i * MazeGraph::cell_size);
    if(!scatter_time--){
        state_ = CHASE;
        ghost = GhostSheet[sprt_i][sprt_j];
        scatter_time = 600;
    }
}

void Ghost::Frighten()
{
    HandleDirection(-1, -1, true);
    if(!sprt_i) sprt_i = 1;
    if(!fright_time--){
        state_ = CHASE;
        HandleSpeedChange(3);
        ghost = GhostSheet[sprt_i][sprt_j];
        fright_time = 600;
    }
}

void Ghost::Eaten()
{
    HandleDirection(MazeGraph::x_o + 12 * MazeGraph::cell_size, 14 * MazeGraph::cell_size);
    int i_ = ypos / MazeGraph::cell_size;
    int j_ = (xpos - MazeGraph::x_o) / MazeGraph::cell_size;
    if(ghost != GhostSheet[dir][2]) ghost = GhostSheet[dir][2];
    if(!((xpos-MazeGraph::x_o)%MazeGraph::cell_size) && !(ypos%MazeGraph::cell_size)){
        if(i_ == 13 && j_ == 11){
            std::cout<<"Chase"<<std::endl;
            state_ = INIT;
            HandleSpeedChange(3);
        }
    }
}

int Ghost::GetXPos(){
    return xpos;
}

int Ghost::GetYPos(){
    return ypos;
}

bool Ghost::IsFrightened()
{
    return state_ == FRIGHT;
}

bool Ghost::IsEatened()
{
    return state_ == EATEN;
}

bool Ghost::IsChase()
{
    return state_ == CHASE;
}

bool Ghost::IsInit(){
    return state_ == INIT;
}

bool Ghost::IsScattered(){
    return state_ == SCATTER;
}

void Ghost::SetStateFright()
{
    /**Rotate the direction 180**/
    //Directions 1 2 3 4
    if(state_ != FRIGHT)
        dir = (dir + 2) % 4;
    state_ = FRIGHT;
    sprt_i = 4;
    sprt_j = 0;
    ghost = GhostSheet[sprt_i][sprt_j];
}

void Ghost::SetStateEat(){
    state_ = EATEN;
    ghost = GhostSheet[0][0];
    fright_time = 600;
}

void Ghost::TargetSystem(std::vector<int> points)
{
    /**@Nothing**/
}
