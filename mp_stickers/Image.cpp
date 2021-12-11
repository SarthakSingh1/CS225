#include "Image.h"
void Image::darken(){
     for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel=getPixel(x,y);
            if(inputPixel.l>.1)
                inputPixel.l -=.1;
            else
                inputPixel.l = 0;
        }
    }
}

void Image::darken(double amount){
     for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel =getPixel(x,y);
            if(inputPixel.l>amount)
                inputPixel.l-=amount;
            else
                inputPixel.l=0;
        }
    }
}
void Image::lighten(){
     for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel=getPixel(x,y);
            if(inputPixel.l<.9)
                inputPixel.l +=.1;
            else
                inputPixel.l = 1;
         }
    }
}
void Image::lighten(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel = getPixel(x,y);
            if(inputPixel.l+amount<1)
                inputPixel.l+=amount;
            else
                inputPixel.l=1;
        }
    }
   
}
void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++)
    {
        for (unsigned y = 0; y < height(); y++)
        {
            HSLAPixel &pixel = getPixel(x, y);
            pixel.h += degrees;
            while (pixel.h < 0.0)
                pixel.h += 360.0;
            while (pixel.h > 360.0)
                pixel.h -= 360.0;
        }
    }
}	
void Image::saturate(){
 for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel=getPixel(x,y);
            if(inputPixel.s<.9)
                inputPixel.s +=.1;
            else
                inputPixel.s = 1;
         }
    }
}
void Image::saturate(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel = getPixel(x,y);
            if(inputPixel.s+amount<1)
                inputPixel.s+=amount;
            else
                inputPixel.s=1;
        }
    }
}
void Image::desaturate(){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel=getPixel(x,y);
            if(inputPixel.s>.1)
                inputPixel.s -=.1;
            else
                inputPixel.s = 0;
        }
    }
}
void Image::desaturate(double amount){
    for(unsigned x = 0; x<width();x++){
        for(unsigned y = 0; y<height();y++){
            cs225::HSLAPixel & inputPixel =getPixel(x,y);
            if(inputPixel.s>amount)
                inputPixel.s-=amount;
            else
                inputPixel.s=0;
        }
    }
}

void Image::illinify(){
for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      if(pixel.h<294  && pixel.h>113)
        pixel.h = 216;
      else
        pixel.h = 11;
    }
  }
}
void Image::grayscale(){
for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
      HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0;
    }
  }
}

void Image::scale(double factor){
Image temp = *this;
resize(width() *factor, height() * factor);
for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        HSLAPixel & pixel = getPixel(x,y);
        HSLAPixel & tempPixel = temp.getPixel(x/factor, y/factor);
        pixel = tempPixel;
    }
}

}


void Image::scale(unsigned w,unsigned h){
Image temp = *this;
resize(w,h);
unsigned xFactor = (double)w / width();
unsigned yFactor = (double)h/ height();

scale(std::min(xFactor,yFactor));

}