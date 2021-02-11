#include "grid.h"
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <memory.h>

Grid::Grid(size_t gridSize) {
    this->_gridSize = gridSize;

    _tiles = new uint8_t[gridSize * _gridSize];
}

Grid::~Grid() {
    delete[] _tiles;
}

size_t Grid::getIndex(size_t x, size_t y) {
    return x + y * _gridSize;
}

void Grid::setTiles(uint8_t* tiles) {
    memcpy(this->_tiles, tiles, _gridSize * _gridSize);
}

uint8_t Grid::getTile(size_t x, size_t y) {
    return this->_tiles[getIndex(x, y)];
}

void Grid::setTile(size_t x, size_t y, uint8_t newChar) {
    this->_tiles[getIndex(x, y)] = newChar;
}

uint8_t Grid::getTile(size_t index) {
    return _tiles[index];
}

size_t Grid::getGridSize() {
    return _gridSize;
}
