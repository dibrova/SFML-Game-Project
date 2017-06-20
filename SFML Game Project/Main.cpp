#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

class gmObject
{
public:
	gmObject() {};
	/*gmObject(Texture &texture ) { 
		sprite.setTexture(texture);
		rect = FloatRect(0, 0, 96 / 3, 128 / 4);
		sprite.setTextureRect(IntRect(rect));
		dx = dy = 0;
		currentFrame = 0;
	};*/

	size_t textW = 96 / 3, textH = 128 / 4, frCount = 3;
	
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float currentFrame;

	virtual void update(float time) {
		/*
		rect.left += dx;
		rect.top += dy;

		currentFrame += 0.005*time;
		if (currentFrame > frCount) currentFrame = 0;

		if (dx < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 1, textW, textH));
		if (dx > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 2, textW, textH));
		if (dy < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 3, textW, textH));
		if (dy > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 0, textW, textH));
		//std::cout << currentFrame << std::endl;
		sprite.setPosition(rect.left, rect.top);
		dx = dy = 0;
		*/
	}
	
	void moveLeft(float dx) { this->dx = -dx; };
	void moveRight(float dx) { this->dx = dx; };
	void moveUp(float dy) { this->dy = -dy; };
	void moveDown(float dy) { this->dy = dy; };

	~gmObject() { };
private:

};

class gmHero : public gmObject
{
public:
	gmHero (Texture &texture) {
	sprite.setTexture(texture);
	rect = FloatRect(0, 0, textW, textH);
	sprite.setTextureRect(IntRect(rect));
	dx = dy = 0;
	currentFrame = 0;
};

	void update(float time) {

		if (sprite.getPosition().x < 0) { moveRight(2); }
		if (sprite.getPosition().x > 640-32) { moveLeft(2); }
		if (sprite.getPosition().y < 0) { moveDown(2); }
		if (sprite.getPosition().y > 480-32) { moveUp(2); }

		rect.left += dx;
		rect.top += dy;
		
		currentFrame += 0.005*time;
		if (currentFrame > frCount) currentFrame = 0;

		if (dx < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 1, textW, textH));
		if (dx > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 2, textW, textH));
		if (dy < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 3, textW, textH));
		if (dy > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 0, textW, textH));
		
		//std::cout << currentFrame << std::endl;
		sprite.setPosition(rect.left, rect.top);
		dx = dy = 0;
	}

private:

};


class gmEnemy : public gmObject
{
public:

	gmEnemy(Texture &texture) {
		sprite.setTexture(texture);
		rect = FloatRect(0, 0, textW, textH);
		sprite.setTextureRect(IntRect(rect));
		dx = dy = 0;
		currentFrame = 0;
	}

	void update(float time) {

		currentFrame += 0.005*time;
		if (currentFrame > frCount) currentFrame = 0;

		/*if (sprite.getPosition().x < 640 - 32 && sprite.getPosition().y == 0) dx += 1;
		if (sprite.getPosition().x == 640 - 32 && sprite.getPosition().y < 480 - 32) dy += 1;
		if (sprite.getPosition().x > 0 && sprite.getPosition().y == 480 - 32) dx += -1;
		if (sprite.getPosition().x == 0 && sprite.getPosition().y > 0) dy += -1;*/

		if (sprite.getPosition().x < 640 - 32 && sprite.getPosition().y == 0) moveRight(1);
		else if (sprite.getPosition().x == 640 - 32 && sprite.getPosition().y < 480 - 32) moveDown(1);
		else if (sprite.getPosition().x > 0 && sprite.getPosition().y == 480 - 32) moveLeft(1);
		else if (sprite.getPosition().x == 0 && sprite.getPosition().y > 0) moveUp(1);

		rect.left += dx;
		rect.top += dy;

		if (dx < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 1, textW, textH));
		if (dx > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 2, textW, textH));
		if (dy < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 3, textW, textH));
		if (dy > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 0, textW, textH));

		//std::cout << currentFrame << std::endl;
		sprite.setPosition(rect.left, rect.top);
		dx = dy = 0;
	}
	

private:

};

class gmEnemyL : public gmObject
{
public:

	gmEnemyL(Texture &texture) {
		sprite.setTexture(texture);
		rect = FloatRect(0, 0, textW, textH);
		sprite.setTextureRect(IntRect(rect));
		dx = dy = 0;
		currentFrame = 0;
		
	}

	int offset = 0;

