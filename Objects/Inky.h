#ifndef INKY_H
#define INKY_H
#include "Ghost.h"


class Inky: public Ghost
{
    public:
        Inky(int x, int y, int w, int h, std::string name);
        virtual ~Inky();

        void TargetSystem(std::vector<int> points);

    private:
};

#endif // INKY_H
