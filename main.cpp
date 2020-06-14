#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct coord {
    int x;
    int y;
    int rotation;
    int number;
};

const int BOARD_WIDTH = 2800;
const int BOARD_HEIGHT = 2070;
vector<coord> smallBoards;

int compareBoards(coord* b1, coord* b2);
int getErrorHor(coord* b1, coord* b2);
int getErrorVer(coord* b1, coord* b2);
int getBoardWidth(coord* coord);
int getBoardHeight(coord* coord);
int calculateExceededSurface(coord* coord);

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
    while (file >> x && file >> y){
        file >> x;
        file >> y;
        file >> rotation;
        coord coord = {x, y, rotation, number};
        coords.push_back(coord);
        number++;
    }
    return coords;
}

int getOverlapError() {
    vector<coord> positions = readOutput();
    long overlapSum = 0;
    for (int i = 0; i < smallBoards.size() - 1; i++) {
        for (int j = i + 1; j < smallBoards.size(); j++) {
            overlapSum += compareBoards(&positions[i], &positions[j]);
        }
    }
    return overlapSum;
}

int compareBoards(coord* b1, coord* b2) {
    int errorHor = getErrorHor(b1, b2);
    int errorVer = getErrorVer(b1, b2);
    return errorHor * errorVer;
}

int getErrorHor(coord* b1, coord* b2) {
    coord* boardL;
    coord* boardR;
    if (b1->x <= b2->x) {
        boardL = b1;
        boardR = b2;
    } else {
        boardL = b2;
        boardR = b1;
    }

    int leftBoardEnd = boardL->x + getBoardWidth(boardL);
    int rightBoardStart = boardR->x;

    int errorHor = 0;
    int maxError = leftBoardEnd - rightBoardStart;
    if (leftBoardEnd > rightBoardStart) {
        errorHor = min(getBoardWidth(boardR), maxError);
    }
    return errorHor;
}

int getErrorVer(coord* b1, coord* b2) {
    coord* boardTop;
    coord* boardBot;
    if (b1->y <= b2->y) {
        boardTop = b1;
        boardBot = b2;
    } else {
        boardTop = b2;
        boardBot = b1;
    }

    int topBoardEnd = boardTop->y + getBoardHeight(boardTop);
    int botBoardStart = boardBot->y;

    int errorVec = 0;
    int maxError = topBoardEnd - botBoardStart;
    if (topBoardEnd > botBoardStart) {
        errorVec = min(getBoardHeight(boardBot), maxError);
    }
    return errorVec;
}

int getExceedError() {
    vector<coord> positions = readOutput();
    long errorSum = 0;
    for (int i = 0; i < smallBoards.size() - 1; i++) {
        errorSum += calculateExceededSurface(&positions[i]);
    }
    return errorSum;
}

int calculateExceededSurface(coord* coord) {
    int sBoardWidth;
    int sBoardWHeight;
    if (coord->rotation == 0) {
        sBoardWidth = smallBoards[coord->number].x;
        sBoardWHeight = smallBoards[coord->number].y;
    } else {
        sBoardWidth = smallBoards[coord->number].y;
        sBoardWHeight = smallBoards[coord->number].x;
    }

    int errorRight = max(coord->x + sBoardWidth - BOARD_WIDTH, 0);
    int errorBot = max(coord->y + sBoardWHeight - BOARD_HEIGHT, 0);
    return errorRight * sBoardWHeight + errorBot * sBoardWidth - errorRight * errorBot;
}

int getBoardWidth(coord* coord) {
    if (coord->rotation == 0) {
        return smallBoards[coord->number].x;
    } else {
        return smallBoards[coord->number].y;
    }
}

int getBoardHeight(coord* coord) {
    if (coord->rotation == 0) {
        return smallBoards[coord->number].y;
    } else {
        return smallBoards[coord->number].x;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    readBoards();
    cout << "overlapSum: " << getOverlapError() << endl;
    cout << "exceedSum: " << getExceedError() << endl;
    return 0;
}