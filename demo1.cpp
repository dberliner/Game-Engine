 #define _CRT_SECURE_NO_WARNINGS 1

#include <math.h>
#include <iostream>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine.h"
using namespace std;
using namespace Engine;


void init();
int x,y;
ObjectProperties bg;
Window window(800,600,32, "Test");
Sprite sprite,tree;
DrawingOrder scene;
int centerX, centerY, radius;
const float _X_VEL=100;
const float _Y_VEL=100;
const float _VEL_45=_X_VEL/sqrt(2);
enum dirs {N,S,W,E,NW,SW,SE,NE};
dirs dir=E;

void newCoords(SpriteCoords &handle, int x, int y, int w, int h)
{
	handle.x=x;
	handle.y=y;
	handle.w=w;
	handle.h=h;
}

void script_loadSprites()
{
	sprite.genSequence("runningE" ,96,96,1536,2784,8,320,8,0.2f,false); //Automatically generate 96x96 pixel sprites from a 1536x2784 pixel sheet with 8 pixels of initial offset. Generate 8 tiles. 0.25sec delay (false is not currently implimented)
	sprite.genSequence("runningN" ,96,96,1536,2784,8,328,8,0.2f,false); 
	sprite.genSequence("runningNE",96,96,1536,2784,8,336,8,0.2f,false);
	sprite.genSequence("runningNW",96,96,1536,2784,8,344,8,0.2f,false);
	sprite.genSequence("runningS" ,96,96,1536,2784,8,352,8,0.2f,false);
	sprite.genSequence("runningSE",96,96,1536,2784,8,360,8,0.2f,false);
	sprite.genSequence("runningSW",96,96,1536,2784,8,368,8,0.2f,false);
	sprite.genSequence("runningW" ,96,96,1536,2784,8,376,8,0.2f,false);


	sprite.genSequence("standingE" ,96,96,1536,2784,8,320,1,numeric_limits<float>::max( ),false); //Automatically generate 96x96 pixel sprites from a 1536x2784 pixel sheet with 8 pixels of initial offset. Generate 8 tiles. 0.25sec delay (false is not currently implimented)
	sprite.genSequence("standingN" ,96,96,1536,2784,8,328,1,numeric_limits<float>::max( ),false); 
	sprite.genSequence("standingNE",96,96,1536,2784,8,336,1,numeric_limits<float>::max( ),false);
	sprite.genSequence("standingNW",96,96,1536,2784,8,344,1,numeric_limits<float>::max( ),false);
	sprite.genSequence("standingS" ,96,96,1536,2784,8,352,1,numeric_limits<float>::max( ),false);
	sprite.genSequence("standingSE",96,96,1536,2784,8,360,1,numeric_limits<float>::max( ),false);
	sprite.genSequence("standingSW",96,96,1536,2784,8,368,1,numeric_limits<float>::max( ),false);
	sprite.genSequence("standingW" ,96,96,1536,2784,8,376,1,numeric_limits<float>::max( ),false);


	sprite.genSequence("swordSwingE" ,96,96,1536,2784,8,0,13,0.1f ,false);
	sprite.genSequence("swordSwingN" ,96,96,1536,2784,8,13,13,0.1f,false);
	sprite.genSequence("swordSwingNE",96,96,1536,2784,8,26,13,0.1f,false);
	sprite.genSequence("swordSwingNW",96,96,1536,2784,8,39,13,0.1f,false);
	sprite.genSequence("swordSwingS" ,96,96,1536,2784,8,52,13,0.1f,false);
	sprite.genSequence("swordSwingSE",96,96,1536,2784,8,65,13,0.1f,false);
	sprite.genSequence("swordSwingSW",96,96,1536,2784,8,78,13,0.1f,false);
	sprite.genSequence("swordSwingW" ,96,96,1536,2784,8,91,13,0.1f,false);

	
	tree.genSequence("treeStanding" ,160,224,1440,224,0,0,1,0.1f ,false);
	tree.genSequence("treeFalling" ,160,224,1440,224,0,0,8,0.1f ,false);
	return;
}


