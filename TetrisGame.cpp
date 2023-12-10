#include "settings.cpp"

class TetrisGame {
private:
    bool gameIsFinish = false;

    sf::RenderWindow window;

    sf::Color currentColor;
    sf::Color newColor;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> currentShape;
    std::vector<std::vector<int>> newShape;

    int currentX;
    int currentY;
    int currentScope;
    int currentLevel;
    int currentDelayTime;

    bool flagFirstStart = true;

    sf::Text textLevelLabel;
    sf::Text textLevel;
    sf::Text textScopeLabel;
    sf::Text textScope;

    sf::Font font;

    void update() {
        if (collides(currentShape, currentX, currentY + 1)) {
            saveBoard();
            removeLines();
            spawnNewShape();

            if (collides(currentShape, currentX, currentY)) {
                gameIsFinish = true;
            }
        }
        else {
            currentY++;
        }
    }

    void rotateShapeClockwise() {
        std::vector<std::vector<int>> rotatedShape(currentShape[0].size(),
                                                   std::vector<int>(currentShape.size(), 0));

        for (int row = 0; row < currentShape.size(); row++) {
            for (int col = 0; col < currentShape[row].size(); col++) {
                rotatedShape[col][currentShape.size() - row - 1] = currentShape[row][col];
            }
        }

        if (!collides(rotatedShape, currentX, currentY)) {
            currentShape = rotatedShape;
        }
    }

    void rotateAntiShapeClockwise() {
        std::vector<std::vector<int>> rotatedShape(currentShape[0].size(),
                                                   std::vector<int>(currentShape.size(), 0));

        for (int row = 0; row < currentShape.size(); row++) {
            for (int col = 0; col < currentShape[row].size(); col++) {
                rotatedShape[currentShape[row].size() - col - 1][row] = currentShape[row][col];
            }
        }

        if (!collides(rotatedShape, currentX, currentY)) {
            currentShape = rotatedShape;
        }
    }

    void saveBoard() {
        for (int row = 0; row < currentShape.size(); ++row) {
            for (int col = 0; col < currentShape[row].size(); ++col) {
                if (currentShape[row][col]) {
                    board[currentX + col][currentY + row] = 1;
                }
            }
        }
    }

    void removeLines() {
        int removeLineCounter = 0;
        for (int row = HEIGHT - 1; row >= 0; row--) {

            bool full = true;
            for (int col = 0; col < WIDTH and full; col++) {
                if (!board[col][row]) {
                    full = false;
                }
            }

            if (full) {
                removeLineCounter++;
                for (int r = row; r > 0; r--) {
                    for (int col = 0; col < WIDTH; col++) {
                        board[col][r] = board[col][r - 1];
                    }
                }

                for (int col = 0; col < WIDTH; col++) {
                    board[col][0] = 0;
                }

                row++;
            }
        }

        addScore(removeLineCounter);
    }

    void speedUpdate(){
        switch (currentLevel) {
            case LEVEL_ONE:
                currentDelayTime = DELAY_TIME_LEVEL_ONE;
                break;

            case LEVEL_TWO:
                currentDelayTime = DELAY_TIME_LEVEL_TWO;
                break;

            case LEVEL_THREE:
                currentDelayTime = DELAY_TIME_LEVEL_THREE;
                break;

            case LEVEL_FOUR:
                currentDelayTime = DELAY_TIME_LEVEL_FOUR;
                break;
        }
    }

    void levelUpdate(){
        bool flagIsLevelUpdate = false;

        if(currentScope >= LEVEL_ONE_SCOPE and currentScope < LEVEL_TWO_SCOPE){
            currentLevel = LEVEL_ONE;
            flagIsLevelUpdate = true;
        }else if(currentScope >= LEVEL_TWO_SCOPE and currentScope < LEVEL_THREE_SCOPE){
            currentLevel = LEVEL_TWO;
            flagIsLevelUpdate = true;
        }else if(currentScope >= LEVEL_THREE_SCOPE and currentScope < LEVEL_FOUR_SCOPE){
            currentLevel = LEVEL_THREE;
            flagIsLevelUpdate = true;
        }else if(currentScope >= LEVEL_FOUR_SCOPE){
            currentLevel = LEVEL_FOUR;
            flagIsLevelUpdate = true;
        }

        if(flagIsLevelUpdate) speedUpdate();
    }

