//By lucassobreiro
//28 Jun 2021

#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

#define RESX 1280
#define RESY 720
#define STARLIMIT 100

typedef struct Star{
	int sSpeed;
	int sSize;
}Star;

int main(){
	Star star[STARLIMIT];
	Clock clock;
	float deltatime;
	srand(time(NULL));

	//Window
	RenderWindow window(VideoMode(RESX, RESY), "BG_Stars", Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorVisible(false);
	window.setKeyRepeatEnabled(false);

	//Star
	Texture starTex;
	if(!starTex.loadFromFile("Resources/star.png")){
		return -1;
	}
	RectangleShape starRec[STARLIMIT];
	for(int a=0; a<STARLIMIT; a++){
		star[a].sSpeed = rand()%20+5;
		star[a].sSize = rand()%5+2;
		starRec[a].setSize(Vector2f(star[a].sSize, star[a].sSize));
		starRec[a].setPosition(Vector2f(rand()%RESX, rand()%RESY));
		starRec[a].setTexture(&starTex);
	}

	//Background
	Texture bg;
	if(!bg.loadFromFile("Resources/background.png")){
		return -1;
	}
	Sprite bg_spr;
	bg_spr.setTexture(bg);
	bg_spr.setColor(Color(rand()&255, rand()&255, rand()&255, 150));

	//-------------------------------
	//Update
	//-------------------------------
	while(window.isOpen()){
		deltatime = clock.restart().asSeconds() * 60;
		Event evt;
		while(window.pollEvent(evt)){
			//Close application
			if(evt.type == Event::Closed){
				window.close();
			}
			if(evt.type == Event::KeyPressed){
				//New background color
				if(evt.key.code == Keyboard::Space){
					bg_spr.setColor(Color(rand()&255, rand()&255, rand()&255, 150));
				}
				//VerticalSync
				if(evt.key.code == Keyboard::V){
					window.setVerticalSyncEnabled(true);
				}
				if(evt.key.code == Keyboard::C){
					window.setVerticalSyncEnabled(false);
				}
				//Close application
				if(evt.key.code == Keyboard::Escape){
					window.close();
				}
			}
		}
		for(int a=0; a<STARLIMIT; a++){
			starRec[a].move(-star[a].sSpeed * deltatime, 0);
			if(starRec[a].getPosition().x < -3){
				star[a].sSpeed = rand()%20+5;
				star[a].sSize = rand()%5+2;
				starRec[a].setPosition(Vector2f(RESX, rand()%RESY));
				starRec[a].setSize(Vector2f(star[a].sSize, star[a].sSize));
			}
		}
		//-------------------------------
		//Draw
		//-------------------------------
		window.clear(Color::Black);
		window.draw(bg_spr);
		for(int a=0; a<STARLIMIT; a++){
			window.draw(starRec[a]);
		}
		window.display();
	}
	return 0;
}
