﻿#include <SFML/Graphics.hpp>
#include "Map.h"
#include "View.h"

using namespace sf;

class Player {
public: float x, y, w, h, dx, dy, speed = 0;
	  int dir = 0;
	  String File;
	  Image image;
	  Texture texture;
	  Sprite sprite;
	  Player(String F, int X, int Y, float W, float H) {
		  File = F;
		  w = W;
		  h = H;
		  image.loadFromFile("Images/" + File);
		  image.createMaskFromColor(Color(41, 33, 59));
		  texture.loadFromImage(image);
		  sprite.setTexture(texture);
		  x = X;
		  y = Y;
		  sprite.setTextureRect(IntRect(w, h, w, h));
	  }
	  void update(float time) {
		  switch (dir)
		  {
		  case 0:
			  dx = speed;
			  dy = 0;
			  break;
		  case 1:
			  dx = -speed;
			  dy = 0;
			  break;
		  case 2:
			  dx = 0;
			  dy = speed;
			  break;
		  case 3:
			  dx = 0;
			  dy = -speed;
			  break;
		  }
		  x += dx * time;
		  y += dy * time;
		  speed = 0;
		  sprite.setPosition(x, y);
	  }
	  float GetPlayerCoordinateX() {
		  return x;
	  }
	  float GetGlayerCoordinateY() {
		  return y;
	  }
};

int main()
{
	RenderWindow window(VideoMode(640, 480), "Test!");
	view.reset(FloatRect(0, 0, 640, 480));

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Player p("hero.png", 250, 250, 96.0, 96.0);

	float CurrentFrame = 0;
	Clock clock;
	 
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			p.dir = 1;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			p.dir = 0;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			p.dir = 3;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) { 
			p.dir = 2;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}

		p.update(time);
		//ViewMap(time);//двигать камерой отдельно от персонажа

		window.setView(view);
		window.clear();

		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32));
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(64, 0, 32, 32));

				s_map.setPosition(j * 32, i * 32);
				window.draw(s_map);
			}
		}

		window.draw(p.sprite);
		window.display();
	}
	return 0;
}
