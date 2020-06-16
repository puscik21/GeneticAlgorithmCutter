#include <iostream>
#include <fstream>
#include <vector>

#include <ga/ga.h>
#include <ga/std_stream.h>
//#define INSTANTIATE_REAL_GENOME
#include <ga/GARealGenome.h>
#include <ga/GAList.C>
#include <ga/GAListGenome.C>
#include <math.h>
#include <ga/GASStateGA.h>
#include <ga/GAListGenome.h>
#include <ga/garandom.h>


#define cout STD_COUT
#define ostream STD_OSTREAM

using namespace std;

struct coord {
    int x;
    int y;
    int rotation;
    int number;
};

float Objective(GAGenome &);
int Mutator(GAGenome&, float);

const int BOARD_WIDTH = 2800;
const int BOARD_HEIGHT = 2070;
int populationCount = 0;
vector<coord> smallBoards;
int compareBoards(coord* b1, coord* b2);
int getErrorHor(coord* b1, coord* b2);
int getErrorVer(coord* b1, coord* b2);
int getBoardWidth(coord* coord);
int getBoardHeight(coord* coord);
int calculateExceededSurface(coord* coord);
long calculateWholeSurface(vector<coord> positions);
long getBoardSurface (coord* board);
int findExcludedBoard(GARealGenome& genome);
void findNewPositionForBoard(GARealGenome& genome, int number);
long getGenomeSurface(GAGenome& g);
int findExcludedBoardWithFocusOnTheBiggest(GARealGenome& genome);
int getExcludedWithFocusOnTheBiggest(GARealGenome& genome, vector<int> excluded);
int chooseFromIncluded(GARealGenome& genome);

