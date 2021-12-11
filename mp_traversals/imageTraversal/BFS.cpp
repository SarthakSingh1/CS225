#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG &png, const Point &start, double tolerance)
{
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  currList.push(start);
  visited.resize(png.width() * png.height());
  setVisited(start_);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(*this);
}
/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point &point)
{
  /** @todo [Part 1] */
  unsigned x = point.x;
  unsigned y = point.y;

  Point right(x + 1, y);
  Point below(x, y + 1);
  Point left(x - 1, y);
  Point above(x, y - 1);   

  if (isValid(right))
  {
    currList.push(right);
    setVisited(right);
  }
  if (isValid(below))
  {
    currList.push(below);
    setVisited(below);
  }

  if (isValid(left))
  {
    currList.push(left);
    setVisited(left);
  }

  if (isValid(above))
  {
    currList.push(above);
    setVisited(above);
  }
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop()
{
  /** @todo [Part 1] */
  Point p = currList.front();
  currList.pop();
  return p;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const
{
  /** @todo [Part 1] */
  if (currList.empty()){
    return Point(-1, -1);
    std::cout << "Peeking and Empty List" << std::endl;
  }
  else
    return currList.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const
{
  /** @todo [Part 1] */
  return currList.empty();
}

bool BFS::isValid(Point &p)
{
  if (p.y >= png_.height() || p.x >= png_.width() || isVisited(p))
    return false;

  return (calculateDelta((png_.getPixel(start_.x, start_.y)), (png_.getPixel(p.x, p.y))) <= tolerance_);
}

bool BFS::isVisited(Point &p)
{
  if (p.x >= png_.width() && p.y >= png_.height())
    return true;

  return visited[Index(p, png_.width())];
}
void BFS::setVisited(Point &p)
{
  if (p.x < png_.width() && p.y < png_.height())
    visited[Index(p, png_.width())] = true;
}