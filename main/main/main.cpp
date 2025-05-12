#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include "logica.h"

sf::Texture rabbitTexture;
sf::Texture holeTexture;
sf::Texture mushroomTexture;
sf::Texture foxTexture;

#define hole 'O'
#define rabbit 'R'
#define mushroom 'M'
#define fox 'F'
#define empty '_'
#define rabbit_in_hole '*'

const int rows = 5;
const int cols = 5;
const float platformSize = 150.0f;

float offsetX = 150.0f;
float offsetY = 150.0f;

bool foxSelected = false;
int selectedFoxIndex = -1;

bool rabbitSelected = false;
int selectedRabbitRow = -1;
int selectedRabbitCol = -1;
sf::Vector2i mousePos;


void drawRabbit(sf::RenderWindow& window, float offsetX, float offsetY, bool isSelected = false) {

    if (!rabbitTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/iepure.jpg")) {
        std::cerr << "Failed to load rabbit texture!" << std::endl;
        return;
    }

    const float cellSize = 150.0f;
    const float holeRadius = 52.0f;
    const float rabbitRadius = holeRadius * 0.9f;

    sf::CircleShape rabbitCircle(rabbitRadius);
    rabbitCircle.setOrigin(rabbitRadius, rabbitRadius);
    rabbitCircle.setPosition(offsetX + cellSize / 2, offsetY + cellSize / 2);
    rabbitCircle.setTexture(&rabbitTexture);

    if (isSelected) {
        rabbitCircle.setOutlineThickness(5.0f);
        rabbitCircle.setOutlineColor(sf::Color::Yellow);
    }

    window.draw(rabbitCircle);
}

void drawHole(sf::RenderWindow& window, float offsetX, float offsetY) {
    const float holeRadius = 60.0f;

    if (!holeTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/vizuina.jpg")) {
        std::cerr << "Failed to load hole texture!" << std::endl;
        return;
    }

    sf::CircleShape holeCircle(holeRadius);
    holeCircle.setOrigin(holeRadius, holeRadius);
    holeCircle.setPosition(offsetX + 75.0f, offsetY + 75.0f);
    holeCircle.setTexture(&holeTexture);

    window.draw(holeCircle);
}

void drawMushroom(sf::RenderWindow& window, float offsetX, float offsetY) {
    const float mushroomRadius = 60.0f;

    if (!mushroomTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/ciuperca.jpg")) {
        std::cerr << "Failed to load mushroom texture!" << std::endl;
        return;
    }

    sf::CircleShape mushroomCircle(mushroomRadius);
    mushroomCircle.setOrigin(mushroomRadius, mushroomRadius);
    mushroomCircle.setPosition(offsetX + 75.0f, offsetY + 75.0f);
    mushroomCircle.setTexture(&mushroomTexture);

    window.draw(mushroomCircle);
}

void drawFox(sf::RenderWindow& window, float offsetX, float offsetY, bool isVertical, bool isSelected = false) {
    if (!foxTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/vulpe.png")) {
        std::cerr << "Failed to load fox texture!" << std::endl;
        return;
    }

    sf::RectangleShape dfox;

    if (isVertical) {
        dfox.setSize(sf::Vector2f(149.0f, 299.0f));
    }
    else {
        dfox.setSize(sf::Vector2f(299.0f, 149.0f));
    }

    dfox.setPosition(offsetX, offsetY);
    dfox.setTexture(&foxTexture);

    if (isSelected) {
        dfox.setOutlineThickness(5.0f);
        dfox.setOutlineColor(sf::Color::Red);
    }

    window.draw(dfox);
}

void game(int level);
void gameScene();
void congratulationsScreen(int level);
void menu();



int main() {

    menu();


    return 0;
}










