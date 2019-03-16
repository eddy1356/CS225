#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image segFault; segFault.readFromFile("mySticker/base.png");
  segFault.scale(2.0);
  Image a;    a.readFromFile("mySticker/1.png");
  Image b;    b.readFromFile("mySticker/2.png");
  Image c;    c.readFromFile("mySticker/3.png");
  Image d;    d.readFromFile("mySticker/4.png");
  d.scale(1.5);
  StickerSheet s1(segFault, 4);
  s1.addSticker(a, 400, 70);
  s1.addSticker(b, 500, 150);
  s1.addSticker(c, 550, 310);
  s1.addSticker(d, 200, 520);
  Image image = s1.render();

  image.writeToFile("myImage.png");
  return 0;
}
