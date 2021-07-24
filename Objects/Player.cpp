#include "Player.h"
#include "MazeGraph.h"

#include "Player.h"

Player::~Player()
{
    //dtor
    if(player)
        delete player;
    for(unsigned i = 0 ; i < Pacman.size(); i++){
        for(unsigned j = 0; j < Pacman[0].size(); j++){
            if(Pacman[i][j]) delete Pacman[i][j];
            Pacman[i][j] = nullptr;
        }
    }
    player = nullptr;
}

Player::Player(int x, int y, int w, int h)
{
    for(int i = 0; i < 4; i++){
        std::vector<GameObject*> temp;
        for(int j = 1; j < 3; j++){
            const char * filename;
            std::string file("Sprites/Pacman" + std::to_string(j+i*2) + ".png");
            filename = &file[0];
            temp.push_back(new GameObject(filename, x, y, w, h));
        }
        temp.push_back(new GameObject("Sprites/Pacman0.png", x ,y, w, h));
        Pacman.push_back(temp);
    }
    score = 0;
    lives = 3;
    x_pos = x;
    y_pos = y;
    width = w;
    height = h;
    a_rate = 10;
    a_indx = 0;
    dir = 0;
    player = Pacman[dir][a_indx];
}

void Player::HandleDisplay()
{
    //Render Player
    player->Update(x_pos - MazeGraph::cell_size/4, y_pos - MazeGraph::cell_size/4);
    player->Render();
}

void Player::HandleMovement()
{
    int vel = 3;
    if(!HasCollided((short)dir)){
        switch(dir){
            case 3: y_pos -= vel;
                break;
            case 1: y_pos += vel;
                break;
            case 2:
                /**
                For these parts, we handle to teleportation of Pacman between the two portals
                **/
                if(!(x_pos - MazeGraph::x_o))
                    x_pos = MazeGraph::x_o + MazeGraph::cell_size * (MazeGraph::graph[0].size()-1);
                else
                    x_pos -= vel;
                break;
            default:
                if((x_pos >= (int)(MazeGraph::graph[0].size()-1) * (int)MazeGraph::cell_size + (int)MazeGraph::x_o))
                    x_pos = MazeGraph::x_o;
                else
                    x_pos += vel;
                break;
        }
    }
}


void Player::HandleEventListener()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    //This conditional statement is used for rendering purposes: To ensure that the pacman character's texture doesn't
    //Overlap with the barriers, this condition make's sure to turn only at certain points
    if((x_pos - MazeGraph::x_o) % MazeGraph::cell_size == 0 && (y_pos) % MazeGraph::cell_size == 0){
        if (state[SDL_SCANCODE_A]) {
            dir = 2;
            player = Pacman[dir][a_indx];
        }
        else if (state[SDL_SCANCODE_D]) {
            dir = 0;
            player = Pacman[dir][a_indx];
        }
        else if (state[SDL_SCANCODE_W]) {
            dir = 3;
            player = Pacman[dir][a_indx];
        }
        else if(state[SDL_SCANCODE_S]){
            dir = 1;
            player = Pacman[dir][a_indx];
        }
        else if(state[SDL_SCANCODE_J])
            std::cout<<score<<std::endl;
    }

    a_rate --;
    //Check to see if we transition
    if(!a_rate){
        a_rate = 10;
        a_indx ++;
        a_indx %= 3;
        player = Pacman[dir][a_indx];
    }
}

bool Player::HasCollided(short direction)
{
    unsigned j_ = (x_pos) - MazeGraph::x_o + width/2;
    unsigned i_ = y_pos + height/2;

    j_ /= MazeGraph::cell_size;
    i_ /= MazeGraph::cell_size;

    /**
    Scoring System: Used to update the score of the current player and update the graph structure of the
    maze as well
    **/

    if(!((x_pos - MazeGraph::x_o) % MazeGraph::cell_size) && !(y_pos % MazeGraph::cell_size)){
        //continue
        switch(MazeGraph::pellets[i_][j_]){
            case 1: score += 100; break;
            case 2: score += 1000; break;
            default: break;
        }
        MazeGraph::pellets[i_][j_] = 0;
    }
    /**
    Collision Detection
    **/
    switch(direction){
        case 0:  //Right
            if((x_pos - MazeGraph::x_o) % MazeGraph::cell_size || MazeGraph::graph[i_][j_+1] != '.')
                return false;
            return true;
        case 2: //Left
            if((x_pos - MazeGraph::x_o) % MazeGraph::cell_size || MazeGraph::graph[i_][j_-1] != '.')
                return false;
            return true;
        case 1: //Down
            if(y_pos % MazeGraph::cell_size || MazeGraph::graph[i_+1][j_] != '.')
                return false;
            return true;
        default:
            if(y_pos % MazeGraph::cell_size || MazeGraph::graph[i_-1][j_] != '.')
                return false;
            return true;
    }
}

int Player::GetXPos()
{
    return x_pos;
}

int Player::GetYPos()
{
    return y_pos;
}

int Player::GetDir(){
    return dir;
}
