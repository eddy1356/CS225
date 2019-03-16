#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  int width = png.width();
  int height = png.height();
  int xCord = start.x;
  int yCord = start.y;
  add(start);

  while(!options.empty()){
    Point t = options.top();
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
bool DFS::compareTol(const HSLAPixel & p1, const HSLAPixel & p2, double tolerance){
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
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(visited.begin());
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(visited.end());
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  options.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point temp = this->options.top();
  this->options.pop();
  return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  Point temp = this->options.top();
  return temp;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  if(this->options.empty()) {
    return true;
  } else {
    return false;
  }
}
