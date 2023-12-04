constexpr int WALL = 2;
constexpr int WIDTH = 10 + WALL;
constexpr int HEIGHT = 20 + WALL;
constexpr int SHAPE_TYPES = 7;
constexpr int SHAPE_SIZE = 4;

const int tetraminoTypes[SHAPE_TYPES][SHAPE_SIZE]{
        {1, 3, 5, 7},
        {2, 4, 5, 7},
        {3, 5, 4, 6},
        {3, 5, 4, 7},
        {2, 3, 5, 7},
        {3, 5, 7, 6},
        {2, 3, 4, 5}
};