int main(int argc, char ** argv)
{  
	script_loadSprites();
	sprite.loadImg("img/big.png",111,79,51);
	tree.loadImg("img/tree.png",94,66,41);

	//Activate the running east sequence
	sprite.setActiveSequence("runningE");
	tree.setActiveSequence("treeStanding");

	//Place our sprite at 100,100
	sprite.placeOnMap(100,100);
	tree.placeOnMap(300,300);

	//Set up the isomorphic scale
	sprite.setIsomatricScale(0.7,600);

	// Set up the background image
	bg.loadImg("img\\environment_forest_alt1.png");

	// Set up the clock
	sf::Clock clock;
	float tmpTime,spriteTime=0,frameTime=0;

	//Only move the frame if some key is down
	bool isKeyDown=false;

	
	int done=0;
	
	scene.addTop(&bg,"bg");
	scene.addTop(&sprite,"sprite");
	scene.addTop(&tree,"tree");

	while( done == 0)
	{
		tmpTime=clock.restart().asSeconds();
		spriteTime += tmpTime;
		frameTime += tmpTime;
        // Process events
        sf::Event Event;
		while (window.screen->pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed){
                window.screen->close();
				done=1;
			}
        }
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			isKeyDown=true;
		else
			isKeyDown=false;
		

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if(dir==NW)
				sprite.forceSequence("swordSwingNW");
			else if(dir==NE)
				sprite.forceSequence("swordSwingNE");
			else if(dir==SW)
				sprite.forceSequence("swordSwingSW");
			else if(dir==SE)         
				sprite.forceSequence("swordSwingSE");
			else if(dir==W)
				sprite.forceSequence("swordSwingW");
			else if(dir==E)
				sprite.forceSequence("swordSwingE");
			else if(dir==S) 
				sprite.forceSequence("swordSwingS");
			else if(dir==N)
				sprite.forceSequence("swordSwingN");
		}
 		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sprite.setActiveSequence("runningNW");
			sprite.changeVelocityAbsolute(-_VEL_45,-_VEL_45);
			dir=NW;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sprite.setActiveSequence("runningNE");
			sprite.changeVelocityAbsolute(_VEL_45,-_VEL_45);
			dir=NE;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sprite.setActiveSequence("runningSW");
			sprite.changeVelocityAbsolute(-_VEL_45,_VEL_45);
			dir=SW;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sprite.setActiveSequence("runningSE");
			sprite.changeVelocityAbsolute(_VEL_45,_VEL_45);
			dir=SE;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.setActiveSequence("runningW");
			sprite.changeVelocityAbsolute(-_X_VEL,0);
			dir=W;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setActiveSequence("runningE");
			sprite.changeVelocityAbsolute(_X_VEL,0);
			dir=E;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sprite.setActiveSequence("runningS");
			sprite.changeVelocityAbsolute(0,_Y_VEL);
			dir=S;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sprite.setActiveSequence("runningN");
			sprite.changeVelocityAbsolute(0,-_Y_VEL);
			dir=N;
		}
		else
		{
			sprite.changeVelocityAbsolute(0,0);
			if(dir==NW)
				sprite.setActiveSequence("standingNW");
			else if(dir==NE)
				sprite.setActiveSequence("standingNE");
			else if(dir==SW)
				sprite.setActiveSequence("standingSW");
			else if(dir==SE)
				sprite.setActiveSequence("standingSE");
			else if(dir==W)
				sprite.setActiveSequence("standingW");
			else if(dir==E)
				sprite.setActiveSequence("standingE");
			else if(dir==S)
				sprite.setActiveSequence("standingS");
			else if(dir==N)
				sprite.setActiveSequence("standingN");
		}

		//Layering
		if(sprite.y()+sprite.h()/2-20 > tree.y()+tree.h()/2)
		{
			int a=sprite.y()+sprite.h();
			int b=tree.y()+tree.h();

			scene.moveOver("sprite","tree");
		}
		else
		{
			scene.moveUnder("sprite","tree");
		}

		//Move the sprite
		sprite.applyVelocity(tmpTime);

		//If 100ms has passed iterate the sprite
		if(spriteTime > 0.2)
		{
			sprite.nextFrame(tmpTime);
		}

		if(frameTime > 0.0166){
			frameTime=0;
			//Draw the items
			window.screen->clear();
			scene.draw(window.screen);
			// Display window contents on screen
			window.screen->display(); 

		}
	}
	return 0;
}
