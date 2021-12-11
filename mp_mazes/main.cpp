#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;
using ::SquareMaze;

int main()
{
    // Write your own main here
    cout << "Add your own tests here! Modify main.cpp" << endl;
    SquareMaze hi;
    int width, height;
    width = 5;
    height = 5;
    hi.makeMaze(width,height);
    PNG * temp = hi.drawMaze();
    temp->writeToFile("MainTest.png");
    // testFunctions::printValues(width,height,hi);
    // hi.setWall(1, 1,0,false);
    // hi.setWall(1, 1, 1, true);
    // testFunctions::printValues(width, height, hi);


    std::cout << "Done " << std::endl ;
    return 0;
}