vector<coord> readBoards() {
    ifstream file("maleplyty.txt");
    cout << "File is good? " << file.good() << endl;
    int width;
    int height;
    while (file >> width && file >> height ){
        coord smallBoard = {width, height};
        smallBoards.push_back(smallBoard);
    }
    ::smallBoards = smallBoards;
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

int getOverlapError(vector<coord> positions) {
    long overlapSum = 0;
    for (int i = 0; i < smallBoards.size() - 1; i++) {
        for (int j = i + 1; j < smallBoards.size(); j++) {
            overlapSum += compareBoards(&positions[i], &positions[j]);
        }
    }
    return overlapSum;
}

int compareBoards(coord* b1, coord* b2) {
    if (b1->x == -1 || b1->y == -1 || b2->x == -1 || b2->y == -1) {
        return 0;
    }

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

int getExceedError(vector<coord> positions) {
    long errorSum = 0;
    for (int i = 0; i < smallBoards.size(); i++) {
        errorSum += calculateExceededSurface(&positions[i]);
    }
    return errorSum;
}

int calculateExceededSurface(coord* coord) {
    if (coord->x == -1 || coord->y == -1) {
        return 0;
    }

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

long calculateWholeSurface(vector<coord> positions) {
    long surface = 0;
    for (int i = 0; i < positions.size(); i++) {
        surface += getBoardSurface(&positions[i]);
    }
    return surface;
}

long getBoardSurface (coord* board) {
    if (board->x == -1 || board->y == -1) {
        return 0;
    }
    return smallBoards[board->number].x * smallBoards[board->number].y;
}

int main(int argc, char *argv[]) {
    unsigned int seed = 0;
    for(int ii=1; ii<argc; ii++) {
        if(strcmp(argv[ii++],"seed") == 0) {
            seed = atoi(argv[ii]);
        }
    }

    readBoards();
    int length = smallBoards.size() * 3;
    GARealAlleleSet alleles1;

for (int i = -1; i < 2800; i++) {
    alleles1.add(i);
}
    GARealGenome genome1(length, alleles1, Objective);
//    genome1.crossover(GARealGenome::OnePointCrossover);
    genome1.crossover(GARealGenome::TwoPointCrossover);
//    genome1.crossover(GARealGenome::UniformCrossover);
//    genome1.crossover(GARealGenome::UniformCrossover);
    genome1.mutator(Mutator);

    GAParameterList params;
    GASteadyStateGA::registerDefaultParameters(params);
    params.set(gaNnGenerations, 100);
    params.set(gaNpopulationSize, 100);
    params.set(gaNscoreFrequency, 10);
    params.set(gaNflushFrequency, 50);
    params.set(gaNpMutation, 0.2);
    params.set(gaNpCrossover, 0.8);
    params.set(gaNselectScores, (int)GAStatistics::AllScores);
    params.parse(argc, argv, gaFalse);

    GASteadyStateGA ga1(genome1);
    ga1.maximize();

//    GARouletteWheelSelector selector;
//    GATournamentSelector selector;
    GARankSelector selector;
//    GAUniformSelector selector;
//  GADSSelector selector;
//  GASRSSelector selector;      // - chyba niezly

    ga1.selector(selector);

    GASigmaTruncationScaling scaling;             // nieujemnosc f. dostosowania
    ga1.scaling(scaling);
    ga1.parameters(params);
    ga1.set(gaNscoreFilename, "bog1.dat");
    cout << "\nrunning ga number 1 (alternate allele(0) and allele(3))..."<<endl;

    ga1.initialize(seed);
    while(!ga1.done()){
        ga1.step();
        cout << "actual best (" << populationCount <<"):\t" << ga1.statistics().bestIndividual() << endl;
        populationCount++;
        cout.flush();
    }

    cout << "the ga generated:\n" << ga1.statistics().bestIndividual() << endl;
    genome1 = ga1.statistics().bestIndividual();
    cout << "Best fitness: " << Objective(genome1) << endl;
    cout << "Whole surface: " << getGenomeSurface(genome1) << endl;
    return 0;
}

float Objective(GAGenome& g) {
    GARealGenome &genome = (GARealGenome &) g;
    long overlapError = 0;
    long exceedError = 0;
    long surface = 0;
    vector<coord> positions;
    for (int i = 0; i < genome.length() - 2; i += 3) {
        int posX = genome.gene(i);
        int posY = genome.gene(i + 1);
        int rotation = genome.gene(i + 2);
        int number = i / 3;
        coord board = {posX, posY, rotation, number};
        positions.push_back(board);
    }

    surface = calculateWholeSurface(positions);
    overlapError = getOverlapError(positions);
    exceedError = getExceedError(positions);

    if (overlapError > 0 || exceedError > 0) {
        return 0;
    } else {
        return surface;
    }

//    return surface - overlapError - exceedError;
}

int Mutator(GAGenome& g, float pmut) {
    GARealGenome &genome = (GARealGenome &) g;

    if (populationCount == 0) {
        for (int i = 0; i < genome.size(); i++) {
            genome.gene(i, -1);
        }
    }

    if (populationCount < 25) {
        int numberToInclude = findExcludedBoardWithFocusOnTheBiggest(genome);
//        cout << "Number: " << numberToInclude << endl;
        findNewPositionForBoard(genome, numberToInclude);
    } else {
        if (Objective(g) == 0) {
            int rotationPos = 3 * chooseFromIncluded(genome) + 2;
            if (rotationPos != -1) {
                if (genome.gene(rotationPos) < 1) {
                    genome.gene(rotationPos, 1);
                } else {
                    genome.gene(rotationPos, 0);
                }
            }

            if (Objective(genome) == 0) {
                int excludedBoardNumber = 3 * GARandomInt(0, genome.size() / 3);   // position of board to change   TODO
                genome.gene(excludedBoardNumber, -1);
                genome.gene(excludedBoardNumber + 1, -1);
            }
        } else if (GAFlipCoin(1)) {
            if (GAFlipCoin(1)) {
                int numberToInclude = findExcludedBoard(genome);
                if (numberToInclude != -1) {
                    findNewPositionForBoard(genome, numberToInclude);
                }
            }
        }
    }


//    if (GAFlipCoin(0.5)) {
////        int rotationPos = 3 * GARandomInt(0, (genome.size() / 3) - 1) + 2;
//        int rotationPos = 3 * chooseFromIncluded(genome) + 2;
//        if (rotationPos != -1) {
////            cout << "co sie kryje pop rotationPos: " << genome.gene(rotationPos) << endl;
//            if (genome.gene(rotationPos) < 1) {
//                genome.gene(rotationPos, 1);
//            } else {
//                genome.gene(rotationPos, 0);
//            }
//        }
//    }

//    for (int i = 2; i < genome.size() - 2; i += 3) {
//        if (genome.gene(i) < 1) {
//            genome.gene(i, 1);
//        } else {
//            genome.gene(i, 0);
//        }
//    }

    return (1);
}

int chooseFromIncluded(GARealGenome& genome) {
    vector<int> included = vector<int>();
    for (int i = 0; i < genome.size() - 2; i += 3) {
        if (genome.gene(i) != -1 && genome.gene(i + 1) != -1) {
            included.push_back(i);
        }
    }
    if (!included.empty()) {
        int numberOfIncluded = GARandomInt(0, included.size());
        return included[numberOfIncluded - 1] / 3;
    } else {
        return -1;
    }
}

int findExcludedBoard(GARealGenome& genome) {
    vector<int> excluded = vector<int>();
    for (int i = 0; i < genome.size() - 2; i += 3) {
        if (genome.gene(i) == -1 || genome.gene(i + 1) == -1) {
            excluded.push_back(i);
        }
    }
    if (!excluded.empty()) {
        int numberOfExcluded = GARandomInt(0, excluded.size());
        return excluded[numberOfExcluded - 1] / 3;
    } else {
        return -1;
    }
}

int findExcludedBoardWithFocusOnTheBiggest(GARealGenome& genome) {
    vector<int> excluded = vector<int>();
    for (int i = 0; i < genome.size() - 2; i += 3) {
        if (genome.gene(i) == -1 || genome.gene(i + 1) == -1) {
            excluded.push_back(i);
        }
    }
    if (excluded.size() > 0) {
        int numberOfExcluded = getExcludedWithFocusOnTheBiggest(genome, excluded);
        return excluded[numberOfExcluded - 1] / 3;
    } else {
        return -1;
    }
}

int getExcludedWithFocusOnTheBiggest(GARealGenome& genome, vector<int> excluded) {
    float sum = 0;
    for (int i = 0; i < excluded.size(); i++) {
        int x = smallBoards[excluded[i]/3].x;
        int y = smallBoards[excluded[i]/3].y;
//        cout << "x: " << x << endl;
//        cout << "y: " << y << endl;
        sum += x * y;
    }
    float prob = GARandomFloat();
    float probCounter = 0;
    for (int i = 0; i < excluded.size(); i++) {
        int x = smallBoards[excluded[i]/3].x;
        int y = smallBoards[excluded[i]/3].y;
//        cout << "x: " << x << endl;
//        cout << "y: " << y << endl;
//        cout << "liczone: " << x * y / sum << endl;
//        cout << "prob: " << prob << endl;
        probCounter += x * y / sum;
        if (probCounter > prob) {
//            cout << "Pole: " << x*y << endl;
//            cout << "i: " << i << endl;
            return i;
//            return 7;
        }
    }
}

void findNewPositionForBoard(GARealGenome& genome, int number) {
    coord boardPosition = {(int)genome.gene(number), (int)genome.gene(number + 1), (int)genome.gene(number + 2), number};
    int upperRangeX = BOARD_WIDTH - getBoardWidth(&boardPosition);
    int upperRangeY = BOARD_HEIGHT - getBoardHeight(&boardPosition);
    if (upperRangeX < 0 || upperRangeY < 0 || number < 0) {
        return;
    }

    genome.gene(3 * number, GARandomInt(0, upperRangeX));
    genome.gene(3 *number + 1, GARandomInt(0, upperRangeY));
}

long getGenomeSurface(GAGenome& g) {
    GARealGenome &genome = (GARealGenome &) g;

    vector<coord> positions;
    for (int i = 0; i < genome.length() - 2; i += 3) {
        int posX = genome.gene(i);
        int posY = genome.gene(i + 1);
        int rotation = genome.gene(i + 2);
        int number = i / 3;
        coord board = {posX, posY, rotation, number};
        positions.push_back(board);
    }

    return calculateWholeSurface(positions);
}