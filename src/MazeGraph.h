#ifndef MAZEGRAPH_H
#define MAZEGRAPH_H
#include <vector>

class MazeGraph
{
    public:
        MazeGraph();
        ~MazeGraph();

        void ParseGraphFromFile();
        void PrintGraph();
        void RenderMaze();
        void ClearMaze();


        static std::vector<std::vector<char>> graph;
        static std::vector<std::vector<short>> visited;
        static unsigned x_o;
        static unsigned cell_size;
        static unsigned width, height;
    private:
};

#endif // MAZEGRAPH_H