void congratulationsScreen(int level) {
    sf::RenderWindow congratsWindow(sf::VideoMode::getDesktopMode(), "Felicitari!", sf::Style::Fullscreen);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/fundal.jpg")) {
        std::cerr << "Nu s-a putut încărca imaginea de fundal!" << std::endl;
        return;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Nu s-a putut încărca fontul!" << std::endl;
        return;
    }

    sf::Text congratsText("Felicitari! Ai castigat!", font, 60);
    congratsText.setFillColor(sf::Color::Yellow);

    float textPosX = (congratsWindow.getSize().x - congratsText.getLocalBounds().width) / 2;
    float textPosY = congratsWindow.getSize().y / 4; 

    sf::RectangleShape playAgainButton(sf::Vector2f(300.0f, 100.0f));  
    playAgainButton.setFillColor(sf::Color(0, 100, 0));                
    float buttonSpacing = 50.0f;                                       

    sf::RectangleShape exitButton(playAgainButton);                    
    playAgainButton.setPosition(
        (congratsWindow.getSize().x - playAgainButton.getSize().x) / 2,
        congratsWindow.getSize().y / 2
    );

    exitButton.setPosition(
        playAgainButton.getPosition().x,
        playAgainButton.getPosition().y + playAgainButton.getSize().y + buttonSpacing
    );

    sf::Text playAgainText("Joaca din nou", font, 30);
    playAgainText.setFillColor(sf::Color::White);

    sf::Text exitText("Alege alt nivel", font, 30);
    exitText.setFillColor(sf::Color::White);

    playAgainText.setPosition(
        playAgainButton.getPosition().x + (playAgainButton.getSize().x - playAgainText.getLocalBounds().width) / 2,
        playAgainButton.getPosition().y + (playAgainButton.getSize().y - playAgainText.getLocalBounds().height) / 2 - 10
    );

    exitText.setPosition(
        exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2,
        exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2 - 10
    );

    while (congratsWindow.isOpen()) {
        sf::Event event;
        while (congratsWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                congratsWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(congratsWindow);

                if (playAgainButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    game(level);

                if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    gameScene();
            }
        }

        congratsWindow.clear();
        congratsWindow.draw(backgroundSprite);
        congratsWindow.draw(congratsText);
        congratsWindow.draw(playAgainButton);
        congratsWindow.draw(playAgainText);
        congratsWindow.draw(exitButton);
        congratsWindow.draw(exitText);
        congratsWindow.display();
    }
}


