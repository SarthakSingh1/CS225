#include "Image.h"
#include "StickerSheet.h"

int main() {
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png

Image one, two, three, four;

one.readFromFile("1.png");
two.readFromFile("2.png");
three.readFromFile("3.png");
four.readFromFile("4.png");


StickerSheet testSheet(one,3);

testSheet.addSticker(four, 100, 200);
testSheet.addSticker(three, 25, 35);
testSheet.addSticker(two, 2000, 2000);

Image final = testSheet.render();

final.writeToFile("myImage.png");

  return 0;
}
