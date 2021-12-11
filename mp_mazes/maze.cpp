/* Your code here! */
#include "maze.h"
#include "queue"
#include "stack"
using cs225::HSLAPixel;
using std::queue;
#include <sys/time.h>

SquareMaze::SquareMaze()
{
}

void SquareMaze::makeMaze(int width, int height)
{
    myHeight = height;
    myWidth = width;
    int totalSize = myHeight * myWidth;
    /*
    Initialize myWalls so that its big enough
    First bool is if the right wall exists while the second is the bottom wall
    */
    myWalls.resize(totalSize);
    for (int i = 0; i < totalSize; i++)
    {
        pair<bool, bool> temp(true, true);
        myWalls[i] = temp;
    }
    // add empty elements to our disjointSet
    mySet.addelements(totalSize);

    // To make sure rand puts a different value every time
      struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_usec);

    int randX, randY, currIdx, currIdxRight, currIdxUnder, goRight;
    // Run until all the items are inside of one list which is equal to the totalSize(no more unions can be made without a loop)
    while (mySet.size(0) < totalSize)
    {
        randX = rand() % width;
        randY = rand() % height;
        currIdx = (randY * width) + randX;
        currIdxRight = (randY * width) + randX + 1;
        currIdxUnder = ((randY + 1) * width) + randX;
        goRight = rand() % 2;

        // Randomly decide if I should try to go right or under(Bad algorithm but I cant find another solution)
        if (goRight == 1)
        {
            if (randX != width - 1)
            {
                if (mySet.find(currIdx) != mySet.find(currIdxRight))
                {
                    myWalls[currIdx].first = false;
                    mySet.setunion(currIdx, currIdxRight);
                }
            }
        }
        else
        {
            if (randY != height - 1)
            {
                if (mySet.find(currIdx) != mySet.find(currIdxUnder))
                {
                    myWalls[currIdx].second = false;
                    mySet.setunion(currIdx, currIdxUnder);
                }
            }
        }
    }
}
// dir = 0 represents a rightward step (+1 to the x coordinate)
// dir = 1 represents a downward step (+1 to the y coordinate)
// dir = 2 represents a leftward step (-1 to the x coordinate)
// dir = 3 represents an upward step (-1 to the y coordinate)

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    int currIdx = (y * myWidth) + x;
    pair<bool, bool> currPair, abovePair, leftPair;

    if (x > myWidth || y > myHeight || x < 0 || y < 0)
        return false;

    // Edge cases in case you are on a boundry

    // If x is on the left and you want to move left it is always
    if (x == 0 && dir == 2)
        return false;

    if (y == 0 && dir == 3)
        return false;

    // If it is not an edge case then we need to check the pair above it and the pair to its right to see if it can move in all 4 directions

    currPair = myWalls[currIdx];
    abovePair = myWalls[currIdx - myWidth];
    leftPair = myWalls[currIdx - 1];

    if (dir == 0)
    {
        if (currPair.first == false)
            return true;
        else
            return false;
    }
    if (dir == 1)
    {
        if (currPair.second == false)
            return true;
        else
            return false;
    }
    if (dir == 2)
    {
        if (leftPair.first == false)
            return true;
        else
            return false;
    }

    if (dir == 3)
    {
        if (abovePair.second == false)
            return true;
        else
            return false;
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{

    int currIdx = (y * myWidth) + x;

    // Set right wall
    if (dir == 0)
        myWalls[currIdx].first = exists;

    // Set bottom wall
    else if (dir == 1)
        myWalls[currIdx].second = exists;
}

vector<int> SquareMaze::solveMaze()
{

    int x, y, currIdx;
    vector<int> visited;
    vector<int> distance;
    
    for (int i = 0; i < myWidth * myHeight; i++)
    {
        visited.push_back(-1);
        distance.push_back(0);
    }
    visited[0] = 0;
    distance[0] = 0;

    queue<int> searchQueue;
    searchQueue.push(0);

    while (!searchQueue.empty())
    {
        currIdx = searchQueue.front();
        x = currIdx % myWidth;
        y = currIdx / myWidth;
        searchQueue.pop();
        int currIdxRight = currIdx + 1, currIdxDown = currIdx + myWidth, currIdxLeft = currIdx - 1, currIdxAbove = currIdx - myWidth;

        for (int i = 0; i < 4; i++)
        {
            int tempIdx;
            if (i == 0)
                tempIdx = currIdxRight;
            if (i == 1)
                tempIdx = currIdxDown;
            if (i == 2)
                tempIdx = currIdxLeft;
            if (i == 3)
                tempIdx = currIdxAbove;
            if (canTravel(x, y, i))
            {
                if (visited[tempIdx] == -1)
                {
                    searchQueue.push(tempIdx);
                    visited[tempIdx] = currIdx;
                    distance[tempIdx] = distance[currIdx] + 1;
                }
            }
        }
    }

    int currPath = myWidth * (myHeight - 1);
    for (int i = 0; i < myWidth; i++)
    {
        if (distance[myWidth * (myHeight - 1) + i] > distance[currPath])
            currPath = myWidth * (myHeight - 1) + i;
    }

    finalSquare = currPath;
    int currIdx2 = finalSquare;
    std::vector<int> finalValues;
    while (currIdx2 != 0)
    {
        if (visited[currIdx2] == currIdx2 - 1)
            finalValues.push_back(0);
        if (visited[currIdx2] == currIdx2 + 1)
            finalValues.push_back(2);
        if (visited[currIdx2] == currIdx2 - myWidth)
            finalValues.push_back(1);
        if (visited[currIdx2] == currIdx2 + myWidth)
            finalValues.push_back(3);
        currIdx2 = visited[currIdx2];
    }
    reverse(finalValues.begin(), finalValues.end());

    return finalValues;
}

PNG *SquareMaze::drawMaze() const
{
    unsigned picHeight = myHeight * 10 + 1;
    unsigned picWidth = myWidth * 10 + 1;

    PNG *myMaze = new PNG(picWidth, picHeight);

    for (unsigned y = 0; y < picHeight; y++)
    {
        HSLAPixel &p = myMaze->getPixel(0, y);
        p.l = 0;
    }

    for (unsigned x = 10; x < picWidth; x++)
    {
        HSLAPixel &p = myMaze->getPixel(x, 0);
        p.l = 0;
    }

    for (int y = 0; y < myHeight; y++)
    {
        for (int x = 0; x < myWidth; x++)
        {
            int currIdx = (y * myWidth) + x;
            if (myWalls[currIdx].first == true)
            {
                for (int i = 0; i <= 10; i++)
                {
                    HSLAPixel &p = myMaze->getPixel((x + 1) * 10, y * 10 + i);
                    p.l = 0;
                }
            }
            if (myWalls[currIdx].second == true)
            {
                for (int i = 0; i <= 10; i++)
                {
                    HSLAPixel &p = myMaze->getPixel(x * 10 + i, (y + 1) * 10);
                    p.l = 0;
                }
            }
        }
    }
    return myMaze;
}

PNG *SquareMaze::drawMazeWithSolution()
{
    PNG *png = drawMaze();
    vector<int> solution = solveMaze();
    //1,1 essentially
    int x = 5 , y = 5;
    //Draw lines base don if you move to the right left up etc. 
    while (!solution.empty()){

        if (solution[0] == 0) {
            for (int i = x; i <= x+10; i++)
            {
                HSLAPixel &pixel = png->getPixel(i, y); 
                pixel.s = 1;
                pixel.l = .5;
            }
            x+=10;
        }
        if (solution[0] == 1) {
            for (int i = y; i < y+10; i++) {
                HSLAPixel &pixel = png->getPixel(x, i) ;
                pixel.s = 1 ;
                pixel.l = .5;
            }
            y += 10;
        }
        if (solution[0] == 2) {
        for (int i = x - 10; i <=x ; i++){
                HSLAPixel &pixel = png->getPixel(i, y);
                pixel.s = 1 ;
                pixel.l = .5;
            }
            x -= 10;
        }
        if (solution[0] == 3){
            for (int i = y - 10; i <= y ; i++){
                HSLAPixel &pixel = png->getPixel(x, i);
                pixel.s = 1 ;
                pixel.l = .5;
            }
            y -= 10;
        }
            solution.erase(solution.begin());
    }
    //Fill in the closing part
    int destinationX = finalSquare % myWidth;
    int destinationY = finalSquare / myHeight;
  for(int k = 1; k <= 9; k++){
    HSLAPixel& p = png->getPixel(destinationX * 10 + k, (destinationY + 1) * 10);
    p.l = 1;
  }
    return png;
}