#include <iostream>
#include "Image.h"


Image::Image():PNG() {
}
//
// Image::Image(unsigned int width, unsigned int height):PNG(width, height){
// }

void Image::lighten() {
    for(unsigned int x = 0; x < width(); x++){
      for(unsigned int y = 0; y < height(); y++){
        cs225::HSLAPixel & pixel = getPixel(x,y);
        pixel.l += 0.1;
        if(pixel.l > 1.0) {
          pixel.l = 1.0;
        }
      }
    }
  }

void Image::lighten(double amount) {
    for(unsigned int x = 0; x < width(); x++){
      for(unsigned int y = 0; y < height(); y++){
        cs225::HSLAPixel & pixel = getPixel(x,y);
        pixel.l += amount;
        if(pixel.l > 1.0) {
          pixel.l = 1.0;
        }
      }
    }
  }

void Image::darken() {
    for(unsigned int x = 0; x < width(); x++){
      for(unsigned int y = 0; y < height(); y++){
        cs225::HSLAPixel & pixel = getPixel(x,y);
        pixel.l -= 0.1;
        if(pixel.l < 0.0) {
          pixel.l = 0.0;
        }
      }
    }
  }
void Image::darken(double amount) {
    for(unsigned int x = 0; x < width(); x++){
      for(unsigned int y = 0; y < height(); y++){
        cs225::HSLAPixel & pixel = getPixel(x,y);
        pixel.l -= amount;
        if(pixel.l < 0.0) {
          pixel.l = 0.0;
        }
      }
    }
  }
void Image::saturate() {
    for(unsigned int x = 0; x < width(); x++){
      for(unsigned int y = 0; y < height(); y++) {
        cs225::HSLAPixel & pixel = getPixel(x,y);
        pixel.s += 0.1;
        if(pixel.s > 1.0) {
          pixel.s = 1.0;
        }
      }
    }
  }

void Image::saturate(double amount) {
    for(unsigned int x = 0; x < width(); x++){
      for(unsigned int y = 0; y < height(); y++){
        cs225::HSLAPixel & pixel = getPixel(x,y);
        pixel.s += amount;
        if(pixel.s > 1.0) {
          pixel.s = 1.0;
        }
      }
    }
  }

void Image::desaturate() {
  for(unsigned int x = 0; x < width(); x++){
    for(unsigned int y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x,y);
      pixel.s -= 0.1;
      if(pixel.s < 0.0) {
        pixel.s = 0.0;
      }
    }
  }
}

void Image::desaturate(double amount) {
  for(unsigned int x = 0; x < width(); x++) {
    for(unsigned int y = 0; y < height(); y++){
      cs225::HSLAPixel & pixel = getPixel(x,y);
      pixel.s -= amount;
      if(pixel.s < 0.0) {
        pixel.s = 0.0;
      }
    }
  }
}

void Image::grayscale() {
  for(unsigned int x = 0; x < width(); x++) {
    for(unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = getPixel(x,y);
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees) { //DEGREES MAY BE NEGATIVE!!!!!
  for(unsigned int x = 0; x < width(); x++) {
    for(unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = getPixel(x,y);
      pixel.h += degrees;
      if(pixel.h >= 360) {
        pixel.h -= 360;
      } else if (pixel.h < 0.0) {
        pixel.h += 360;
      }
    }
  }
}

void Image::illinify() {
  for (unsigned int x = 0; x < width(); x++) {
    for (unsigned int y = 0; y < height(); y++) {
      cs225::HSLAPixel & pixel = getPixel(x,y);
      if (113.5 < pixel.h && pixel.h <= 293.5) {
        pixel.h = 216.0;
      } else {
        pixel.h = 11.0;
      }
    }
  }
}

void Image::scale(double factor) {
  cs225::PNG* temp = new PNG(factor * width(), factor * height());

  if ( factor > 1) {
    for(unsigned int x = 0; x < width(); x++) {
      for(unsigned int y = 0; y < height(); y++) {
        for(unsigned int z = factor * x; z < (x * factor + factor); z++) {
          for(unsigned int w = factor * y; w < (y * factor + factor); w++){
            cs225::HSLAPixel & pixel = this->getPixel(x,y);
            temp->getPixel(z,w) = pixel;
          }
        }
      }
    }
  } else {
    for(unsigned int x = 0; x < width(); x++) {
      for(unsigned int y = 0; y < height(); y++) {
        cs225::HSLAPixel & pixel = this->getPixel(x,y);
        temp->getPixel((x * factor) , (y * factor)) = pixel;
      }
    }
  }
  unsigned int resizedWidth = factor * width();
  unsigned int resizedHeight = factor * height();
  resize(factor * width(), factor * height());

  for(unsigned int x = 0; x < resizedWidth; x++) {
    for(unsigned int y = 0; y < resizedHeight; y++){
      cs225::HSLAPixel & tempPixel = temp->getPixel(x,y);
      this->getPixel(x,y) = tempPixel;
    }
  }
  delete temp;
}

void Image::scale(unsigned w, unsigned h) {
  if (width() * (double) h / (double) height() <= w) {
    scale((double) h / (double) height());
  } else {
    scale((double) w / (double) width());
  }
}
