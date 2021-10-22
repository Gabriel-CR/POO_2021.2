#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>

struct PINCEL { // construindo a fonte
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

    PINCEL(sf::RenderWindow& window) : window{window} {
        if (!font.loadFromFile("Poppins-Bold.ttf"))
            std::cout << "Erro no carregamento da fonte\n";
        text.setFont(font);
    }

    void write(std::string str, int x, int y, int size, sf::Color color) { // mostrando a fonte na tela
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(x, y);
        text.setFillColor(color);
        window.draw(text);
    }
};

struct BUBBLE {
    static const int radius { 10 };
    int x;
    int y;
    char letter;
    int speed;
    bool alive { true };

    BUBBLE(int x, int y, char letter, int speed) : x{x}, y{y}, letter{letter}, speed{speed} {
    }

    void update(){
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window){
        sf::CircleShape circle (BUBBLE::radius);
        circle.setPosition(x, y);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);

        static PINCEL pencil(window);
        pencil.write(std::string(1, letter), x + 0.2 * BUBBLE::radius, y, BUBBLE::radius * 1.5, sf::Color::Blue);
    }
};

struct BOARD {
    sf::RenderWindow& window;
    std::vector<BUBBLE> bubbles;
    PINCEL pencil;
    int hits { 0 };
    int misses { 0 };

    BOARD(sf::RenderWindow& window) : window{window}, pencil{window} {
        bubbles.push_back(BUBBLE(100, 100, 'A', 1));
        bubbles.push_back(BUBBLE(200, 100, 'B', 2));
        bubbles.push_back(BUBBLE(300, 100, 'C', 3));
    }

    void update() {
        if (this->checkNewBubble())
            this->addNewBubble();

        for (BUBBLE& bubble : bubbles)
            bubble.update();

        this->markOutsideBubbles();
        this->removeDeadBubbles();
    }

    void removeDeadBubbles(){
        std::vector<BUBBLE> vivas;

        for (BUBBLE& bubble : bubbles) {
            if (bubble.alive)
                vivas.push_back(bubble);
        }

        this->bubbles = vivas;
    }

    void markOutsideBubbles() {
        for (BUBBLE& bubble : bubbles) {
            if (bubble.y + 2 * BUBBLE::radius > (int) this-> window.getSize().y) {
                if (bubble.alive) {
                    bubble.alive = false;
                    this->misses++;
                }
            }
        }
    }

    void markByHit(char letter){
        for (BUBBLE& bubble : bubbles) {
            if (bubble.letter == letter) {
                bubble.alive = false;
                this->hits++;
                break;
            }
        }
    }

    bool checkNewBubble(){
        static const int newBubblesTimeOut { 30 };
        static int newBubblesTimer { 0 };

        newBubblesTimer--;
        if (newBubblesTimer <= 0) {
            newBubblesTimer = newBubblesTimeOut;
            return true;
        }
        return false;
    }

    void addNewBubble(){
        int x = rand() % ((int) this->window.getSize().x - 2 * BUBBLE::radius);
        int y = - 2 * BUBBLE::radius;
        int speed = rand() % 5 + 1;
        char letter = rand() % 26 + 'A';
        bubbles.push_back(BUBBLE(x, y, letter, speed));
    }

    void draw() {
        pencil.write("Hits: " + std::to_string(this->hits) + "  Misses: " + std::to_string(this->misses), 10, 10, 20, sf::Color::White);
        pencil.write("Size: " + std::to_string(this->bubbles.size()), 10, 30, 20, sf::Color::White);

        for (BUBBLE& bubble : bubbles)
            bubble.draw(window);
    }
};

struct GAME {
    sf::RenderWindow window;
    BOARD board;
    std::function<void()> onUpdate;

    GAME() : window(sf::VideoMode(800, 600), "Bubbles"), board(window) { // criando janela
        this->onUpdate = [&]() {
            this->gamePlay();
        };
        window.setFramerateLimit(30);
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { //fecha a janela
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.markByHit(code);
            }
        }
    }

    void gamePlay() {
        board.update();
        window.clear(sf::Color::Black);
        board.draw();
        window.display();

        if (board.misses > 10) {
            this->onUpdate = [&]() {
                this->gameOver();
            };
        }
    }

    void gameOver(){
        static PINCEL pincel(window);
        window.clear(sf::Color::Red);
        pincel.write("Game Over", 400, 300, 50, sf::Color::White);
        window.display();
    }

    void mainLoop() { // ordem de acontecimentos do jogo
        while (window.isOpen()) {
            processEvents();
            onUpdate();
        }        
    }
};

int main(){
    GAME game;
    game.mainLoop();
    return 0;
}