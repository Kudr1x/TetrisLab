constexpr int WALL = 2;
constexpr int WIDTH = 10 + WALL;
constexpr int HEIGHT = 20 + WALL;
constexpr int SHAPE_TYPES = 7;
constexpr int levelOneScope = 0;
constexpr int levelTwoScope = 1000;
constexpr int levelThreeScope = 2000;
constexpr int levelFourScope = 3000;
constexpr int SHAPE_SIZE = 4;
constexpr int LEVEL_1 = 1;
constexpr int LEVEL_2 = 2;
constexpr int LEVEL_3 = 3;
constexpr int LEVEL_4 = 4;
constexpr int addSumForOneLine = 100;
constexpr int addSumForTwoLine = 300;
constexpr int addSumForThreeLine = 700;
constexpr int addSumForFourLine = 1500;
constexpr int addSumDefault = 0;

const int tetraminoTypes[SHAPE_TYPES][SHAPE_SIZE]{
        {1, 3, 5, 7},
        {2, 4, 5, 7},
        {3, 5, 4, 6},
        {3, 5, 4, 7},
        {2, 3, 5, 7},
        {3, 5, 7, 6},
        {2, 3, 4, 5}
};