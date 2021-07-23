#ifndef GHOST_H
#define GHOST_H

#include "MazeGraph.h"
#include "GameObject.h"
#include <vector>

class Ghost
{
    public:
        Ghost();
        Ghost(int x, int y, int w, int h, std::string name);
        ~Ghost();
        enum State{SCATTER, CHASE, FRIGHT, EATEN};

        void InitializeGhost();
        void HandleDisplay();
        void HandleDirection(int x, int y);
        void HandleMovement();

        int GetXPos();
        int GetYPos();

        virtual void TargetSystem(std::vector<int> points);

    protected:
        std::vector<std::vector<GameObject*>> GhostSheet;
        std::vector<short> directions;
        GameObject* ghost;

        int xpos;
        int ypos;
        int w, h;
        int vel, dir;
        std::string name;

        /**Used for moving mechanism**/
        int target_i;
        int target_j;
        int scatter_i;
        int scatter_j;

        int scatter_time;
        State state_;
};

#endif // GHOST_H
