#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <conio.h>
#include "cmake-build-debug/settings.cpp"

class Tetramino {
private:
    int tetraminoGrid[SHAPE_SIZE][SHAPE_SIZE]{};
    int type;
    int dx = 0;
    int dy = 0;
public:
    Tetramino(){
        std::random_device rd;
        std::mt19937 gen(rd());

        type = gen() % SHAPE_TYPES;

        for(int i = 0; i < SHAPE_SIZE; i++){
            tetraminoGrid[tetraminoTypes[type][i] / 2][tetraminoTypes[type][i] % 2] = 1;
        }
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
    int newBoard[HEIGHT][WIDTH]{};
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
        int space = 1;
        if(tetramino.getType() == 0) {
            space = 0;
        }

        while (true) {
            for(int i = 0 + space; i < SHAPE_SIZE; i++) {
                for(int j = 0; j < SHAPE_SIZE; j++) {
                    if(currentBoard[i - space + tetramino.getDy() - 1][j + WIDTH / 2 - 2 + tetramino.getDx() - 1] != 2) {
                        currentBoard[i - space + tetramino.getDy() - 1][j + WIDTH / 2 - 2 + tetramino.getDx() - 1] = 0;
                    }
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
                break;
            };

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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
                newBoard[i][j] = currentBoard[i][j];
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
                newBoard[i][j] = currentBoard[i][j];
            }
        }

        bool flagCollision = true;
        for(int i = 0 + d; (i < SHAPE_SIZE) and flagCollision; i++) {
            for(int j = 0; (j < SHAPE_SIZE) and flagCollision; j++) {
                if(currentBoard[i - d + tetramino.getDy()][j + WIDTH / 2 - 2 + tetramino.getDx() + move] + tetramino.getByIndex(i, j) == 3){
                    flagCollision = false;
                }
            }
        }

        return flagCollision;
    }

    void saveBoard() {
        for(int i = 0; i < HEIGHT; i++) {
            for(int j = 0; j < WIDTH; j++) {
                if(currentBoard[i][j] == 1) currentBoard[i][j] = WALL;
            }
        }
    }

    bool checkFinishGame() {
        return (currentBoard[1][4] != 0 or currentBoard[1][5] != 0);
    }
};

class TetrisGame{
private:
    bool gameRunFlag;
    Board board;
public:
    TetrisGame() {
        gameRunFlag = true;
    }

    void finishGame() {
        gameRunFlag = false;
    }

    void run() {
        while (gameRunFlag) {
            Tetramino tetramino;
            board.addTetraminoOnBoard(tetramino);
            board.saveBoard();

            if(board.checkFinishGame()) {
                finishGame();
            }
        }
    }
};

int main() {
    TetrisGame game;
    game.run();
}