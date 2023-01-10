#include <SFML/Graphics.hpp>
#include "Map.h"
#include "View.h"
#include <iostream>
#include <sstream>

using namespace sf;

class Player {
public: float x, y, w, h, dx, dy, speed = 0;
	  int dir,score;
	  String File;
	  Image image;
	  Texture texture;
	  Sprite sprite;
	  Player(String F, int X, int Y, float W, float H) {
		  dir = 0;
		  score = 0;
		  File = F;
		  w = W;
		  h = H;
		  image.loadFromFile("Images/" + File);
		  //image.createMaskFromColor(Color(41, 33, 59));//del color on img
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
		  InteractionMap();
	  }
	  float GetPlayerCoordinateX() {
		  return x;
	  }
	  float GetGlayerCoordinateY() {
		  return y;
	  }
	  void InteractionMap() {
		  for (int i = y/32; i < (h+y)/32; i++)
		  {
			  for (int j = x/32; j < (x+w)/32; j++)
			  {
				  if (TileMap[i][j] == '0')//cant go after 0 in map
				  {
					  if (dy>0)
					  {
						  y = i * 32 - h;
					  }
					  if (dy<0)
					  {
						  y = i * 32 + 32;
					  }
					  if (dx>0)
					  {
						  x = j * 32 - w;
					  }
					  if (dx<0)
					  {
						  x = j * 32 + 32;
					  }
				  }
				  if (TileMap[i][j]=='s') // use s(stoun)
				  {
					  //x = 300;//teleport
					  //y = 300;
					  score++;
					  TileMap[i][j] = ' ';//clear s
				  }
			  }
		  }
	  }
};

int main()
{
	RenderWindow window(VideoMode(640, 480), "Test!");
	view.reset(FloatRect(0, 0, 640, 480));

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setOutlineColor(Color::White);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Image map_image;
	map_image.loadFromFile("Images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Player p("Test.png", 160, 160, 40, 60);

	float CurrentFrame = 0;
	Clock clock;
	int step = 10;
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
			if (CurrentFrame > 0) { step = 30; }
			else step = 10;
			CurrentFrame += 0.005 * time; 
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(50 *int(CurrentFrame)+step, 133, -40, 60));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			p.dir = 0;
			p.speed = 0.1; 
			if (CurrentFrame > 0) { step = 30; }else step = 10;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(50 * int(CurrentFrame)+step, 133, 40, 60));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}
		/*if (Keyboard::isKeyPressed(Keyboard::W)) {
			p.dir = 3;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 307, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}*/
		/*if (Keyboard::isKeyPressed(Keyboard::S)) { 
			p.dir = 2;
			p.speed = 0.1;
			CurrentFrame += 0.005 * time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
			GetPlayerCoordinateForView(p.GetPlayerCoordinateX(), p.GetGlayerCoordinateY());
		}*/

		p.update(time);
		//ViewMap(time);//move camera without hero
		//changeview();//more move camera 
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
		std::ostringstream ScoreString;
		ScoreString << p.score;
		text.setString("Собрано камней: "+ ScoreString.str()); 
		text.setPosition(view.getCenter().x-265, view.getCenter().y-200);
		window.draw(p.sprite);
		window.draw(text);
		window.display();
	}
	return 0;
}
