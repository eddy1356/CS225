#include <iterator>
#include <cmath>
#include <list>
#include <queue>

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
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  int width = png.width();
  int height = png.height();
  int xCord = start.x;
  int yCord = start.y;
  add(start);

  while(!options.empty()){
    Point t = options.front();
    options.pop();
    int x = t.x;
    int y = t.y;
    if(std::find(visited.begin(),visited.end(),t) == visited.end()){
      visited.push_back(t);
      if(x+1 < width && compareTol(png.getPixel(xCord,yCord),png.getPixel(x+1,y), tolerance)){
        add(Point(x+1, y));
      }
      if(y+1 < height && compareTol(png.getPixel(xCord,yCord),png.getPixel(x,y+1), tolerance)){
        add(Point(x, y+1));
      }
      if(x-1 >= 0 && compareTol(png.getPixel(xCord,yCord),png.getPixel(x-1,y), tolerance)){
        add(Point(x-1, y));
      }
      if(y-1 >= 0 && compareTol(png.getPixel(xCord,yCord),png.getPixel(x,y-1), tolerance)){
        add(Point(x, y-1));
      }
    }
  }
}
/**
 * helper function to determine the conditions for tolerance
 */
bool BFS::compareTol(const HSLAPixel & p1, const HSLAPixel & p2, double tolerance){
  double delta = ImageTraversal::calc(p1,p2);
  if(delta >= tolerance) {
    return false;
  } else {
    return true;
  }
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(visited.begin());
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(visited.end());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  this->options.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  Point temp = this->options.front();
  this->options.pop();
  return temp;}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  Point temp = this->options.front();
  return temp;
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(this->options.empty()) {
    return true;
  } else {
    return false;
  }
}
