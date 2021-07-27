#ifndef GHOST_H
#define GHOST_H

#include "MazeGraph.h"
#include "GameObject.h"
#include <vector>

#define GhostVel 3

class Ghost
{
    public:
        Ghost();
        Ghost(int x, int y, int w, int h, std::string name);
        ~Ghost();
        enum State{INIT, SCATTER, CHASE, FRIGHT, EATEN};

        void InitializeGhost();
        void HandleDisplay();
        void HandleDirection(int x, int y, bool random = false);
        void HandleMovement();
        void HandleSpeedChange(int new_speed);

        void Init();
        void Scatter();
        void Frighten();
        void Eaten();

        int GetXPos();
        int GetYPos();
        bool IsFrightened();
        bool IsEatened();
        bool IsChase();
        bool IsInit();
        bool IsScattered();

        void SetStateFright();
        void SetStateEat();

        virtual void TargetSystem(std::vector<int> points);

    protected:
        std::vector<std::vector<GameObject*>> GhostSheet;
        std::vector<short> directions;
        GameObject* ghost;

        int xpos, start_x;
        int ypos, start_y;
        int w, h;
        int vel, dir;
        int sprt_i, sprt_j;
        int fps = 5;
        std::string name;

        /**Used for moving mechanism**/
        int target_i;
        int target_j;
        int scatter_i;
        int scatter_j;


        int scatter_time, fright_time, init_time;
        State state_;
};

#endif // GHOST_H
