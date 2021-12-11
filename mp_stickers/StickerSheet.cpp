#include "StickerSheet.h"
#include <cmath>

StickerSheet::StickerSheet(const Image &picture, unsigned max)
{
    local_max = max;
    baseImage = new Image(picture);
    renderedImage = new Image();
    mySheet = new vector<ASticker>(local_max);
}

void StickerSheet::changeMaxStickers(unsigned max)
{
    mySheet->resize(max);
    mySheet->shrink_to_fit();
    local_max = max;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
{
    for (unsigned i = 0; i < local_max; i++)
    {
        if (mySheet->at(i).image == NULL)
        {
            mySheet->at(i).image = new Image(sticker);
            mySheet->at(i).x = x;
            mySheet->at(i).y = y;
            return i;
        }
    }
    return -1;
}
void StickerSheet::removeSticker(unsigned index)
{
    if (index < local_max)
    {
        delete mySheet->at(index).image;
        mySheet->erase(mySheet->begin()+index);
        changeMaxStickers(local_max);
    }
}


Image *StickerSheet::getSticker(unsigned index) { return mySheet->at(index).image; }

const StickerSheet &StickerSheet::operator=(const StickerSheet &other)
{
    if (this != &other)
    {
        destroy();
        copy(other);
    }
    return *this;
}
void StickerSheet::destroy()
{
    delete baseImage;
    delete renderedImage;
    for (unsigned i = 0; i < local_max; i++)
    {
        if (mySheet->at(i).image != NULL)
            delete mySheet->at(i).image;
    }
    delete mySheet;
    mySheet = NULL;
}
void StickerSheet::copy(const StickerSheet &other)
{
    local_max = other.local_max;
    baseImage = new Image(*(other.baseImage));
    renderedImage = new Image(*(other.renderedImage));
    mySheet = new vector<ASticker>(local_max);
    for (unsigned i = 0; i < local_max; i++)
    {
        if (other.mySheet->at(i).image != NULL)
        {
            mySheet->at(i).image = new Image(*other.mySheet->at(i).image);
            mySheet->at(i).x = other.mySheet->at(i).x;
            mySheet->at(i).y = other.mySheet->at(i).y;
        }
    }
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y)
{
    if (index < local_max)
    {
        if (mySheet->at(index).image != NULL)
        {
            mySheet->at(index).x = x;
            mySheet->at(index).y = y;
            return true;
        }
    }
    return false;
}
StickerSheet::StickerSheet(const StickerSheet &other) { copy(other); }
StickerSheet::~StickerSheet() { destroy(); }


Image StickerSheet::render() const
{
    unsigned maxX = baseImage->width();
    unsigned maxY = baseImage->height();

    for (unsigned i = 0; i < local_max; i++)
    {
        ASticker sticker = mySheet->at(i);

        if (sticker.image != NULL)
        {
            maxX = std::max(maxX, sticker.x + sticker.image->width());
            maxY = std::max(maxY, sticker.y + sticker.image->height());
        }
    }
    *renderedImage = *baseImage;

    renderedImage->resize(maxX, maxY);

    for (unsigned i = 0; i < local_max; i++)
    {
        if (mySheet->at(i).image != NULL)
        {

            ASticker sticker = mySheet->at(i);
            for (unsigned i = 0; i < sticker.image->width(); i++)
            {
                for (unsigned j = 0; j < sticker.image->height(); j++)
                {
                    HSLAPixel &basePixel = renderedImage->getPixel(i + sticker.x, j + sticker.y);
                    HSLAPixel &stickerPixel = sticker.image->getPixel(i, j);
                    if (stickerPixel.a != 0) {
                        basePixel = stickerPixel;
                    }
                }
            }
        }
    }
    return *renderedImage;
}