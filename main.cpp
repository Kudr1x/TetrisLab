#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int SHAPE_TYPES = 7;
const int SHAPE_SIZE = 4;

int sleepTime = 1000;
int score = 0;
bool gameOver = false;

const int tetraminoTypes[SHAPE_TYPES][SHAPE_SIZE]{
        {1, 3, 5, 7},
        {0, 2, 3, 5},
        {1, 3, 2, 4},
        {1, 3, 2, 5},
        {0, 1, 3, 5},
        {1, 3, 5, 4},
        {0, 1, 2, 3}
};

class Tetramino{
private:
     int field[SHAPE_SIZE][SHAPE_SIZE]{};
     bool collision = false;
     int dx = 0;
     int dy = 0;
public:
    Tetramino(){
        std::random_device rd;
        std::mt19937 gen(rd());

        int type = gen() % SHAPE_TYPES;

        for(int i = 0; i < SHAPE_SIZE; i++){
            field[tetraminoTypes[type][i] / 2][tetraminoTypes[type][i] % 2] = 1;
        }
    }

    void rotateClockwiseTetramino(){
        int temp[SHAPE_SIZE][SHAPE_SIZE];

        for(int i = 0; i < SHAPE_SIZE; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                temp[i][j] = field[SHAPE_SIZE - 1 - j][i];
            }
        }

        for(int i = 0; i < SHAPE_SIZE; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                field[i][j] = temp[i][j];
            }
        }
    }

    void rotateAntiClockwiseTetramino(){
        int temp[SHAPE_SIZE][SHAPE_SIZE];

        for (int i = 0; i < SHAPE_SIZE; i++) {
            for (int j = 0; j < SHAPE_SIZE; j++) {
                temp[SHAPE_SIZE - 1 - j][i] = field[i][j];
            }
        }

        for(int i = 0; i < SHAPE_SIZE; i++) {
            for(int j = 0; j < SHAPE_SIZE; j++) {
                field[i][j] = temp[i][j];
            }
        }
    }

    void setDx(int dx){
        this->dx = dx;
    }

    void setDy(int dy){
        this->dy = dy;
    }

    int getDx(){
        return dx;
    }

    int getDy(){
        return dy;
    }

    bool getCollision(){
        return collision;
    }

    bool setCollision(){
        collision = true;
    }

    int get(int i, int j){
        return field[i][j];
    }
};

class Board{
private:
    int board[BOARD_HEIGHT][BOARD_WIDTH] = {};
    int tempBoard[BOARD_HEIGHT][BOARD_WIDTH] = {};
public:
    void printBoard(){
        for(int i = 0; i < BOARD_HEIGHT; i++){
            for(int j = 0; j < BOARD_WIDTH; j++){
                std::cout << board[i][j];
            }
            std::cout << std::endl;
        }
    }

    void addToBoard(Tetramino tetramino){
        for(int i = 0; i < BOARD_HEIGHT; i++){
            for(int j = 0; j < BOARD_WIDTH; j++){
                tempBoard[i][j] = board[i][j];
            }
        }

        while (!tetramino.getCollision()){
            for(int i = 0; i < BOARD_HEIGHT; i++){
                for(int j = 0; j < BOARD_WIDTH; j++){
                    board[i][j] = tempBoard[i][j];
                }
            }

            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j ++){
                    board[i + tetramino.getDx()][j + BOARD_WIDTH / 2 - 2 + tetramino.getDy()] = tetramino.get(i, j);
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));

            tetramino.setDx(tetramino.getDx() + 1);

            if(_kbhit()){
                int event = _getch();

                switch (event) {
                    case 'a':
                        tetramino.setDy(tetramino.getDy() - 1);
                        break;
                    case 'd':
                        tetramino.setDy(tetramino.getDy() + 1);
                        break;
                    case 'q':
                        tetramino.rotateAntiClockwiseTetramino();
                        break;
                    case 'e':
                        tetramino.rotateClockwiseTetramino();
                        break;
                }
            }

            std::cout << "===================================" << std::endl;
            printBoard();
        }
    }
};


int main(){
    Tetramino tetramino;
    Board board;
    board.addToBoard(tetramino);
}