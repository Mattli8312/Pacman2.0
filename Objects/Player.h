#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <vector>
#include <string>
#include <cstring>

class Player
{
    public:
        Player(int x, int y, int w, int h);
        ~Player();

        void HandleDisplay();
        void HandleEventListener();
        void HandleMovement();

        bool HasCollided(short direction);
        bool HasCompleted();
        bool IsEnergized();
        int GetXPos();
        int GetYPos();
        int GetDir();
        int GetScore();

        void SetEnergized(bool);

    private:
        std::vector<std::vector<GameObject*>> Pacman;
        GameObject * player;

        int score;
        int lives;
        int x_pos;
        int y_pos;
        int width;
        int height;
        int dir;
        int a_rate; //Animation rate
        int a_indx; //Animation indx

        bool energized;
        bool completed;
};

#endif // PLAYER_H
