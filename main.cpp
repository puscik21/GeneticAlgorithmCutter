#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct coord {
    int x;
    int y;
    int rotation;
    int number;
};

vector<coord> smallBoards;

int compareBoards(coord* b1, coord* b2);
int getErrorHor(coord* b1, coord* b2);
int getErrorVer(coord* b1, coord* b2);

vector<coord> readBoards() {
    ifstream file("maleplyty.txt");
    int width;
    int height;
    while (file >> width && file >> height ){
        coord smallBoard = {width, height};
        smallBoards.push_back(smallBoard);
    }
    return smallBoards;
}

vector<coord> readOutput() {
    ifstream file("output.txt");
    if (file.bad()) {
        return vector<coord>();
    }
    vector<coord> coords;
    int surface;
    int x, y;
    int number = 0;
    bool rotation;
    file >> surface;
//    file >> x;
//    file >> y;
    while (file >> x && file >> y){
        file >> x;
        file >> y;
        file >> rotation;
        coord coord = {x, y, rotation, number};
        coords.push_back(coord);
    }
    return coords;
}

void overlapCheck() {
    vector<coord> positions = readOutput();
//    cout << "(" << smallBoards[0].x << ", " << smallBoards[0].y << ") - " << positions[0].x << ", " << positions[0].y << endl;
//    cout << "(" << smallBoards[1].x << ", " << smallBoards[1].y << ") - " << positions[1].x << ", " << positions[1].y << endl;
    cout << compareBoards(&positions[0], &positions[1]) << endl;
}

// TODO przerobic ta metode zeby jeszcze pole zwracalo z tego co nachodzi/wychodzi zle
int compareBoards(coord* b1, coord* b2) {
    // todo if rotation, then swap height and width for check (probably create new structure)
    smallBoards[0] = {500, 500};
    smallBoards[1] = {400, 50};
    b1 = new coord{0, 0, 0, 0};
    b2 = new coord{300, 200, 0, 1};
    int errorHor = getErrorHor(b1, b2);
    int errorVer = getErrorVer(b1, b2);

    cout << "Hor: " << errorHor << endl;
    cout << "Ver: " << errorVer << endl;
    return false;
}

int getErrorHor(coord* b1, coord* b2) {
    // todo if rotation, then swap height and width for check (probably create new structure)
    coord* boardL;
    coord* boardR;
    if (b1->x <= b2->x) {
        boardL = b1;
        boardR = b2;
    } else {
        boardL = b2;
        boardR = b1;
    }

    int leftBoardEnd = boardL->x + smallBoards[boardL->number].x;
    int rightBoardStart = boardR->x;

    int errorHor = 0;
    int maxError = leftBoardEnd - rightBoardStart;
    if (leftBoardEnd > rightBoardStart) {
        errorHor = min(smallBoards[boardR->number].x, maxError);
    }
    return errorHor;
}

int getErrorVer(coord* b1, coord* b2) {
    // todo if rotation, then swap height and width for check (probably create new structure)
    coord* boardTop;
    coord* boardBot;
    if (b1->y <= b2->y) {
        boardTop = b1;
        boardBot = b2;
    } else {
        boardTop = b2;
        boardBot = b1;
    }

    int topBoardEnd = boardTop->y + smallBoards[boardTop->number].y;
    int botBoardStart = boardBot->y;

    int errorVec = 0;
    int maxError = topBoardEnd - botBoardStart;
    if (topBoardEnd > botBoardStart) {
        errorVec = min(smallBoards[boardBot->number].y, maxError);
    }
    return errorVec;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    readBoards();
    overlapCheck();
    return 0;
}