void game(int level) {
    switch (level) {
    case 0:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel1.txt");
        break;
    case 1:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel2.txt");
        break;
    case 2:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel3.txt");
        break;
    case 3:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel4.txt");
        fox_level4();
        break;
    case 4:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel5.txt");
        fox_level5();
        break;
    case 5:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel6.txt");
        fox_level6();
        break;
    case 6:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel7.txt");
        fox_level7();
        break;
    case 7:
        loadLevel("C:/Users/Bia/Desktop/jump in/main/nivel8.txt");
        fox_level8();
        break;
    case 8:
        randomBoard();
    }


    sf::Texture backgroundTexture;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Tabla de joc cu Iepure, Gauri, Ciuperci si Vulpe", sf::Style::Fullscreen);


    if (!backgroundTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/fundal.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
        return;
    }

    sf::Vector2u windowSize = window.getSize();

    sf::Sprite backgroundSprite;

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
    );


    sf::RectangleShape platform(sf::Vector2f(platformSize, platformSize));
    platform.setFillColor(sf::Color::Green);

    float offsetX = (windowSize.x - cols * platformSize) / 2;
    float offsetY = (windowSize.y - rows * platformSize) / 2;


    sf::VertexArray grid(sf::Lines, (cols + 1) * 2 + (rows + 1) * 2);

    for (int col = 0; col <= cols; ++col) {
        grid.append(sf::Vertex(sf::Vector2f(offsetX + col * platformSize, offsetY), sf::Color::Black));
        grid.append(sf::Vertex(sf::Vector2f(offsetX + col * platformSize, offsetY + rows * platformSize), sf::Color::Black));
    }

    for (int row = 0; row <= rows; ++row) {
        grid.append(sf::Vertex(sf::Vector2f(offsetX, offsetY + row * platformSize), sf::Color::Black));
        grid.append(sf::Vertex(sf::Vector2f(offsetX + cols * platformSize, offsetY + row * platformSize), sf::Color::Black));
    }

    sf::RectangleShape settingsButton(sf::Vector2f(150, 50));
    settingsButton.setFillColor(sf::Color::Blue);
    settingsButton.setPosition(10, 10); // Plasăm butonul în colțul din stânga sus


    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/calibri.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::RectangleShape exitButton(sf::Vector2f(150.0f, 50.0f));
    exitButton.setFillColor(sf::Color::Black);

    sf::Text exitText("Inapoi", font, 25);
    exitText.setFillColor(sf::Color::White);

    sf::Text settingsText("Setari", font, 24);
    settingsText.setFillColor(sf::Color::White);
    settingsText.setPosition(20, 20); // Plasăm textul pe buton

    while (window.isOpen() && !gameWon()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseMoved) {
                mousePos = sf::Mouse::getPosition(window);
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    gameScene();
                }
        }

        mousePos = sf::Mouse::getPosition(window);
        int row = (mousePos.y - offsetY) / platformSize;
        int col = (mousePos.x - offsetX) / platformSize;
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y));

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            mousePos = sf::Mouse::getPosition(window);
            int row = (mousePos.y - offsetY) / platformSize;
            int col = (mousePos.x - offsetX) / platformSize;

            if (row >= 0 && row < rows && col >= 0 && col < cols && (board[row][col] == rabbit || board[row][col] == rabbit_in_hole)) {
                rabbitSelected = true;
                selectedRabbitRow = row;
                selectedRabbitCol = col;
            }
        }

        if (event.type == sf::Event::MouseMoved && rabbitSelected) {
            mousePos = sf::Mouse::getPosition(window);
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && rabbitSelected) {
            int newRow = (mousePos.y - offsetY) / platformSize;
            int newCol = (mousePos.x - offsetX) / platformSize;

            moveRabbit(selectedRabbitRow, selectedRabbitCol, newRow, newCol);

            rabbitSelected = false;
            selectedRabbitRow = -1;
            selectedRabbitCol = -1;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePos = sf::Mouse::getPosition(window);
            int row = (mousePos.y - offsetY) / platformSize;
            int col = (mousePos.x - offsetX) / platformSize;

            if (row >= 0 && row < rows && col >= 0 && col < cols && board[row][col] == fox) {
                for (int i = 0; Fox[i].orientation != '\0'; ++i) {
                    if ((Fox[i].start.row == row && Fox[i].start.column == col) ||
                        (Fox[i].end.row == row && Fox[i].end.column == col)) {
                        foxSelected = true;
                        selectedFoxIndex = i;
                    }
                }
            }
            else {
                foxSelected = false;
                selectedFoxIndex = -1;
            }
        }

        if (foxSelected) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                moveFox(selectedFoxIndex, 'w', 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                moveFox(selectedFoxIndex, 's', 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                moveFox(selectedFoxIndex, 'a', 1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                moveFox(selectedFoxIndex, 'd', 1);
            }
        }

        window.clear();

        window.draw(backgroundSprite);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                platform.setPosition(offsetX + col * platformSize, offsetY + row * platformSize);
                window.draw(platform);
            }
        }

        window.draw(grid);

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (board[row][col] == hole || board[row][col] == rabbit_in_hole) {
                    float holePosX = offsetX + col * platformSize;
                    float holePosY = offsetY + row * platformSize;
                    drawHole(window, holePosX, holePosY);
                }
            }
        }

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (board[row][col] == mushroom) {
                    float mushroomPosX = offsetX + col * platformSize;
                    float mushroomPosY = offsetY + row * platformSize;
                    drawMushroom(window, mushroomPosX, mushroomPosY);
                }
            }
        }

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (board[row][col] == rabbit || board[row][col] == rabbit_in_hole) {
                    float rabbitPosX = offsetX + col * platformSize;
                    float rabbitPosY = offsetY + row * platformSize;
                    bool isSelected = (rabbitSelected && row == selectedRabbitRow && col == selectedRabbitCol);
                    drawRabbit(window, rabbitPosX, rabbitPosY, isSelected);
                }
            }
        }

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (board[row][col] == fox)
                {
                    bool isSelected;
                    int foxNumber = 0;
                    for (int i = 0; Fox[i].orientation != '\0'; ++i)
                        if (((Fox[i].start.row == row && Fox[i].start.column == col) || (Fox[i].end.row == row && Fox[i].end.column == col))) {
                            foxNumber = i;
                            isSelected = (foxSelected && i == selectedFoxIndex);
                        }
                    if (board[row][col + 1] == fox) {
                        if (((Fox[foxNumber].start.row == row && Fox[foxNumber].start.column == col + 1) || (Fox[foxNumber].end.row == row && Fox[foxNumber].end.column == col + 1)))
                            drawFox(window, offsetX + col * platformSize, offsetY + row * platformSize, false, isSelected);
                    }
                    if (board[row + 1][col] == fox) {
                        if (((Fox[foxNumber].start.row == row + 1 && Fox[foxNumber].start.column == col) || (Fox[foxNumber].end.row == row + 1 && Fox[foxNumber].end.column == col)))
                            drawFox(window, offsetX + col * platformSize, offsetY + row * platformSize, true, isSelected);
                    }
                }
            }
        }
        if (gameWon() == true) {
            congratulationsScreen(level);
            break;
        }
        exitButton.setPosition(window.getSize().x - exitButton.getSize().x - 20.f, 20.f);
        float exitTextPosX = exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2;
        float exitTextPosY = exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2;
        exitText.setPosition(exitTextPosX, exitTextPosY);

        window.draw(settingsButton);
        window.draw(settingsText);
        window.draw(exitText);
        window.display();

    }
}

