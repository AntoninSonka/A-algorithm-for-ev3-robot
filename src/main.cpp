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

    Tile grid[SIZE_Y][SIZE_X];
    setupGrid(grid);

    findPath(grid, coords{START_Y, START_X}, coords{FINISH_Y, FINISH_X}, 0);

    return 0;
}
