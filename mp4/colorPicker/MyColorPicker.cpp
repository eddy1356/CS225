#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(HSLAPixel color) : color(color){}
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if(color.h > 200) {
    color.h += 13;
    color.s -= 10;
  } else {
    color.h -=12;
    color.s += 10;
  }
  return color;
}
