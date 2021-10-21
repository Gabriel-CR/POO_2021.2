#include <SFML/Graphics.hpp>
#include <iostream>

// g++ -IC:\SFML-2.5.1\include -c main.cpp -o main.o
// g++ -LC:\SFML-2.5.1\lib .\main.o -o app.exe -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main -mwindows

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
    
};


struct GAME {
    sf::RenderWindow window;

    GAME() : window(sf::VideoMode(800, 600), "Bubbles") { // criando janela
        window.setFramerateLimit(60);
    }

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) { //fecha a janela
                window.close();
            }
        }
    }

    void draw() {
        window.clear(sf::Color::Black);
        static BUBBLE bubble(200, 100, 'B', 2);
        bubble.update();
        bubble.draw(window);
        window.display();
    }

    void mainLoop() { // ordem de acontecimentos do jogo
        while (window.isOpen()) {
            processEvents();
            draw();
        }        
    }
};


int main(){
    GAME game;
    game.mainLoop();

    return 0;
}