void gameScene() {
    sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "Scena Jocului", sf::Style::Fullscreen);

    // Încarcă imaginea pentru fundal
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/fundal.jpg")) {
        std::cerr << "Nu s-a putut încărca imaginea de fundal!" << std::endl;
        return;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Configurarea fontului pentru text
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Nu s-a putut încărca fontul!" << std::endl;
        return;
    }

    sf::RectangleShape exitButton(sf::Vector2f(150.0f, 50.0f));
    exitButton.setFillColor(sf::Color::Black);

    sf::Text exitText("Inapoi", font, 25);
    exitText.setFillColor(sf::Color::White);

    const int gridSize = 3;
    const float buttonWidth = 300.0f;  
    const float buttonHeight = 150.0f; 
    const float padding = 30.0f;       

    sf::RectangleShape buttons[gridSize * gridSize];
    sf::Text buttonTexts[gridSize * gridSize];

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int index = i * gridSize + j;

            buttons[index].setSize(sf::Vector2f(buttonWidth, buttonHeight));
            buttons[index].setFillColor(sf::Color(0, 100, 0)); 
            float posX = (gameWindow.getSize().x - (gridSize * buttonWidth + (gridSize - 1) * padding)) / 2 + j * (buttonWidth + padding);
            float posY = (gameWindow.getSize().y - (gridSize * buttonHeight + (gridSize - 1) * padding)) / 2 + i * (buttonHeight + padding);
            buttons[index].setPosition(posX, posY);

            buttonTexts[index].setFont(font);
            buttonTexts[index].setString("Nivel " + std::to_string(index + 1));
            buttonTexts[index].setCharacterSize(30); 
            buttonTexts[index].setFillColor(sf::Color::White);
            float textPosX = posX + (buttonWidth - buttonTexts[index].getLocalBounds().width) / 2;
            float textPosY = posY + (buttonHeight - buttonTexts[index].getLocalBounds().height) / 2 - 5;
            buttonTexts[index].setPosition(textPosX, textPosY);
        }
    }

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);

                for (int i = 0; i < gridSize * gridSize; ++i) {
                    if (buttons[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                        gameWindow.close();
                        game(i);
                    }
                }

                if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    menu();
                }
            }

        }
        exitButton.setPosition(gameWindow.getSize().x - exitButton.getSize().x - 20.f, 20.f);
        float exitTextPosX = exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2;
        float exitTextPosY = exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2;
        exitText.setPosition(exitTextPosX, exitTextPosY);

        gameWindow.clear();
        gameWindow.draw(backgroundSprite);
        for (int i = 0; i < gridSize * gridSize; ++i) {
            gameWindow.draw(buttons[i]);
            gameWindow.draw(buttonTexts[i]);
        }
        gameWindow.draw(exitButton);
        gameWindow.draw(exitText);
        gameWindow.display();
    }
}



