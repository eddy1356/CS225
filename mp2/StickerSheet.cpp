#include "StickerSheet.h"
#include "Image.h"
#include <algorithm>

using namespace std;
using namespace cs225;

StickerSheet::StickerSheet(const Image & picture, unsigned max) {
  maxSticker = max;
  layer = 0;
  baseImage = new Image(picture);
  xCoordinate = new unsigned[maxSticker];
  yCoordinate = new unsigned[maxSticker];
  stickers = new Image*[maxSticker];
  for(unsigned i = 0; i < maxSticker; ++i){
    stickers[i] = NULL;
  }

}

StickerSheet::~StickerSheet() {
  delete[] yCoordinate;
  delete[] xCoordinate;
  delete[] stickers;
  delete baseImage;
}

StickerSheet::StickerSheet(const StickerSheet & other){
  maxSticker = other.maxSticker;
  layer = other.layer;
  baseImage = new Image(*(other.baseImage));
  xCoordinate = new unsigned[maxSticker];
  yCoordinate = new unsigned[maxSticker];
  stickers = new Image*[maxSticker];
  for(unsigned i = 0; i < maxSticker; ++i){
    stickers[i] = NULL;
  }

  for(unsigned i = 0; i < layer; ++i) {
    xCoordinate[i] = other.xCoordinate[i];
    yCoordinate[i] = other.yCoordinate[i];
    stickers[i] = new Image(*(other.stickers[i]));
  }
}

const StickerSheet& StickerSheet::operator=(const StickerSheet & other) {
  if(this == &other) {
    return *this;
  } else {
    //free memory
    delete[] stickers;
    delete[] yCoordinate;
    delete[] xCoordinate;
    delete baseImage;

    //get private values of the other
    maxSticker = other.maxSticker;
    layer = other.layer;
    this -> baseImage = new Image(*(other.baseImage));
    this -> xCoordinate = new unsigned[maxSticker];
    this -> yCoordinate = new unsigned[maxSticker];
    stickers = new Image*[maxSticker];
    //NULLing all stickers array
    for(unsigned i = 0; i < maxSticker; ++i) {
      stickers[i] = NULL;
    }
    //Assigning other's values into this
    for(unsigned i = 0; i < layer; ++i) {
      xCoordinate[i] = other.xCoordinate[i];
      yCoordinate[i] = other.yCoordinate[i];
      stickers[i] = new Image(*(other.stickers[i]));
    }
    return other;
  }
}
void StickerSheet::changeMaxStickers(unsigned max){
  /*
  three cases:
  1. max == maxSticker
  2. max > maxSticker : higher max value
  3. max < maxSticker : lower max value
      - check if layer > max  or max > layer or max == layer
  */
  // case 1
  if(max == maxSticker) {
    return;
  }
  //case 2
  else if(max > maxSticker) {
    //making a temporary variables to transfer the values
    Image * tempBase = new Image(*baseImage);
    unsigned * tempX = new unsigned[max];
    unsigned * tempY = new unsigned[max];
    Image ** tempStickers = new Image*[max];
    for(unsigned i = 0; i < max; ++i){
      tempStickers[i] = NULL;
    }

    //copy the original values into temp var
    for(unsigned i = 0; i < this->layer; ++i){
      tempX[i] = xCoordinate[i];
      tempY[i] = yCoordinate[i];
      tempStickers[i] = new Image(*(stickers[i]));
    }

    //free original values in order to transfer values from temp to original
    delete[] stickers;
    delete[] yCoordinate;
    delete[] xCoordinate;
    delete baseImage;

    //place the temp into the original
    maxSticker = max;
    baseImage = tempBase;
    xCoordinate = tempX;
    yCoordinate = tempY;
    stickers = tempStickers;
  }
  //case 3
  else {
    //making a temporary variables to transfer the values
    Image * tempBase = new Image(*(baseImage));
    unsigned * tempX = new unsigned[max];
    unsigned * tempY = new unsigned[max];
    Image ** tempStickers = new Image*[max];
    for(unsigned i = 0; i < max; ++i) {
      tempStickers[i] = NULL;
    }
    //copy the original values into temp var
    //check if (layer > max)  or (max >= layer)
    if(layer > max) {
      for(unsigned i = 0; i < max; ++i){
        tempX[i] = xCoordinate[i];
        tempY[i] = yCoordinate[i];
        tempStickers[i] = new Image(*(stickers[i]));
      }
    } else {
      for(unsigned i = 0; i < layer; ++i) {
        tempX[i] = xCoordinate[i];
        tempY[i] = yCoordinate[i];
        tempStickers[i] = new Image(*(stickers[i]));
      }
    }
    //free original values in order to transfer values from temp to original
    delete[] stickers;
    delete[] yCoordinate;
    delete[] xCoordinate;
    delete baseImage;
    //place the temp into the original
    maxSticker = max;
    layer = std::min(max,layer);
    baseImage = tempBase;
    xCoordinate = tempX;
    yCoordinate = tempY;
    stickers = tempStickers;

  }
}

