#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <chrono>
#include "grid.h"

#define MAX_DIMS 5

int16_t binarySearchPrefix(std::vector<std::string> arr, std::string prefix) {
    int l = 0;
    int r = arr.size() - 1;
    while (l <= r) {
        const int mid = l + (r - l) / 2;

        const int res = prefix.compare(arr[mid]);

        if (res == 0) {
            printf("%s, %s\n", arr[mid].c_str(), prefix.c_str());
            return mid;
        }

        // Checks if the word starts with the given prefix
        if (arr[mid].compare(0, prefix.size(), prefix) == 0) {
            return -2;
        } else {
            if (res > 0) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }

    return -1;
}

bool naive(Grid* grid, std::vector<std::string> words) {
    for (size_t i = 0; i < grid->getGridSize() * grid->getGridSize(); i++) {
        for (int dir = 1; dir < 4; dir++) {
            uint8_t deltaX = dir & 0x01;
            uint8_t deltaY = ((dir >> 1) & 0x01);
            uint8_t delta = deltaX + deltaY * grid->getGridSize();

            size_t curTile = i;

            std::string prefix = "";

            int16_t result = 0;
            do {
                if ((curTile % grid->getGridSize()) + deltaX > grid->getGridSize() || (curTile / grid->getGridSize()) + deltaY > grid->getGridSize()) break;

                prefix += grid->getTile(curTile);

                curTile += delta;
            } while ((result = binarySearchPrefix(words, prefix)) == -2);

            if (result >= 0) {
                words.erase(words.begin() + result);
                words.shrink_to_fit();
                uint8_t startX = i % grid->getGridSize();
                uint8_t startY = i / grid->getGridSize();

                uint8_t curTileX = curTile % grid->getGridSize();
                uint8_t curTileY = curTile / grid->getGridSize();

                printf("    Start: (%u, %u)\n    Dir: (%u, %u)\n    End: (%u, %u)\n\n", startX, startY, deltaX, deltaY, curTileX, curTileY);
                if (words.empty()) return true;
            }
        }
    }

    return false;
}

int main() {
    size_t gridSize = 6;
    Grid* grid = new Grid(gridSize);


    uint8_t* ptr;
    uint8_t tiles[gridSize * gridSize] = {
        'N', 'K', 'L', 'L', 'K', 'C',
        'R', 'B', 'S', 'L', 'K', 'A',
        'E', 'L', 'I', 'L', 'C', 'N',
        'D', 'I', 'F', 'R', 'N', 'D',
        'Y', 'K', 'C', 'U', 'D', 'Y',
        'Y', 'E', 'F', 'K', 'M', 'N'
    };

    std::vector<std::string> words;
    std::string wordsArr[5] = {"BIRD", "CANDY", "FUN", "LIKE", "RED"};
    words.insert(words.begin(), std::begin(wordsArr), std::end(wordsArr));

    grid->setTiles(tiles);

    auto start = std::chrono::steady_clock::now();
    naive(grid, words);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "Speed (sec): " << elapsed_seconds.count() << std::endl;
    
    delete grid;
    return 0;
}