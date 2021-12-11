/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal
{
public:
  BFS(const PNG &png, const Point &start, double tolerance);
  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();

  void add(const Point &point);
  Point pop();
  Point peek() const;
  bool empty() const;
  bool isValid(Point &p);
  bool isVisited(Point &p);
  void setVisited(Point &p);
private:
  /** @todo [Part 1] */
  /** add private members here*/
  PNG png_;
  Point start_;
  double tolerance_;
  std::queue<Point> currList;
  std::vector<bool> visited;
};