void menu() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Meniu de Intrare", sf::Style::Fullscreen);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/Bia/Desktop/jump in/media/fundal.jpg")) {
        std::cerr << "Nu s-a putut încărca imaginea de fundal!" << std::endl;
        return;
    }

    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    sf::RectangleShape startButton(sf::Vector2f(300.0f, 60.0f));  
    startButton.setFillColor(sf::Color(0, 100, 0));

    float buttonPosX = (window.getSize().x - startButton.getSize().x) / 2;
    float buttonPosY = (window.getSize().y - startButton.getSize().y) / 2;
    startButton.setPosition(buttonPosX, buttonPosY);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Nu s-a putut încărca fontul!" << std::endl;
        return;
    }

    sf::Text startText("Incepe Jocul", font, 30);  
    startText.setFillColor(sf::Color::White);
    float textPosX = buttonPosX + (startButton.getSize().x - startText.getLocalBounds().width) / 2;
    float textPosY = buttonPosY + (startButton.getSize().y - startText.getLocalBounds().height) / 2;
    startText.setPosition(textPosX, textPosY);

    sf::RectangleShape settingsButton(sf::Vector2f(150.0f, 50.0f));  
    settingsButton.setFillColor(sf::Color::Blue);

    settingsButton.setPosition(20.f, 20.f);

    sf::Text settingsText("Setari", font, 25);
    settingsText.setFillColor(sf::Color::White);
    float settingsTextPosX = settingsButton.getPosition().x + (settingsButton.getSize().x - settingsText.getLocalBounds().width) / 2;
    float settingsTextPosY = settingsButton.getPosition().y + (settingsButton.getSize().y - settingsText.getLocalBounds().height) / 2;
    settingsText.setPosition(settingsTextPosX, settingsTextPosY);

    bool settingsOpened = false;

    sf::RectangleShape stopMusicButton(sf::Vector2f(200.0f, 60.0f));
    stopMusicButton.setFillColor(sf::Color::Red);

    sf::Text stopMusicText("Opreste Muzica", font, 25);
    stopMusicText.setFillColor(sf::Color::White);

    sf::RectangleShape languageButton(sf::Vector2f(200.0f, 60.0f));
    languageButton.setFillColor(sf::Color::Yellow);

    sf::Text languageText("Schimba Limba", font, 25);
    languageText.setFillColor(sf::Color::Black);

    sf::RectangleShape exitButton(sf::Vector2f(150.0f, 50.0f));
    exitButton.setFillColor(sf::Color::Black);

    sf::Text exitText("Iesire", font, 25);
    exitText.setFillColor(sf::Color::White);

    sf::Music music;
    if (!music.openFromFile("C:/Users/Bia/Desktop/jump in/media/Lulakarma_-_Gettin'_High_-_Lofi_Chill_Vibe_Background_Instrumental_Music.mp3")) {
        std::cerr << "Nu s-a putut încărca muzica!" << std::endl;
        return;
    }
    music.setLoop(true);
    music.play();

    bool musicPlaying = true;
    bool languageEnglish = false; 

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    gameScene();
                }

                if (settingsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    settingsOpened = !settingsOpened;
                }

                if (settingsOpened && stopMusicButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    if (musicPlaying) {
                        music.stop();
                        musicPlaying = false;
                    }
                    else {
                        music.play();
                        musicPlaying = true;
                    }
                }

                if (settingsOpened && languageButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    languageEnglish = !languageEnglish;
                    startText.setString(languageEnglish ? "Start Game" : "Incepe Jocul");
                    settingsText.setString(languageEnglish ? "Settings" : "Setari");
                    stopMusicText.setString(languageEnglish ? "Stop Music" : "Opreste Muzica");
                    languageText.setString(languageEnglish ? "Change Language" : "Schimba Limba");
                    exitText.setString(languageEnglish ? "Exit" : "Iesire");
                }

                if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    window.close();
                }
            }
        }

        exitButton.setPosition(window.getSize().x - exitButton.getSize().x - 20.f, 20.f);
        float exitTextPosX = exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2;
        float exitTextPosY = exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2;
        exitText.setPosition(exitTextPosX, exitTextPosY);

        if (settingsOpened) {
            stopMusicButton.setPosition(settingsButton.getPosition().x + settingsButton.getSize().x + 10.f, settingsButton.getPosition().y);
            float stopMusicTextPosX = stopMusicButton.getPosition().x + (stopMusicButton.getSize().x - stopMusicText.getLocalBounds().width) / 2;
            float stopMusicTextPosY = stopMusicButton.getPosition().y + (stopMusicButton.getSize().y - stopMusicText.getLocalBounds().height) / 2;
            stopMusicText.setPosition(stopMusicTextPosX, stopMusicTextPosY);

            languageButton.setPosition(stopMusicButton.getPosition().x, stopMusicButton.getPosition().y + stopMusicButton.getSize().y + 10.f);
            float languageTextPosX = languageButton.getPosition().x + (languageButton.getSize().x - languageText.getLocalBounds().width) / 2;
            float languageTextPosY = languageButton.getPosition().y + (languageButton.getSize().y - languageText.getLocalBounds().height) / 2;
            languageText.setPosition(languageTextPosX, languageTextPosY);
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(startButton);
        window.draw(startText);
        window.draw(settingsButton);
        window.draw(settingsText);

        if (settingsOpened) {
            window.draw(stopMusicButton);
            window.draw(stopMusicText);
            window.draw(languageButton);
            window.draw(languageText);
        }
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }

}