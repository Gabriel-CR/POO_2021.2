#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height) {
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity{
    int x {0}; //ATRIBUTOS
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture):
        x { x }, y { y }, step { step }, sprite( texture ) {
    }

    void draw(sf::RenderWindow& window) { // MÉTODOS
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }
};

struct Board {
    int nc { 0 };
    int nl { 0 };
    int step { 0 };
    sf::Sprite sprite;
    sf::RectangleShape rect;

    Board(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);

        for (int i = 0; i < nc; i++) {
            for (int j = 0; j < nl; j++) {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
    }
};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys) {
    if (key == move_keys[0])
        entity.x--;
    else if (key == move_keys[1])
        entity.y--;
    else if (key == move_keys[2])
        entity.x++;
    else if (key == move_keys[3])
        entity.y++;
}

sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cout << "Error loading texture" << '\n';
        exit(1);
    }
    return texture;
}

int main() {
    sf::Texture wolf_text { loadTexture("images/musk.png") };
    sf::Texture rabbit_text { loadTexture("images/bezos.png") };
    sf::Texture grass_text { loadTexture("images/fundo.png") };

    const int STEP {100};

    Entity wolf(1, 1, STEP, wolf_text);
    Entity rabbit(3, 3, STEP, rabbit_text);
    Board board(7, 5, STEP, grass_text);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;

		// TRATAMENTOS DE EVENTOS
        while (window.pollEvent(event)) { // pollEvent() GUARDA EVENTOS E RETORNA
            if (event.type == sf::Event::Closed) {
                window.close();
            }
			else if (event.type == sf::Event::KeyPressed) {
                moveEntity(event.key.code, wolf, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
                moveEntity(event.key.code, rabbit, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
            }
        }

		// ATUALIZAÇÃO E PINTURA
        window.clear();
        board.draw(window);
        wolf.draw(window);
        rabbit.draw(window);
        window.display();
    }

    return 0;
}