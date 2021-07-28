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
        void RenderMaze(bool);
        void RenderCellWall(int i, int j, bool);
        void ClearMaze();


        static std::vector<std::vector<char>> graph;
        static std::vector<std::vector<short>> pellets;
        static unsigned x_o;
        static unsigned cell_size;
        static unsigned width, height;
        static int food_count;

    private:
        int maze_complete_fps = 0;
};

#endif // MAZEGRAPH_H
