#include <algorithm>
#include <chrono>
#include <thread>
#include "aStar.h"


/* A* algorithm for EV3 robot.
 *
 * !After traping robot in unbeateble maze segmentation foult occurs!
 * 
 * Starting values can be changed in aStar.h, they are enums.
 * Note that when you change size of maze, you have to change 2D boolean array in function setupGrid(...).
 *
 * todo list:
     *
     * High priority
     *
     * TODO Implement better Error Handeling.
     * TODO I have to implement EV3 robot into this code.
     * 
     *
     * Low priority
     *
     * TODO Possibly swap arrays for priority queues
 *
 *
 * Author: Antonín Šonka
 * Co-Author: Oliver Špaček
*/


int main(){

    std::vector<coords> openVec;
    std::vector<coords> closedVec;

    Tile grid[SIZE_Y][SIZE_X];
    setupGrid(grid);

    Tile blankGrid[SIZE_Y][SIZE_X];
    setupGrid(blankGrid);

    grid[START_Y][START_X].hCost = calculateHCost(coords{START_Y, START_X});
    grid[START_Y][START_X].gCost = calculateGCost(grid, coords{START_Y, START_X});
    grid[START_Y][START_X].fCost = grid[START_Y][START_X].hCost + grid[START_Y][START_X].gCost;

    openVec.push_back(coords{START_Y, START_X});

    while(true){
        coords current = minElement(openVec, grid);

        printGrid(blankGrid, current);
        std::cout << "\nF cost: " << grid[current.y][current.x].fCost << "\n";

        openVec.erase(openVec.begin() + indexByCoords(openVec, current));
        closedVec.push_back(current);

        if(current.y == FINISH_Y && current.x == FINISH_X){

            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            clearScreen();

            break;
        }

        if((current.y - 1) >= 0){
            descoverTile(current, coords{current.y - 1, current.x}, grid, openVec, closedVec);
        }
        if((current.y + 1) < SIZE_Y){
            descoverTile(current, coords{current.y + 1, current.x}, grid, openVec, closedVec);
        }
        if((current.x - 1) >= 0){
            descoverTile(current, coords{current.y, current.x - 1}, grid, openVec, closedVec);
        }
        if((current.x + 1) < SIZE_X){
            descoverTile(current, coords{current.y, current.x + 1}, grid, openVec, closedVec);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
        clearScreen();
    }
    
    coords current = {FINISH_Y, FINISH_X};

    while(current.y != START_Y || current.x != START_X){
        printGrid(blankGrid, current);
        std::cout << "\nF cost: " << grid[current.y][current.x].fCost << "\n";

        current = grid[current.y][current.x].prevPosition;

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        clearScreen();
    }

    printGrid(blankGrid, current);
    std::cout << "\nF cost: " << grid[current.y][current.x].fCost << "\n";
    std::cout << "success\n";

    return 0;
}