    void addScore(int removeLineCounter){
        int tempScope;
        bool flagScopeIsChange = false;
        switch (removeLineCounter) {
            case ONE_LINE:
                tempScope = ONE_LINE_REWARD;
                flagScopeIsChange = true;
                break;
            case TWO_LINE:
                tempScope = TWO_LINE_REWARD;
                flagScopeIsChange = true;
                break;
            case THREE_LINE:
                tempScope = THREE_LINE_REWARD;
                flagScopeIsChange = true;
                break;
            case FOUR_LINE:
                tempScope = FOUR_LINE_REWARD;
                flagScopeIsChange = true;
                break;
            default:
                tempScope = ZERO_LINE_REWARD;
        }

        currentScope += tempScope;

        if(flagScopeIsChange) levelUpdate();
    }

    void spawnNewShape() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, SHAPES_LIST.size() - 1);

        if(flagFirstStart){
            currentShape = SHAPES_LIST[dis(gen)];
            currentColor = COLOR_LIST[dis(gen)];

            newShape = SHAPES_LIST[dis(gen)];
            newColor = COLOR_LIST[dis(gen)];

            currentX = WIDTH / 2 - currentShape[0].size() / 2;
            currentY = 0;

            flagFirstStart = false;
        }else{
            currentShape = newShape;
            currentColor = newColor;

            currentX = WIDTH / 2 - currentShape[0].size() / 2;
            currentY = 0;

            newShape = SHAPES_LIST[dis(gen)];
            newColor = COLOR_LIST[dis(gen)];
        }
    }

    bool collides(const std::vector<std::vector<int>>& shape, int offsetX, int offsetY) {
        for (int row = 0; row < shape.size(); ++row) {
            for (int col = 0; col < shape[row].size(); ++col) {
                if (shape[row][col] && (offsetX + col < 0 || offsetX + col >= WIDTH || offsetY + row >= HEIGHT || board[offsetX + col][offsetY + row])) {
                    return true;
                }
            }
        }

        return false;
    }

    void processEvents() {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A and !collides(currentShape, currentX - 1, currentY)) {
                    currentX--;
                }
                else if (event.key.code == sf::Keyboard::D and !collides(currentShape, currentX + 1, currentY)) {
                    currentX++;
                }
                else if (event.key.code == sf::Keyboard::S and !collides(currentShape, currentX, currentY + 1)) {
                    currentY++;
                }
                else if (event.key.code == sf::Keyboard::Q) {
                    rotateAntiShapeClockwise();
                }
                else if (event.key.code == sf::Keyboard::E) {
                    rotateShapeClockwise();
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    while (!collides(currentShape, currentX, currentY + 1)) {
                        currentY++;
                    }
                }
            }
        }
    }

    void render() {
        window.clear();

        renderBoard();
        renderGUI();

        window.display();
    }

    void renderBoard(){
        // Отрисовка поля
        for (int row = 0; row < HEIGHT; ++row) {
            for (int col = 0; col < WIDTH; ++col) {
                if (board[col][row]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    block.setPosition(float(col * BLOCK_SIZE), float(row * BLOCK_SIZE));
                    block.setFillColor(sf::Color::White);
                    window.draw(block);
                }
            }
        }

        // Отрисовка текущей фигуры
        for (int row = 0; row < currentShape.size(); ++row) {
            for (int col = 0; col < currentShape[row].size(); ++col) {
                if (currentShape[row][col]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    block.setPosition(float(currentX + col) * BLOCK_SIZE, float(currentY + row) * BLOCK_SIZE);
                    block.setFillColor(currentColor);
                    window.draw(block);
                }
            }
        }
    }

    void renderGUI(){
        sf::RectangleShape block(sf::Vector2f(2, HEIGHT * BLOCK_SIZE));
        block.setPosition(WIDTH * BLOCK_SIZE, 0);
        block.setFillColor(sf::Color::White);
        window.draw(block);

        font.loadFromFile("JetBrainsMono-Medium.ttf");

        textLevelLabel.setFont(font);
        textLevelLabel.setString("Level: ");
        textLevelLabel.setPosition((WIDTH + 2) * BLOCK_SIZE, 2 * BLOCK_SIZE);
        window.draw(textLevelLabel);

        textLevel.setFont(font);
        textLevel.setString(std::to_string(currentLevel));
        textLevel.setPosition((WIDTH + 6) * BLOCK_SIZE, 2 * BLOCK_SIZE);
        window.draw(textLevel);

        textScopeLabel.setFont(font);
        textScopeLabel.setString("Scope: ");
        textScopeLabel.setPosition((WIDTH + 2) * BLOCK_SIZE, 4 * BLOCK_SIZE);
        window.draw(textScopeLabel);

        textScope.setFont(font);
        textScope.setString(std::to_string(currentScope));
        textScope.setPosition((WIDTH + 6) * BLOCK_SIZE, 4 * BLOCK_SIZE);
        window.draw(textScope);

        for (int row = 0; row < newShape.size(); ++row) {
            for (int col = 0; col < newShape[row].size(); ++col) {
                if (newShape[row][col]) {
                    sf::RectangleShape block(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
                    block.setPosition(float(13 + col) * BLOCK_SIZE, float(10 + row) * BLOCK_SIZE);
                    block.setFillColor(newColor);
                    window.draw(block);
                }
            }
        }
    }

public:
    TetrisGame():
            window(sf::VideoMode(WIDTH * BLOCK_SIZE + 250, HEIGHT * BLOCK_SIZE), "Tetris"){
        std::vector<std::vector<int>> temp(WIDTH, std::vector<int>(HEIGHT, 0));
        board = temp;

        spawnNewShape();

        currentLevel = 1;
        currentScope = 0;
        currentDelayTime = DELAY_TIME_LEVEL_ONE;
    }

    void runDialogWindow(){
        sf::RenderWindow dialog(sf::VideoMode(DIALOG_WIDTH, DIALOG_HEIGHT), "Oh no!");

        sf::Text finalScopeLabel;
        finalScopeLabel.setFont(font);
        finalScopeLabel.setString("Scope: ");
        finalScopeLabel.setPosition(0, 0);
        dialog.draw(finalScopeLabel);

        sf::Text finalScope;
        finalScope.setFont(font);
        finalScope.setString(std::to_string(currentScope));
        finalScope.setPosition(120, 0);
        dialog.draw(finalScope);

        sf::Text rankLabel;
        rankLabel.setFont(font);
        rankLabel.setString(rankList[currentLevel - 1]);
        rankLabel.setPosition(0, DIALOG_HEIGHT / 2);
        dialog.draw(rankLabel);

        dialog.display();

        while (dialog.isOpen()){
            // проверяем все события окна, которые были запущены после последней итерации цикла
            sf::Event event{};
            while (dialog.pollEvent(event)){
                // если произошло событие Закрытие, закрываем наше окно
                if (event.type == sf::Event::Closed) {
                    dialog.close();
                    window.close();
                }
            }
        }
    }

    void run() {
        sf::Clock clock;

        while (window.isOpen()) {
            sf::Time elapsed = clock.getElapsedTime();
            if (elapsed.asMilliseconds() > currentDelayTime) {
                update();
                clock.restart();
            }

            processEvents();
            render();

            if(gameIsFinish){
                runDialogWindow();
            }
        }
    }
};