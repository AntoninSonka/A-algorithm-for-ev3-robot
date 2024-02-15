#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>


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
    START_X = 2,
    FINISH_Y = 6,
    FINISH_X = 6,
    TIME = 250
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
    /*
     * bool descovered
     * descovered is true if position is in closed or in opend
     * moving sequence is creating an virtual grid where non descovered tiles are walls. with that bot will move effectively and correctly
    */
};

void clearScreen();

void setupGrid(Tile grid[SIZE_Y][SIZE_X]);

void printGrid(Tile grid[SIZE_Y][SIZE_X], coords position);

int calculateHCost(coords position, coords finish);

int calculateGCost(Tile grid[SIZE_Y][SIZE_X], coords position, coords start);

coords minElement(std::vector<coords> vec, Tile grid[SIZE_Y][SIZE_X]); //returns best new coords of a tile to descover based on lowest f cost and after on lowest h cost

int indexByCoords(std::vector<coords> vec, coords position);

bool compareGCosts(coords position, Tile grid[SIZE_Y][SIZE_X], coords newParents, coords start);

void descoverTile(coords current, coords neighbour, Tile grid[SIZE_Y][SIZE_X], std::vector<coords>& openVec, std::vector<coords> closedVec, coords start, coords finish);

void findPath(Tile grid[SIZE_Y][SIZE_X], coords start, coords finish, bool skipRide);

void rideToNewTile(std::vector<coords>& openVec, std::vector<coords>& closedVec, coords newStart, coords newFinish);
