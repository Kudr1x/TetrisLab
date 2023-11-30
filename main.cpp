#include <random>
#include <iostream>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int SHAPE_TYPES = 7;
const int SHAPE_SIZE = 4;

int score = 0;
int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
bool gameOver = false;

const int tetraminoTypes[7][4]{
        {1, 3, 5, 7},
        {2, 4, 5, 7},
        {3, 5, 4, 6},
        {3, 5, 4, 7},
        {2, 3, 5, 7},
        {3, 5, 7, 6},
        {2, 3, 4, 5}
};

class Tetramino{
private:
     int field[SHAPE_SIZE][SHAPE_SIZE]{};
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

    void printTetramino(){
        for(int i = 0; i < SHAPE_SIZE; i++){
            for(int j = 0; j < SHAPE_SIZE; j++){
                std::cout << field[i][j];
            }

            std::cout << std::endl;
        }
    }
};


int main(){
    Tetramino a;

    a.printTetramino();
    a.rotateAntiClockwiseTetramino();
    a.rotateClockwiseTetramino();
    a.printTetramino();

}