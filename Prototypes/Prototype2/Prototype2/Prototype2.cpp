#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode({ 1280, 720 }), "Prototype 2");

	sf::Texture backgroundTexture("Textures/background.png");
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale({ 0.5f, 0.5f });

	sf::Font font("Fonts/Allura-Regular.ttf");
	sf::Text text(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);

	std::string textString = "";

	while(window.isOpen()) {
		while(const auto event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>()) {
				window.close();
			}

			if(const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
				std::string tempString = fmt::to_string(static_cast<char>(textEntered->unicode));

				// When backspace key is pressed, the last letter of textString will be removed.
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
					if(!textString.empty()) {
						textString.pop_back();
					}
				}
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
					textString += "\n";
				}
				
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
					textString += tempString;
				}

				text.setString(textString);
			}
		}

		window.clear();
		window.draw(backgroundSprite);
		window.draw(text);
		window.display();
	}
}