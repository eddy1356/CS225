#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include "Image.h"

using namespace cs225;

class StickerSheet{
  public:
    // Initializes this StickerSheet with a base picture
    // and the ability to hold a max number of stickers
    // with indices 0 through max - 1
    StickerSheet(const Image &picture, unsigned max);

    // Destructor
    ~StickerSheet();

    StickerSheet(const StickerSheet & other);

    // The assignment operator for the STickerSheet class
    const StickerSheet& operator=(const StickerSheet & other);

    void changeMaxStickers(unsigned max);

    int addSticker(Image & sticker, unsigned x, unsigned y);

    bool translate(unsigned index, unsigned x, unsigned y);

    void removeSticker(unsigned index);

    Image* getSticker(unsigned index) const;

    Image render() const;

  private:
    unsigned maxSticker;
    unsigned layer;
    Image * baseImage;
    unsigned * xCoordinate;
    unsigned * yCoordinate;
    Image ** stickers;

};

#endif
/*
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_
#include "Image.h"
using namespace cs225;

class StickerSheet{
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);

        StickerSheet const & operator= (const StickerSheet &other);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image *getSticker(unsigned index) const;
        Image render() const;

    private:
        unsigned max_;
        unsigned layer;
        Image **image;
        Image *base;
        unsigned* x;
        unsigned* y;

};

#endif
*/
