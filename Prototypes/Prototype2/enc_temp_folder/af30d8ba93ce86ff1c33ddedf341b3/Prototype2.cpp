#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Prototype 2");

	sf::Texture backgroundTexture("Textures/background.png");
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale({ 0.5f, 0.5f });

	while(window.isOpen()) {
		while(const auto event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		window.clear();
		window.draw(backgroundSprite);
		window.display();
	}
}