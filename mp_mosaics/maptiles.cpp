/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    int rows = theSource.getRows();
    int columns = theSource.getColumns();
    vector<Point<3> > tileValues ;
    map<Point<3>, size_t> mapper;
    MosaicCanvas *myCanvas = new MosaicCanvas(rows, columns);

    for (unsigned i = 0; i < theTiles.size(); i++){
        LUVAPixel pixel = theTiles[i].getAverageColor();
        Point<3> currPoint = convertToXYZ(pixel);
        tileValues.push_back(currPoint);
        mapper.insert(pair<Point<3>, size_t>(currPoint,i));
    }
    KDTree<3> tiles(tileValues);


    for(int x = 0; x < rows;x++){
        for(int y = 0; y<columns; y++){
            Point<3> currReigon = convertToXYZ(theSource.getRegionColor(x, y));
            Point<3> neighbor = tiles.findNearestNeighbor(currReigon);
            int index = mapper[neighbor];
            myCanvas->setTile(x, y, &theTiles[index]);
        }
    }
    return myCanvas;
}