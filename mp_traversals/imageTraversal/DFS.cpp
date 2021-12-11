#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"
using ::ImageTraversal;
using cs225::PNG;

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG &png, const Point &start, double tolerance)
{
  /** @todo [Part 1] */
  png_ = png;
  start_ = start;
  tolerance_ = tolerance;
  currList.push(start_);
  visited.resize(png_.width() * png_.height());
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(*this);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end()
{
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point &point)
{
  /** @todo [Part 1] */
  unsigned x = point.x;
  unsigned y = point.y;
  
    Point right(x+1, y);
    Point below(x, y + 1);
    Point left(x - 1, y);
    Point above(x, y-1);
  
  if (isValid(right))
    currList.push(right);

  if (isValid(below))
    currList.push(below);

  if (isValid(left))
    currList.push(left);

  if (isValid(above))
    currList.push(above);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop()
{
  /** @todo [Part 1] */
  Point currPoint = peek();
  Point p = currPoint;
  setVisited(currPoint);

  while ((!empty()) && isVisited(p))
  {
    currList.pop();
    p = peek();
  }
  return currPoint;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const
{
  /** @todo [Part 1] */
  if (currList.empty())
    return Point(-1, -1);
  else
    return currList.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const
{
  /** @todo [Part 1] */
  return currList.empty();
}

bool DFS::isValid(Point &p)
{
  if (p.y > png_.height() || p.x > png_.width() || isVisited(p))
    return false;

  return (calculateDelta((png_.getPixel(start_.x, start_.y)), (png_.getPixel(p.x, p.y))) <= tolerance_);
}

bool DFS::isVisited(Point &p)
{
  if (p.x < png_.width() && p.y < png_.height())
    return visited[Index(p, png_.width())];
  
  return true;
}

void DFS::setVisited(Point &p)
{
  if (p.x < png_.width() && p.y < png_.height())
    visited[Index(p, png_.width())] = true;
}