#ifndef BLINKY_H
#define BLINKY_H
#include "Ghost.h"

class Blinky: public Ghost
{
    public:
        Blinky(int x, int y, int w, int h, std::string name);
        virtual ~Blinky();

        void TargetSystem(std::vector<int> points);

    private:
};

#endif // BLINKY_H