	void update(float time) {

		currentFrame += 0.005*time;
		if (currentFrame > frCount) currentFrame = 0;

		if (sprite.getPosition().x < 640 - 32 && sprite.getPosition().y == offset) moveRight(1);
		else if (sprite.getPosition().x == 640 - 32 && sprite.getPosition().y < offset+32) moveDown(1);
		else if (sprite.getPosition().x > 0 && sprite.getPosition().y == offset + 32) moveLeft(1);
		else if (sprite.getPosition().x == 0 && sprite.getPosition().y >= offset + 32 && sprite.getPosition().y < offset + 64) moveDown(1);
		else offset += 64;
		


		/*if (sprite.getPosition().x < 640 - 32 && sprite.getPosition().y == 0) moveRight(1);
		if (sprite.getPosition().x == 640 - 32 && sprite.getPosition().y < 32) moveDown(1);
		if (sprite.getPosition().x > 0 && sprite.getPosition().y == 32) moveLeft(1);
		if (sprite.getPosition().x == 0 && sprite.getPosition().y >= 32 && sprite.getPosition().y < 32*2) moveDown(1);

		if (sprite.getPosition().x < 640 - 32 && sprite.getPosition().y == 32*2) moveRight(1);
		if (sprite.getPosition().x == 640-32 && sprite.getPosition().y >= 32*2 && sprite.getPosition().y < 32 * 3) moveDown(1);
		if (sprite.getPosition().x > 0 && sprite.getPosition().y == 32*3) moveLeft(1);
		if (sprite.getPosition().x == 0 && sprite.getPosition().y >= 32 * 3 && sprite.getPosition().y < 32*4) moveDown(1);
*/
		//cout << sprite.getPosition().x << " , " << sprite.getPosition().y << endl;

		rect.left += dx;
		rect.top += dy;

		if (dx < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 1, textW, textH));
		if (dx > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 2, textW, textH));
		if (dy < 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 3, textW, textH));
		if (dy > 0) sprite.setTextureRect(IntRect((int)currentFrame * textW, textH * 0, textW, textH));

		//std::cout << currentFrame << std::endl;
		sprite.setPosition(rect.left, rect.top);
		dx = dy = 0;
	}


private:

};

