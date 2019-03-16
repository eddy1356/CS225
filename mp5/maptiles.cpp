/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
#include "point.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     //make MosaicCanvas ptr/object
     MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
     //MosaicCanvas* ptr = &canvas;
     vector<Point<3>> tilepoint;
     map<Point<3>, TileImage*> tiles;
     Point<3> curr;

     //Point vector of theTiles
     unsigned long i=0;
     while(i<theTiles.size()){
       HSLAPixel tileavg = theTiles[i].getAverageColor();
       curr = Point<3>(tileavg.h, tileavg.s, tileavg.l);
       tiles[curr] = &theTiles[i];
       tilepoint.push_back(curr);
       i++;
     }

     //build KDTree of tilepoints
     KDTree<3> tiletree = KDTree<3>(tilepoint);

     //traverse through all regions and replace with closest tiles
     int k=0;
     int j=0;
     while(k!=theSource.getRows()){
       while(j!=theSource.getColumns()){
         HSLAPixel pointavg = theSource.getRegionColor(k,j);
         curr = Point<3>(pointavg.h, pointavg.s, pointavg.l);
         //find closest tile to curr & replace
         Point<3> close = tiletree.findNearestNeighbor(curr);
         canvas->setTile(k,j,tiles[close]);
         j++;
       }
       j=0;
       k++;
     }
    return canvas;

}


TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
