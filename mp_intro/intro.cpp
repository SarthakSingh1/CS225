#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
using cs225::PNG;
using cs225::HSLAPixel;
void rotate(std::string inputFile, std::string outputFile) {
  PNG input_;
  input_.readFromFile(inputFile);
  PNG output_(input_.width(), input_.height());

  for(unsigned x = 0; x<input_.width();x++){
    for(unsigned y = 0; y<input_.height();y++){
      HSLAPixel & inputPixel = input_.getPixel(x,y);
      HSLAPixel & outputPixel = output_.getPixel(input_.width() - x - 1,input_.height()-y-1);
      outputPixel = inputPixel ;
    }
  }

  output_.writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
unsigned width_third = width/3;
unsigned height_third = height/3;
  for(unsigned x = 0; x<png.width();x++){
    for(unsigned y = 0; y<png.height();y++){
    HSLAPixel & inputPixel = png.getPixel(x,y);
    if(x > (width_third *2) || y>(height_third *2)){
      inputPixel.l=150;
      inputPixel.h=30;}
    else if(x > width_third || y>height_third){
      inputPixel.l = 75;
      inputPixel.h=150;}
    else{
      inputPixel.l=300;
      inputPixel.h=75;}
    }
  }
  // TODO: Part 3

  return png;
}
