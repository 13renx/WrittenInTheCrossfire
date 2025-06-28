#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <dotenv.h>
#include <cpr/cpr.h>
#include <fmt/base.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

int main() {
	dotenv::init(".env");
	const char* apiKeyTemp = std::getenv("API_KEY");

	if(apiKeyTemp == nullptr) {
		throw std::runtime_error("API_KEY was not found");
	}

	const std::string apiKey = std::string(apiKeyTemp);
	std::string textString = "";
	json data;
	json output;
	std::string outputText;

	// Initialize SFML
	sf::RenderWindow window(sf::VideoMode(), "Prototype 2", sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);

	sf::Texture backgroundTexture("Textures/background.png");
	sf::Sprite backgroundSprite(backgroundTexture);
	backgroundSprite.setScale({ 0.6f, 0.6f });

	sf::Font font("Fonts/Allura-Regular.ttf");
	sf::Text text(font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Black);

	// Game loop
	while(window.isOpen()) {
		while(const auto event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>()) {
				window.close();
			}

			if(const auto* textEntered = event->getIf<sf::Event::TextEntered>()) {
				std::string tempString = fmt::to_string(static_cast<char>(textEntered->unicode));

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

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
					if(textString != "") {
						data = json::parse(R"(
							{ 
								"contents": [
									{ 
										"parts": []
									}
								] 
							}
						)");
						data["contents"][0]["parts"][0]["text"] = textString;

						cpr::Response res = cpr::Post(cpr::Url{ "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent" },
							cpr::Parameters{ { "key", apiKey } },
							cpr::Header{ { "Content-Type", "application/json" } },
							cpr::Body{ data.dump() });

						// Add error handling for response

						output = json::parse(res.text);
						outputText = output["candidates"][0]["content"]["parts"][0]["text"].template get<std::string>();
						fmt::print("{}\n", outputText);
					}
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