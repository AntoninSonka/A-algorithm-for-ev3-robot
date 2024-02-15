#include "aStar.h"

void clearScreen(){
    if(!LINUX){
        system("cls");
    }
    else{
        system("clear");
    }
}

void setupGrid(Tile grid[SIZE_Y][SIZE_X]){
    bool wallArr[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    for(int i = 0; i < SIZE_Y; i++){
        for(int j = 0; j < SIZE_X; j++){
            grid[i][j].isWall = wallArr[i][j];
            grid[i][j].position = {i, j};
        }
    }
}

void printGrid(Tile grid[SIZE_Y][SIZE_X], coords position){
    for(int i = 0; i < SIZE_Y; i++){
        for(int j = 0; j < SIZE_X; j++){
            if(i == FINISH_Y && j == FINISH_X){
                std::cout << "\033[33m";
            }
            else if(i == START_Y && j == START_X){
                std::cout << "\033[32m";
            }
            else if(i == position.y && j == position.x){
                std::cout << "\033[34m";
            }
            else if(grid[i][j].isWall){
                std::cout << "\033[31m";
            }
            if(grid[i][j].isWall){
                std::cout << "X ";
            }
            else{
                //std::cout << ((grid[i][j].fCost == 1000) ? 0 : grid[i][j].fCost) << " ";
                std::cout << 0 << " ";
            }
            std::cout << "\033[0m";
        }
        std::cout << "\n";
    }
}

int calculateHCost(coords position, coords finish){
    int hCost = 0;
    while(position.y != finish.y || position.x != finish.x){
        if(position.y < finish.y){
            position.y++;
            hCost++;
        }
        else if(position.y > finish.y){
            position.y--;
            hCost++;
        }
        if(position.x < finish.x){
            position.x++;
            hCost++;
        }
        else if(position.x > finish.x){
            position.x--;
            hCost++;
        }
    }
    return hCost;
}

int calculateGCost(Tile grid[SIZE_Y][SIZE_X], coords position, coords start){
    int gCost = 0;
    while(position.y != start.y || position.x != start.x){
        coords original = position;
        position = grid[original.y][original.x].prevPosition;
        gCost++;
    }
    return gCost;
}

coords minElement(std::vector<coords> vec, Tile grid[SIZE_Y][SIZE_X]){
    int lowestF = 2000;
    coords lowestCoords;
    for(int i = 0; i < vec.size(); i++){
        if(grid[vec[i].y][vec[i].x].fCost < lowestF){
            lowestF = grid[vec[i].y][vec[i].x].fCost;
            lowestCoords = vec[i];
        }
    }
    int lowestH = 2000;
    for(int i = 0; i < vec.size(); i++){
        if(grid[vec[i].y][vec[i].x].fCost == lowestF){
            if(grid[vec[i].y][vec[i].x].hCost < lowestH){
                lowestH = grid[vec[i].y][vec[i].x].hCost;
                lowestCoords = vec[i];
            }
        }
    }
    return lowestCoords;
}

int indexByCoords(std::vector<coords> vec, coords position){
    for(int i = 0; i < vec.size(); i++){
        if(vec[i].y == position.y && vec[i].x == position.x){
            return i;
        }
    }
    return -1;
}

bool compareGCosts(coords position, Tile grid[SIZE_Y][SIZE_X], coords newParents, coords start){
    int originalG = grid[position.y][position.x].gCost;

    coords originalParents = grid[position.y][position.x].prevPosition;

    grid[position.y][position.x].prevPosition = newParents;

    int newG = calculateGCost(grid, position, start);

    if(newG < originalG){
        grid[position.y][position.x].prevPosition = originalParents;
        return 1;
    }

    grid[position.y][position.x].prevPosition = originalParents;
    return 0;
}

void descoverTile(coords current, coords neighbour, Tile grid[SIZE_Y][SIZE_X], std::vector<coords>& openVec, std::vector<coords> closedVec, coords start, coords finish){

    bool isInClosed = (indexByCoords(closedVec, neighbour) + 1);

    if(grid[neighbour.y][neighbour.x].isWall || isInClosed){//tady se musi checkovat pro to, jesti tam neni zed, to bude delat robot sam
        return;
    }

    bool isInOpen = 0;

    if(!openVec.empty()){
        isInOpen = (indexByCoords(openVec, neighbour) + 1);
    }

    bool compareGCostsSuccess = 0;

    if(!(grid[neighbour.y][neighbour.x].prevPosition.y == -1)){
        if(compareGCosts(neighbour, grid, current, start)){
            compareGCostsSuccess = 1;
        }
    }

    if(compareGCostsSuccess || !isInOpen){
        grid[neighbour.y][neighbour.x].prevPosition = current;
        grid[neighbour.y][neighbour.x].hCost = calculateHCost(neighbour, finish);
        grid[neighbour.y][neighbour.x].gCost = calculateGCost(grid, neighbour, start);
        grid[neighbour.y][neighbour.x].fCost = grid[neighbour.y][neighbour.x].hCost + grid[neighbour.y][neighbour.x].gCost;
        if(!isInOpen){
            openVec.push_back(neighbour);
        }
    }
}

void findPath(Tile grid[SIZE_Y][SIZE_X], coords start, coords finish, bool skipRide){
    std::vector<coords> openVec;
    std::vector<coords> closedVec;

    Tile blankGrid[SIZE_Y][SIZE_X];
    setupGrid(blankGrid);

    grid[start.y][start.x].hCost = calculateHCost(start, finish);
    grid[start.y][start.x].gCost = calculateGCost(grid, start, start);
    grid[start.y][start.x].fCost = grid[start.y][start.x].hCost + grid[start.y][start.x].gCost;

    openVec.push_back(coords{start.y, start.x});
    coords oldCurrent = start;

    while(true){
        coords current = minElement(openVec, grid);

        if(!skipRide){
            rideToNewTile(openVec, closedVec, current, oldCurrent);
        }

        if(!skipRide){
            printGrid(blankGrid, current);
            std::cout << "\nF cost: " << grid[current.y][current.x].fCost << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        openVec.erase(openVec.begin() + indexByCoords(openVec, current));
        closedVec.push_back(current);

        if(current.y == finish.y && current.x == finish.x){
            if(!skipRide){
                std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
                clearScreen();
            }

            break;
        }

        if((current.y - 1) >= 0){
            descoverTile(current, coords{current.y - 1, current.x}, grid, openVec, closedVec, start, finish);
        }
        if((current.y + 1) < SIZE_Y){
            descoverTile(current, coords{current.y + 1, current.x}, grid, openVec, closedVec, start, finish);
        }
        if((current.x - 1) >= 0){
            descoverTile(current, coords{current.y, current.x - 1}, grid, openVec, closedVec, start, finish);
        }
        if((current.x + 1) < SIZE_X){
            descoverTile(current, coords{current.y, current.x + 1}, grid, openVec, closedVec, start, finish);
        }
        
        if(!skipRide){
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
            clearScreen();
        }
        oldCurrent = current;
    }

    coords current = {finish.y, finish.x};

    while(current.y != start.y || current.x != start.x){
        if(skipRide){
            printGrid(grid, current);
        }
        else{
            printGrid(blankGrid, current);
        }
        std::cout << "\nF cost: " << grid[current.y][current.x].fCost << "\n";

        current = grid[current.y][current.x].prevPosition; // prejizdeni

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        clearScreen();
    }
    
    if(skipRide){
        printGrid(grid, current);
    }
    else{
        printGrid(blankGrid, current);
    }
    std::cout << "\nF cost: " << grid[current.y][current.x].fCost << "\n";
    std::cout << "success\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    clearScreen();
}

void rideToNewTile(std::vector<coords>& openVec, std::vector<coords>& closedVec, coords newStart, coords newFinish){
    Tile grid[SIZE_Y][SIZE_X];
    for(int i = 0; i < SIZE_Y; i++){
        for(int j = 0; j < SIZE_X; j++){
            grid[i][j].isWall = true;
            grid[i][j].position = coords{i, j};
        }
    }
    for(int i = 0; i < openVec.size(); i++){
        grid[openVec[i].y][openVec[i].x].isWall = false;
    }
    for(int i = 0; i < closedVec.size(); i++){
        grid[closedVec[i].y][closedVec[i].x].isWall = false;
    }

    findPath(grid, newStart, newFinish, 1);
}
