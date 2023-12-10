#include "SFML/Graphics.hpp"
#include <random>
#include <vector>

// Размер поля
const int WIDTH = 10;
const int HEIGHT = 20;

// Размер блока
const int BLOCK_SIZE = 30;

//Уровни игры
const int LEVEL_ONE = 1;
const int LEVEL_TWO = 2;
const int LEVEL_THREE = 3;
const int LEVEL_FOUR = 4;

//Количество линий за раз
const int ONE_LINE = 1;
const int TWO_LINE = 2;
const int THREE_LINE = 3;
const int FOUR_LINE = 4;

//Награда за количество линий
const int ONE_LINE_REWARD = 100;
const int TWO_LINE_REWARD = 300;
const int THREE_LINE_REWARD = 700;
const int FOUR_LINE_REWARD = 1500;
const int ZERO_LINE_REWARD = 0;

//Необходимое количество очков для уровня
const int LEVEL_ONE_SCOPE = 0;
const int LEVEL_TWO_SCOPE = 1000;
const int LEVEL_THREE_SCOPE = 2000;
const int LEVEL_FOUR_SCOPE = 3000;

//Задержка для разных уровней
const int DELAY_TIME_LEVEL_ONE = 500;
const int DELAY_TIME_LEVEL_TWO = 400;
const int DELAY_TIME_LEVEL_THREE = 300;
const int DELAY_TIME_LEVEL_FOUR = 100;

//Размеры окна диалога
const int DIALOG_HEIGHT = 200;
const int DIALOG_WIDTH = 500;

// Фигуры Тетриса
const std::vector<std::vector<std::vector<int>>> SHAPES_LIST = {
        // I-фигура
        {{1, 1, 1, 1}},
        // J-фигура
        {{1, 0, 0},
                {1, 1, 1}},
        // L-фигура
        {{0, 0, 1},
                {1, 1, 1}},
        // O-фигура
        {{1, 1},
                {1, 1}},
        // S-фигура
        {{0, 1, 1},
                {1, 1, 0}},
        // T-фигура
        {{0, 1, 0},
                {1, 1, 1}},
        // Z-фигура
        {{1, 1, 0},
                {0, 1, 1}}
};

//Сообщения
const std::string rankList[4]{"Need to try harder", "Not bad!", "It's working out great!", "You are a Tetris winner!"};

//Цвета фигур
const std::vector<sf::Color> COLOR_LIST = {
        sf::Color::Cyan,
        sf::Color::Blue,
        sf::Color::Magenta,
        sf::Color::Yellow,
        sf::Color::Green,
        sf::Color::Red,
        sf::Color (255, 102, 0)
};