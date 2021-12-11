/* Your code here! */
#pragma once
#include <vector>
#include <iostream>
#include "cs225/PNG.h"
#include "dsets.h"
using std::vector;
using cs225::PNG;
using std::pair;
using std::cout;
using std::endl;

class SquareMaze{
    public:
        void makeMaze(int width, int height);
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        SquareMaze();
        bool canTravel(int x, int y, int dir) const;
        PNG * drawMaze() const;
        PNG *drawMazeWithSolution();
  

    private:
        DisjointSets mySet ;
        vector<pair<bool, bool> > myWalls ;
        int myWidth, myHeight, finalSquare;
};

class testFunctions{
    public: 
    static void printValues(int width, int height, SquareMaze hi)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int total = (y * width) + x;
                std::cout << " Box : " << total
                          << " Can move right " << hi.canTravel(x, y, 0)
                          << " Can move left " << hi.canTravel(x, y, 2)
                          << " Can move above " << hi.canTravel(x, y, 3)
                          << " Can move below " << hi.canTravel(x, y, 1)
                          << " \n" << std::endl;
            }
        }
        std::cout << "======================================== \n" << std::endl;
    }
};