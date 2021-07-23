#ifndef CLYDE_H
#define CLYDE_H
#include "Ghost.h"


class Clyde: public Ghost
{
    public:
        Clyde(int x, int y, int w, int h, std::string name);
        virtual ~Clyde();

        void TargetSystem(std::vector<int> points);
    private:
};

#endif // CLYDE_H
