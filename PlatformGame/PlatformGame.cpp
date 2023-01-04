#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Test!");

	Image heroImage;
	heroImage.loadFromFile("Images/hero.png");

	Texture heroTexture;
	heroTexture.loadFromImage(heroImage);

	Sprite heroSprite;
	heroSprite.setTexture(heroTexture);
	heroSprite.setTextureRect(IntRect(0,192,96, 96));
	heroSprite.setPosition(50, 25);

	float CurrentFrame = 0;
	Clock clock;
	 
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 3) CurrentFrame -= 3;
			heroSprite.move(-0.1 * time, 0);
			heroSprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			heroSprite.move(0.1 * time, 0);
			heroSprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			heroSprite.move(0, -0.1 * time);
			heroSprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) { 
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			heroSprite.move(0, 0.1 * time);
			heroSprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
		}


		window.clear();
		window.draw(heroSprite);
		window.display();
	}
	return 0;
}
