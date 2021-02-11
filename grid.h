#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vector>

class Grid {
private:
    uint8_t* _tiles;
    size_t _gridSize;
public:
    Grid(size_t gridSize);
    ~Grid();

    size_t getIndex(size_t x, size_t y);
    void setTiles(uint8_t* tiles);
    void setTile(size_t x, size_t y, uint8_t newChar);
    uint8_t getTile(size_t x, size_t y);
    uint8_t getTile(size_t index);

    size_t getGridSize();
};