auto gmRand(Clock clock) { return (rand()*clock.getElapsedTime().asMicroseconds()); }

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Game!");
	/*sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);*/

	CircleShape bulet(2); bulet.setFillColor(Color::Yellow); bulet.setPosition(Vector2f(640, 480));
	//RectangleShape bulet(Vector2f(2,2)); bulet.setFillColor(Color::Yellow); bulet.setPosition(Vector2f(640, 480));
	Vector2f bulMove(0, 0);

	window.setFramerateLimit(60);
	
	Clock clock;
	
	
	
	char *textureFiles[]{ "01.png", "02.png", "03.png", "03.png", "04.png", "05.png",
		"06.png","07.png","08.png","09.png","10.png","11.png","12.png","13.png","14.png","15.png",
	"16.png","17.png","18.png","19.png","20.png","21.png","22.png","23.png","24.png","25.png",
	"26.png","27.png","28.png","29.png","30.png","31.png","32.png","33.png","34.png","35.png","36.png","37.png"};



	Texture texture;
	//texture.loadFromFile("Cloaked dude.png");
	texture.loadFromFile(textureFiles[gmRand(clock) % 37]);
	gmHero player(texture);
	player.rect.left = gmRand(clock) % 20 * 32;
	player.rect.top = gmRand(clock) % 14 * 32;

	Texture texture2;
	//texture2.loadFromFile(textureFiles[rand()*clock.getElapsedTime().asMicroseconds() % 37]);
	texture2.loadFromFile(textureFiles[gmRand(clock) % 37]);
	gmEnemy enemy(texture2);
	enemy.rect.left = gmRand(clock) % 19 * 32;
	
	Texture texture3;
	texture3.loadFromFile(textureFiles[gmRand(clock) % 37]);
	gmEnemyL enemyL(texture3);
	enemyL.rect.left =gmRand(clock) % 20*32;
	enemyL.rect.top = gmRand(clock) % 14*32;

	

	Sprite wall;
	Texture textureWall;
	textureWall.loadFromFile("rpg_maker_vx__modernrtp_tilea2_by_painhurt-d3f7rwg.png");
	wall.setTexture(textureWall);

	
	list<gmObject*> gmList;
	//list<gmObject*>::iterator it;

	gmObject * ptr = nullptr;  
	//gmObject * ptrEnemy = &enemy;
	
	gmList.push_back(&player);
	gmList.push_back(&enemy);
	gmList.push_back(&enemyL);

	RectangleShape rectangle(Vector2f (32,32));
	size_t Map[640 / 32][480 / 32];
	for (size_t i = 0; i < 640 / 32; i++){
		for (size_t j = 0; j < 480 / 32; j++){
			Map[i][j] = gmRand(clock) % 3;
			std::cout << Map[i][j] << " ";
		} std::cout << std::endl;
	}
	
	Map[0][480/32 - 1] = 9;//test mine


	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		//time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		/*if (Keyboard::isKeyPressed(Keyboard::Key::Left)) player.dx = -1;
		if (Keyboard::isKeyPressed(Keyboard::Key::Right)) player.dx = 1;
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) player.dy = -1;
		if (Keyboard::isKeyPressed(Keyboard::Key::Down)) player.dy = 1;*/

		if (Keyboard::isKeyPressed(Keyboard::Key::Left)) player.moveLeft(1);
		if (Keyboard::isKeyPressed(Keyboard::Key::Right)) player.moveRight(1);
		if (Keyboard::isKeyPressed(Keyboard::Key::Up)) player.moveUp(1);
		if (Keyboard::isKeyPressed(Keyboard::Key::Down)) player.moveDown(1);
		
		if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
			//bulet.setPosition(player.sprite.getPosition());
			if (player.dx == -1) {bulMove.x = -2; bulMove.y = 0; 
			bulet.setPosition(player.sprite.getPosition() + Vector2f(-5, 15));}
			else if (player.dx == 1) {bulMove.x = 2; bulMove.y = 0;
			bulet.setPosition(player.sprite.getPosition() + Vector2f(33, 15));}	
			else if (player.dy == -1) {bulMove.x = 0; bulMove.y = -2;
			bulet.setPosition(player.sprite.getPosition() + Vector2f(15, -5));}		
			else if (player.dy == 1) {bulMove.x = 0; bulMove.y = 2;
			bulet.setPosition(player.sprite.getPosition() + Vector2f(15, 33));}
		}


		/*if (player2.sprite.getPosition().x < 640-32 && player2.sprite.getPosition().y==0) player2.dx += 1;
		if (player2.sprite.getPosition().x == 640 - 32 && player2.sprite.getPosition().y < 480 - 32) player2.dy += 1;
		if (player2.sprite.getPosition().x > 0 && player2.sprite.getPosition().y == 480 - 32) player2.dx += -1;
		if (player2.sprite.getPosition().x == 0 && player2.sprite.getPosition().y > 0) player2.dy += -1;*/

		/*if (player.rect.intersects(enemy.rect) && player.rect.top < enemy.rect.top) player.dy += -2;
		if (player.rect.intersects(enemy.rect) && player.rect.top > enemy.rect.top) player.dy += 2;
		if (player.rect.intersects(enemy.rect) && player.rect.left < enemy.rect.left) player.dx += -2;
		if (player.rect.intersects(enemy.rect) && player.rect.left > enemy.rect.left) player.dx += 2;*/

		if (player.rect.intersects(enemy.rect) && player.rect.top < enemy.rect.top) player.moveUp(1);
		if (player.rect.intersects(enemy.rect) && player.rect.top > enemy.rect.top) player.moveDown(1);
		if (player.rect.intersects(enemy.rect) && player.rect.left < enemy.rect.left) player.moveLeft(1);
		if (player.rect.intersects(enemy.rect) && player.rect.left > enemy.rect.left) player.moveRight(1);

		//for (it = myList.begin(); it != myList.end(); it++) { it->update(time); }

		for each (gmObject* var in gmList){
			if (var->sprite.getPosition().x==0 && var->sprite.getPosition().y==480-32){
				//myList.remove(var);
				ptr = var;
				std::cout << "action!\n"; continue;				
			}

			if (var->rect.intersects(bulet.getGlobalBounds())) { ptr = var; 
			std::cout << "kill!\n"; bulet.setPosition(Vector2f(640, 480));}// kill enemy
			
			else var->update(time);
			//std::cout << &var; std::cout << "\n";
			
		}
		//for (it = myList.begin(); it != myList.end(); it++) {std::cout<< it->currentFrame <<std::endl; }
		//std::cout << myList.size(); std::cout << "\n";
		if (ptr) {	gmList.remove(ptr);	ptr = nullptr; }

		


		//player.update(time);
		//enemy.update(time);
		window.clear();
		//window.draw(shape);


	/*	for (size_t i = 0; i < 640 / 32; i++) 
			for (size_t j = 0; j < 480 / 32; j++) {
				if (Map[i][j] == 1) rectangle.setFillColor(Color::Color(150,150,150));
				if (Map[i][j] == 2) rectangle.setFillColor(Color::Green);
				if (Map[i][j] == 0) continue;
				rectangle.setPosition(i * 32, j * 32);
				window.draw(rectangle);
			} */
		

		for (size_t i = 0; i < 640 / 32; i++)
			for (size_t j = 0; j < 480 / 32; j++) {
				if (Map[i][j] == 1) wall.setTextureRect(IntRect(4*32, 0*32, 32, 32));
				if (Map[i][j] == 2) wall.setTextureRect(IntRect(3*32, 0*32, 32, 32));
				if (Map[i][j] == 0) wall.setTextureRect(IntRect(6*32, 0*32, 32, 32));//continue;

				if (Map[i][j] == 9) wall.setTextureRect(IntRect(6*32, 6*32, 32, 32));//test mine

				wall.setPosition(Vector2f(i * 32, j * 32));
				window.draw(wall);
			}


		//for (it = myList.begin(); it != myList.end(); it++) { window.draw(it->sprite); }
		/*window.draw(player.sprite);
		window.draw(enemy.sprite);*/


		for each (gmObject* var in gmList) window.draw(var->sprite);
		
		if (bulet.getPosition().x < 640 && bulet.getPosition().x > -3 &&
			bulet.getPosition().y < 480 && bulet.getPosition().y > -3) bulet.move(bulMove);

		window.draw(bulet);

		window.display();
	}

	return 0;
}