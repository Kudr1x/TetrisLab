#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <conio.h>
#include "settings.cpp"

class Tetramino {
private:
    int tetraminoGrid[SHAPE_SIZE][SHAPE_SIZE]{};
    int type;
    int dx;
    int dy;
public:
    Tetramino(){
        std::random_device rd;
        std::mt19937 gen(rd());

        type = gen() % SHAPE_TYPES;

        for(int i = 0; i < SHAPE_SIZE; i++){
            tetraminoGrid[tetraminoTypes[type][i] / 2][tetraminoTypes[type][i] % 2] = 1;
        }

        dx = 0;
        dy = 0;
    }

    void rotateClockwiseTetramino(){
        int temp[SHAPE_SIZE][SHAPE_SIZE];

        for(int i = 0; i < SHAPE_SIZE; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                temp[i][j] = tetraminoGrid[SHAPE_SIZE - 1 - j][i];
            }
        }

        for(int i = 0; i < SHAPE_SIZE; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                tetraminoGrid[i][j] = temp[i][j];
            }
        }
    }

    void rotateAntiClockwiseTetramino(){
        int temp[SHAPE_SIZE][SHAPE_SIZE];

        for (int i = 0; i < SHAPE_SIZE; i++) {
            for (int j = 0; j < SHAPE_SIZE; j++) {
                temp[SHAPE_SIZE - 1 - j][i] = tetraminoGrid[i][j];
            }
        }

        for(int i = 0; i < SHAPE_SIZE; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                tetraminoGrid[i][j] = temp[i][j];
            }
        }
    }


    int getByIndex(int i, int j) {
        return tetraminoGrid[i][j];
    }

    int getType() {
        return type;
    }

    int getDx() {
        return dx;
    }

    int getDy() {
        return dy + 1;
    }

    void setDx(int dx) {
        this->dx = dx;
    }

    int setDy(int dy) {
        this->dy = dy;
    }

    void plusDy() {
        dy++;
    }
};

class Board {
protected:
    int currentBoard[HEIGHT][WIDTH]{};
    int checkBoard[HEIGHT][WIDTH]{};
    int baseBoard[HEIGHT][WIDTH]{};
public:
    Board() {
        for(int i = 0; i < WIDTH; i++) {
            currentBoard[HEIGHT - 1][i] = WALL;
            currentBoard[0][i] = WALL;
        }

        for(int i = 0; i < HEIGHT; i++) {
            currentBoard[i][0] = WALL;
            currentBoard[i][WIDTH - 1] = WALL;
        }
    }

    void printBoard() {
        for(int i = 0; i < HEIGHT; i++) {
            for(int j = 0; j < WIDTH; j++) {
                std::cout << currentBoard[i][j];
            }
            std::cout << std::endl;
        }

        std::cout << "==========================" << std::endl;
    }

