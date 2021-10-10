#include <SFML/Graphics.hpp>
#include <iostream>

void setSize(sf::Sprite& sprite, int width, int height){ // REDIMENSIONA A IMAGEM
	auto dim = sprite.getLocalBounds();
	sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity{
	int x { 0 }; //ATRIBUTOS
	int y { 0 };
	int step { 0 };
	sf::Sprite sprite;

	Entity (int x, int y, int step, sf::Texture& texture):
		x { x }, y { y }, step { step }, sprite(texture) {
	}

	void draw(sf::RenderWindow& window) { // MÉTODOS
		this->sprite.setPosition(x * step, y * step);
		setSize(this->sprite, step, step);
		window.draw(this->sprite);
	}
};

struct Board {
	int nc { 0 };
};


void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys){
	if (key == move_keys[0])
		entity.x--;
	else if (key == move_keys[1])
		entity.y--;
	else if (key == move_keys[2])
		entity.x++;
	else if (key == move_keys[3])
		entity.y++;
}

sf::Texture loadTexture(std::string path){
	sf::Texture texture;

	if (! texture.loadFromFile(path)) {
		std::cout << "Error loading texture" << '\n';
		exit(1);
	}

	return texture;
}

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

	sf::Texture wolf_text { loadTexture("content/lobo.png") };
	sf::Texture rabbit_text { loadTexture("content/coelho.png") };

	Entity wolf(1, 1, 100, wolf_text);
	Entity rabbit(3, 3, 100, rabbit_text);

	while (window.isOpen()) {
		sf::Event event;

		// TRATAMENTOS DE EVENTOS
		while (window.pollEvent(event)) { // pollEvent() GUARDA EVENTOS E RETORNA
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type ==  sf::Event::KeyPressed) {
				moveEntity(event.key.code, wolf, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
				moveEntity(event.key.code, rabbit, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
			}
		}

		// ATUALIZAÇÃO E PINTURA
		window.clear();
		wolf.draw(window);
		rabbit.draw(window);
		window.display();
	}

	return 0;
}
