#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel &p1, const HSLAPixel &p2)
{
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180)
  {
    h = 360 - h;
  }
  h /= 360;

  return sqrt((h * h) + (s * s) + (l * l));
}
unsigned ImageTraversal::Index(Point &p, unsigned width)
{
  return (p.y * width) + p.x;
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator()
{
  /** @todo [Part 1] */
  currTraversal = NULL;
}
ImageTraversal::Iterator::Iterator(ImageTraversal &t)
{
  /** @todo [Part 1] */
  currTraversal = &t;
  currValue = currTraversal->peek();
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator &ImageTraversal::Iterator::operator++()
{
  /** @todo [Part 1] */
  if (!currTraversal->empty())
  {
    currValue = currTraversal->pop();
    currTraversal->add(currValue);
    currValue = currTraversal->peek();
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*()
{
  /** @todo [Part 1] */
  return currValue;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other)
{
  /** @todo [Part 1] */
  bool temp1 = false;
  bool temp2 = false;

  if (currTraversal == NULL)
    temp1 = true;
  if (other.currTraversal == NULL)
    temp2 = true;

  if (temp1 == false)
    temp1 = currTraversal->empty();
  if (temp2 == false)
    temp2 = other.currTraversal->empty();

  if (temp1 && temp2)
    return false;

  while (!temp1 && !temp2)
  {
    if (currTraversal == NULL)
      temp1 = true;
    if (other.currTraversal == NULL)
      temp2 = true;

    if (temp1 == false)
      temp1 = currTraversal->empty();
    if (temp2 == false)
      temp2 = other.currTraversal->empty();
  }
  return true;
}