    void addTetraminoOnBoard(Tetramino tetramino) {

        //todo костыль
//        int space = 1;
//        if(tetramino.getType() == 0) {
//            space = 0;
//        }

        int space = 0;

        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTH; j++){
                baseBoard[i][j] = currentBoard[i][j];
            }
        }

        while (true) {
            for(int i = 0; i < HEIGHT; i++) {
                for(int j = 0; j < WIDTH; j++) {
                    currentBoard[i][j] = baseBoard[i][j];
                }
            }

            for(int i = 0 + space; i < SHAPE_SIZE; i++) {
                for(int j = 0; j < SHAPE_SIZE; j++) {
                    currentBoard[i - space + tetramino.getDy()][j + WIDTH / 2 - 2 + tetramino.getDx()] += tetramino.getByIndex(i, j);
                }
            }

            printBoard();

            if(checkDrop(tetramino, space)) {
                tetramino.plusDy();
            }else {
                //todo убрать брик
                break;
            };

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if(_kbhit()){
                int event = _getch();

                switch (event) {
                    case 'a':
                        if(checkMove(tetramino, space, -1)) tetramino.setDx(tetramino.getDx() - 1);
                        break;
                    case 'd':
                        if(checkMove(tetramino, space, 1)) tetramino.setDx(tetramino.getDx() + 1);
                        break;
                    case 'q':
                        tetramino.rotateAntiClockwiseTetramino();
                        break;
                    case 'e':
                        tetramino.rotateClockwiseTetramino();
                        break;
                }
            }
        }
    }

    bool checkDrop(Tetramino tetramino, int d) {
        for(int i = 0; i < HEIGHT; i++) {
            for(int j = 0; j < WIDTH; j++) {
                checkBoard[i][j] = currentBoard[i][j];
            }
        }

        bool flagCollision = true;
        for(int i = 0 + d; (i < SHAPE_SIZE) and flagCollision; i++) {
            for(int j = 0; (j < SHAPE_SIZE) and flagCollision; j++) {
                if(currentBoard[i - d + tetramino.getDy() + 1][j + WIDTH / 2 - 2 + tetramino.getDx()] + tetramino.getByIndex(i, j) == 3){
                    flagCollision = false;
                }
            }
        }

        return flagCollision;
    }

    bool checkMove(Tetramino tetramino, int d, int move){
        for(int i = 0; i < HEIGHT; i++){
            for(int j = 0; j < WIDTH; j++){
                checkBoard[i][j] = currentBoard[i][j];
            }
        }

        bool flagCollision = true;
        for(int i = 0 + d; (i < SHAPE_SIZE) and flagCollision; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                if(currentBoard[i - d + tetramino.getDy()][j + WIDTH / 2 - 2 + tetramino.getDx() + move] + tetramino.getByIndex(i, j) == 3){
                    flagCollision = false;
                }
            }
        }

        return flagCollision;
    }

    int saveBoard() {
        for(int i = 0; i < HEIGHT; i++) {
            for(int j = 0; j < WIDTH; j++) {
                if(currentBoard[i][j] == 1) currentBoard[i][j] = WALL;
            }
        }

        int lineIndex = -1;
        int lineCounter = 0;
        for(int i = 1; i < HEIGHT - 1; i++){
            int counter = 0;
            for(int j = 1; j < WIDTH - 1; j++){
                if(currentBoard[i][j] == WALL) counter++;
            }

            if(counter == WIDTH - 2) {
                lineIndex = i;
                lineCounter++;
                for(int k = 1; k < WIDTH - 1; k++){
                    currentBoard[i][k] = 0;
                }
            }
        }

        for(int k = lineIndex; k > 1 and lineIndex != -1; k--){
            for(int j = 0; j < WIDTH; j++){
                currentBoard[k][j] = currentBoard[k - 1][j];
            }
        }

        return lineCounter;
    }

    bool checkFinishGame() {
        return (currentBoard[1][4] != 0 or currentBoard[1][5] != 0);
    }
};

class TetrisGame{
private:
    bool gameRunFlag;
    Board board;
    int scope;
    int level;
public:
    TetrisGame() {
        gameRunFlag = true;
        scope = 0;
    }

    void changeScopeAndLvl(int lineCount){
        int sum = 0;

        switch (lineCount) {
            case 1:
                sum = addSumForOneLine;
                break;
            case 2:
                sum = addSumForTwoLine;
                break;
            case 3:
                sum = addSumForThreeLine;
                break;
            case 4:
                sum = addSumForFourLine;
                break;
            default:
                sum = addSumDefault;
                break;
        }

        scope += sum;

        if(scope >= levelOneScope and scope < levelTwoScope){
            level = LEVEL_1;
        }

        if(scope >= levelTwoScope and scope < levelThreeScope){
            level = LEVEL_2;
        }

        if(scope >= levelThreeScope and scope < levelFourScope){
            level = LEVEL_3;
        }

        if(scope >= levelFourScope){
            level = LEVEL_4;
        }
    }

    void finishGame() {
        gameRunFlag = false;
        std::cout << "Scope: " << scope << std::endl;
    }

    void run() {
        while (gameRunFlag) {
            Tetramino tetramino;
            board.addTetraminoOnBoard(tetramino);
            changeScopeAndLvl(board.saveBoard());

            if(board.checkFinishGame()) {
                finishGame();
            }
        }
    }
};