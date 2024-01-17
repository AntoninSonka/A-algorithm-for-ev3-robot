#pragma once

#include <vector>
#include <iostream>


#ifdef _WIN32
    const bool LINUX = false;
#elif __linux__
    const bool LINUX = true;
#else
    #error Unsupported operating system
#endif


enum {
    SIZE_Y = 8,
    SIZE_X = 8,
    START_Y = 2,
    START_X = 4,
    FINISH_Y = 4,
    FINISH_X = 6,
    TIME = 100
};

struct coords{
    int y;
    int x;
};

class Tile{
public:
    coords position;
    coords prevPosition = {-1, -1}; //previous position
    bool isWall = false;
    int hCost = 0; //heuristic cost - the distance from current tile to the finish
    int gCost = 0; //the distance from current tile to the start through visited tiles
    int fCost = 1000;
};

void clearScreen();

void setupGrid(Tile grid[SIZE_Y][SIZE_X]);

void printGrid(Tile grid[SIZE_Y][SIZE_X], coords position);

int calculateHCost(coords position);

int calculateGCost(Tile grid[SIZE_Y][SIZE_X], coords position);

coords minElement(std::vector<coords> vec, Tile grid[SIZE_Y][SIZE_X]);

int indexByCoords(std::vector<coords> vec, coords position);

bool compareGCosts(coords position, Tile grid[SIZE_Y][SIZE_X], coords newParents);

void descoverTile(coords current, coords neighbour, Tile grid[SIZE_Y][SIZE_X], std::vector<coords>& openVec, std::vector<coords> closedVec);
