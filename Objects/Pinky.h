#ifndef PINKY_H
#define PINKY_H
#include "Ghost.h"

class Pinky: public Ghost
{
    public:
        Pinky(int x, int y, int w, int h, std::string name);
        virtual ~Pinky();

        void TargetSystem(std::vector<int> points);

    private:
};

#endif // PINKY_H