int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {
  /*
  three cases:
  1. layer == maxSticker : can't add sticker
  2. layer > maxSticker : not possible
  3. layer < maxSticker : add sticker and layer++
  */
  //case 1 & 2
  if(layer > maxSticker || layer == maxSticker) {
    return -1;
  }
  //case 3
  else {
    xCoordinate[layer] = x;
    yCoordinate[layer] = y;
    stickers[layer] = new Image(sticker);
    ++layer;
    return layer-1;
  }
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  /*
  two cases
  1. layer > index : translate and return true
  2. layer <= index : return false
  */
  //case 1
  if(layer > index) {
    xCoordinate[index] = x;
    yCoordinate[index] = y;
    return true;
  }
  // case 2
  else {
    return false;
  }
}

void StickerSheet::removeSticker(unsigned index) {
  /*
  index is zero-based
  layer is one-based
  Possible cases:
  1. first element : (index == 0)
  2. mid or last element : (index < layer)
  Impossible cases:
  1. no element : (index >= layer)
  2. out of max range: (index >= maxSticker)
  */
  // Impossible cases
  if(index >= layer || index >= maxSticker || (int) index < 0) {
    return;
  }
  //Possible case 1
  else if(index == 0) {
    //making a temporary variables to transfer the values
    Image * tempBase = new Image(*baseImage);
    unsigned * tempX = new unsigned[maxSticker];
    unsigned * tempY = new unsigned[maxSticker];
    Image ** tempStickers = new Image*[maxSticker];
    for(unsigned i = 0; i < maxSticker; ++i) {
      tempStickers[i] = NULL;
    }
    //copy the original values without index value
    //original stickers[1] < stickers[i] < stickers[layer]
    for(unsigned i = 1; i < layer; ++i) {
      tempX[i - 1] = xCoordinate[i];
      tempY[i - 1] = yCoordinate[i];
      if(stickers[i]!=NULL)
        tempStickers[i - 1] = new Image(*(stickers[i]));
    }
    //free the original data
    delete[] stickers;
    delete[] yCoordinate;
    delete[] xCoordinate;
    delete baseImage;

    // assign temp to original
    layer--;
    baseImage = tempBase;
    xCoordinate = tempX;
    yCoordinate = tempY;
    stickers = tempStickers;
  }
  //Possible case 2 : (index < layer)
  else {
    //making a temporary variables to transfer the values
    Image * tempBase = new Image(*baseImage);
    unsigned * tempX = new unsigned[maxSticker];
    unsigned * tempY = new unsigned[maxSticker];
    Image ** tempStickers = new Image*[maxSticker];
    for(unsigned i = 0; i < maxSticker; ++i) {
      tempStickers[i] = NULL;
    }
    //copy the original values without index value
    //original stickers[0] < stickers[i] < stickers[index]
    for(unsigned i = 0; i < index; ++i) {
      tempX[i] = xCoordinate[i];
      tempY[i] = yCoordinate[i];
      if(stickers[i]!=NULL)
        tempStickers[i] = new Image(*(stickers[i]));
    }
    //original stickers[index] < stickers[i] < stickers[layer]
    for(unsigned i = index; i < layer - 1; ++i) {
      tempX[i] = xCoordinate[i + 1];
      tempY[i] = yCoordinate[i + 1];
      tempStickers[i] = new Image(*(stickers[i + 1]));
    }

    //free the original data
    delete[] stickers;
    delete[] yCoordinate;
    delete[] xCoordinate;
    delete baseImage;

    // assign temp to original
    layer--;
    baseImage = tempBase;
    xCoordinate = tempX;
    yCoordinate = tempY;
    stickers = tempStickers;
  }
}

Image * StickerSheet::getSticker(unsigned index) const{
  if(index >= layer) {
    return NULL;
  } else {
    return stickers[index];
  }
}

Image StickerSheet::render() const{
  // very first "layer" = base Image
  //create tempBase so that base image itself isn't effected
  Image * tempBase = new Image(*baseImage);
  unsigned baseWidth = tempBase -> width();
  unsigned baseHeight = tempBase -> height();
  //go through the stickers[] for all the stickers (not NULL)
  //to paste onto the tempBase
  for(unsigned i = 0; i < maxSticker; ++i) {
    if(stickers[i] != NULL){
      unsigned x = xCoordinate[i];
      unsigned y = yCoordinate[i];
      unsigned width = stickers[i] -> width();
      unsigned height = stickers[i] -> height();
      unsigned xEnd = width + x;
      unsigned yEnd = height + y;
      //sticker going out of range of the baseTemp
      if(baseWidth < xEnd) {
        baseWidth = xEnd;
        tempBase -> resize(baseWidth, baseHeight);
      }
      if(baseHeight < yEnd) {
        baseHeight = yEnd;
        tempBase -> resize(baseWidth, baseHeight);
      }

      //replace tempBase's pixel starting at (j,k)
      //with sticker's pixels
      for(unsigned j = 0; j < width; ++j) {
        for(unsigned k = 0; k < height; ++k) {
          HSLAPixel & stickerPixel
            = stickers[i] -> getPixel(j,k);
          HSLAPixel & basePixel
            = tempBase -> getPixel(j + x, k + y);
          if(stickerPixel.a != 0.0) {
            basePixel = stickerPixel;
          }
        }
      }
    }
  }
  return *tempBase;
}
