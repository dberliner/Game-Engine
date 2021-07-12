#include <math.h>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "engine.h"
using std::vector;
using std::string;
using std::pair;

/*---------------------
Function name: doesFileExist
Purpose: Detects if a given file can be accessed
Paramaters: string file
Returns: true if it has access, false if it does not
Version: 2.3
Level: Core 
NOTE: 
	This function can not discern access issues and the file not existing. 
	A false return simply means that the file can not be accessed and 
	from the program's perspective its all the same because it will cause 
	the same crash.
---------------------*/
bool Engine::doesFileExist(std::string file)
{
	std::fstream fHnd;
	fHnd.open(file.c_str(),std::fstream::in);
	return !fHnd.fail();
}

float Engine::ObjectProperties::x(){
	return xpos;
}

float Engine::ObjectProperties::y(){
	return ypos;
}

float Engine::ObjectProperties::h(){
	return height;
}

float Engine::ObjectProperties::w(){
	return width;
}

/*---------------------
Function name: ObjectProperties
Purpose: Constructor for class ObjectProperties
Paramaters: None
Version: 1.0
Level: Core 
---------------------*/
Engine::ObjectProperties::ObjectProperties()
{
	xpos   = 0;
	ypos   = 0;
	width  = 0;
	height = 0;
}

/*---------------------
Function name: ObjectProperties::changeYRelitave
Purpose: Addes the Y position by the number specified
Paramaters: float change (the value we will add)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changeYRelitave(float change)
{
	ObjectProperties::ypos += change;
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::changeYRelitave
Purpose: Addes the X position by the number specified
Paramaters: float change (the value we will add)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changeXRelitave(float change)
{
	ObjectProperties::xpos += change;
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::changeYRelitave
Purpose: Addes the X and Y position by the number specified
Paramaters: float X(the value we will add to X), float Y(The value we will add to y)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changePositionRelitave(float X,float Y)
{
	ObjectProperties::xpos += X;
	ObjectProperties::ypos += Y;
	face.setPosition(xpos,ypos);
	return;
}


/*---------------------
Function name: ObjectProperties::changeVelocityRelative
Purpose: Addes the X and Y velocity by the number specified
Paramaters: float X(the value we will add to X), float Y(The value we will add to y)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changeVelocityRelative(float x, float y){
	xvel+=x;
	yvel+=y;
	face.setPosition(xpos,ypos);
}

/*---------------------
Function name: ObjectProperties::changeYAbsolute
Purpose: Changes the Y position to the specified location
Paramaters: float change (the value we assign Y to)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changeYAbsolute(float Y)
{
	ObjectProperties::ypos = Y;
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::changeXAbsolute
Purpose: Changes the X position to the specified location
Paramaters: float change (the value we assign X to)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changeXAbsolute(float X)
{
	ObjectProperties::ypos = X;
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::changePostitionAbsolute
Purpose: Changes the X abd Y position to the specified locations
Paramaters: float X(the value we will change xpos to), float Y(The value we will change ypos to)
Returns: Nothing.
Version: 1.0
Level: Core 
NOTE: This object is redefined in snake
---------------------*/
void Engine::ObjectProperties::changePostitionAbsolute(float X,float Y)
{
	ObjectProperties::xpos = X;
	ObjectProperties::ypos = Y;
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::changeVelocityRelative
Purpose: Addes the X and Y velocity by the number specified
Paramaters: float X(the value we will add to X), float Y(The value we will add to y)
Returns: Nothing.
Version: 1.0
Level: Core 
---------------------*/
void Engine::ObjectProperties::changeVelocityAbsolute(float x, float y){
	xvel=x;
	yvel=y;
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::loadFullImg
Purpose: Loads a complete image and sets the width and height to the total of the image
Paramaters: const char *path (the path of the BMP)
Returns: Returns the class' face
Version: 1.0
Level: Core 
NOTE: Works with the following image types:
		BMP, GIF, JPG, PNG, TIF, PNM, XPM, XCF, PCX, LBM 
Wrappers: LoadFullBMP(const char *path,int r,int g,int b)
---------------------*/
void Engine::ObjectProperties::loadImg(string path)
{
	if(Engine::doesFileExist(path))
	{
		img.loadFromFile(path);
		face.setTexture(img);
		
		sf::Vector2u tmpSize;

		tmpSize = img.getSize();
		width = tmpSize.x;
		height = tmpSize.y;

		drawStartX = 0;
		drawStartY = 0;
		return;
	}
}

/*---------------------
Function name: ObjectProperties::LoadFullBMP
Purpose: Loads a complete BMP with ObjectProperties::LoadFullBMP(const char *path) and adds RGB transparacy
Paramaters: const char *path (the path of the BMP) int r, int g, int b (the R G and B transparacy values)
Returns: The objects face.
Version: 1.0
Level: Core 
NOTE: None
---------------------*/
void Engine::ObjectProperties::loadImg(string path,int r,int g,int b)
{
	if(Engine::doesFileExist(path))
	{
		sf::Image tmp;
		tmp.loadFromFile(path);
		tmp.createMaskFromColor(sf::Color(r,g,b));
		img.loadFromImage(tmp);
		face.setTexture(img);

		sf::Vector2u tmpSize;
		tmpSize = img.getSize();
		width = tmpSize.x;
		height = tmpSize.y;

		drawStartX = 0;
		drawStartY = 0;
		return;
	}
}


/*---------------------
Function name: ObjectProperties::placeOnMap
Purpose: Places an object at a given point on the map
Paramaters: float xp, float yp (the x and y points to place the item on)
Returns: Nothing
Version: 1.0
Level: Core 
NOTE: Should probably be removed
---------------------*/
void Engine::ObjectProperties::placeOnMap(float xp, float yp)
{
	ObjectProperties::xpos = xp;
	ObjectProperties::ypos = yp;
	
	face.setPosition(xpos,ypos);
	return;
}

/*---------------------
Function name: ObjectProperties::Draw
Purpose: Draws the object's face on the screen
Paramaters: SDL_Surface *screen (the screen to draw it on)
Returns: Nothing
Version: 1.0
Level: Core 
NOTE: 
---------------------*/
void Engine::ObjectProperties::draw(sf::RenderWindow* const screen)
{
	screen->draw(face);
	return;
}

/*---------------------

--- CURRENTLY NOT IMPLIMENTED ---

Function name: ObjectProperties::DrawAll
Purpose: Draws the entire image, regardless of the data regarding size
Paramaters: SDL_Surface *screen (the screen to draw it on)
Returns: Nothing
Version: 1.0
Level: Core 
NOTE: 
---------------------
void Engine::ObjectProperties::drawAll(sf::RenderWindow screen)
{
	SDL_Rect dest;
	dest.x = (Sint16)ObjectProperties::xpos;
	dest.y = (Sint16)ObjectProperties::ypos;

	SDL_BlitSurface(ObjectProperties::face, NULL, screen, &dest);
	return;
}*/

/*---------------------
Function name: ObjectProperties::Redefine
Purpose: Redefines the size data of the image
Paramaters: int startx, int starty, int w, int h (the start x,y of the image, the width and height of the image)
Returns: Nothing
Version: 1.0
Level: Core 
NOTE: 
---------------------*/
void Engine::ObjectProperties::redefine(int startx, int starty, int w, int h)
{
	ObjectProperties::drawStartX = startx;
	ObjectProperties::drawStartY = starty;
	ObjectProperties::width  = w;
	ObjectProperties::height = h;
	return;
}

/*---------------------

-- NEEDS TO BE REWRITTEN TO ACCOUNT FOR ROTATED STATES --

Function name: ObjectProperties::toRect 
Purpose: Outputs an SDL_Rect with the objects properties
Paramaters: None
Returns: The SDL_Rect that this object represents.
Version: 1.0
Level: Core 
NOTE: 
---------------------
sf::Vector2f Engine::ObjectProperties::toRect()
{
    sf::Vector2f tempRect;
    tempRect.x = (int)ObjectProperties::xpos;
    tempRect.y = (int)ObjectProperties::ypos;
    tempRect.w = (int)ObjectProperties::width;
    tempRect.h = (int)ObjectProperties::height;

    return tempRect;
}*/


/*---------------------
Function name: applyVelocity
Purpose: Applies the velocity variables in the object
Paramaters:	
	float time
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::ObjectProperties::applyVelocity(float time)
{
	ObjectProperties::changePositionRelitave(xvel*time,yvel*time);
	return;
}
    
/*---------------------
Function name: Window::Window
Purpose: Readies the window
Paramaters: 
    Width of screen (in px)
    Height of screen (in px)
    Bits Per Pixel (usually 32)
    Additional Flags
Returns: Nothing
Version: 1.0
Level: Core 
NOTE: 
---------------------*/
Engine::Window::Window(int w, int h, int bpp, string title)
{
    Window::w=w;
    Window::h=h;
	Window::title=title;
	screen=new sf::RenderWindow(sf::VideoMode(w,h),title);

}
Engine::Window::~Window(){
	delete screen;
}
Engine::Window::Window(const Window &other){
	Window::h=other.h;
	Window::w=other.w;
	Window::screen=new sf::RenderWindow(sf::VideoMode(other.w,other.h),other.title);
}
void Engine::Sprite::forceSequence(string sequenceID)
{
	forceSequence(sequenceID,active->name);
}
void Engine::Sprite::forceSequence(string sequenceID, string after)
{
	if(!isForced){
		afterForced=after;
		setActiveSequence(sequenceID);
		isForced=true;
	}
}
/*---------------------
Function name: changeObject
Purpose: Changes the position and dimensions of the sprite
Paramaters:	
	SpriteCoords pCoords
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::changeObject(SpriteCoords pCoords)
{
	Sprite::redefine(pCoords.x,pCoords.y,pCoords.w,pCoords.h);
	return;
}


/*---------------------
Function name: addSequence
Purpose: Adds a sequence to the library
Paramaters:	
	string reference, 
	bool loop
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::addSequence(string reference, float delay, bool loop)
{
	SpriteSequence tmp;
	tmp.name=reference;
	tmp.loop=loop;
	tmp.coef=1;
	tmp.delay=delay;
	Sprite::sequences.push_back(tmp);
	return;
}

void Engine::Sprite::setIsomatricScale(float scale, int height){
	isometricScale=scale;
	isometricScaling=true;
	mapHeight=height;
}

/*---------------------
Function name: getSequence
Purpose: Points paramater pIt to the referenced sprite
Paramaters:	
	string sequenceID,
	vector<Engine::SpriteSequence>::iterator &pIt)
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::getSequence(string sequenceID, vector<Engine::SpriteSequence>::iterator &pIt)
{
	//Start by pointing at the beginning in case there is no match
	pIt=Sprite::sequences.begin();

	//Go though every sequence and find one with the given name
	for(pIt = Sprite::sequences.begin(); 
        pIt != Sprite::sequences.end();
        pIt++)
	{
		if((*pIt).name==sequenceID)
		{
			return;
		}
	}
	return;
}

/*---------------------
Function name: applyVelocity
Purpose: Applies the velocity variables in the object
Paramaters:	
	float time
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::applyVelocity(float time)
{
	ObjectProperties::changePositionRelitave(xvel*time,yvel*time);

	if(isometricScaling){
		float scale=isometricScale+(ypos/mapHeight)*(1-isometricScale);
		face.setScale(scale,scale);
	}
	return;
}


/*---------------------
Function name: deleteSequence
Purpose: Removes a sprite from the library
Paramaters:	
	string sequenceID
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::deleteSequence(string sequenceID)
{
	vector<Engine::SpriteSequence>::iterator tmpIt;
	Sprite::getSequence(sequenceID,tmpIt);
	Sprite::sequences.erase(tmpIt);
	return;
}

/*---------------------
Function name: addCoords
Purpose: Adds another set of coordinates to the end of the sprite sequence
Paramaters:	
	string sequenceID, 
	SpriteCoords coords
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::addCoords(string sequenceID, SpriteCoords coords)
{
	vector<Engine::SpriteSequence>::iterator tmpIt;
	Sprite::getSequence(sequenceID,tmpIt);
	(*tmpIt).coords.push_back(coords);
	return;
}

/*---------------------
To be implimented
---------------------*/
void Engine::Sprite::removeFromSequenceEnd(string sequenceID, SpriteSequence sequence)
{	
	return;
}

/*---------------------
To be implimented
---------------------*/
void Engine::Sprite::removeFromSequence(string sequenceID, int place, SpriteCoords sequence)
{
	return;
}

/*---------------------
Function name: addCoords
Purpose: Sets the sequence of motions this sprite should be using
Paramaters:	
	string sequenceID
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::setActiveSequence(string sequenceID)
{
	if(!isForced){
		//If we are running for the first time we can't make comparisons with an unset iterator
		if(hasSequenceBeenSet==false){
			hasSequenceBeenSet=true;
			Sprite::getSequence(sequenceID,Sprite::active);
			Sprite::frame=(*Sprite::active).coords.begin();
		}
		else
		{
			vector<Engine::SpriteSequence>::iterator tmpIt;
			Sprite::getSequence(sequenceID,tmpIt);
			//Only change the sequence if it is different
			if(tmpIt != Sprite::active){
				Sprite::active=tmpIt;
				Sprite::frame=(*Sprite::active).coords.begin();
			}
		}
	}
	return;
}

/*---------------------
Function name: addCoords
Purpose: Iterates the sprite to the next frame in the active sequence
Paramaters:	
	none
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::nextFrame(float time)
{
	delayMarker+=time;
	if(delayMarker >= active->delay){
		Sprite::frame += (*Sprite::active).coef;
		if((Sprite::frame==(*Sprite::active).coords.end() && (*Sprite::active).coef==1) || (Sprite::frame==(*Sprite::active).coords.begin() && (*Sprite::active).coef==-1))
		{
			if((*Sprite::active).loop==false){
			
				if(isForced){
					isForced=false;
					setActiveSequence(afterForced);
					afterForced="";
				}
				Sprite::frame=(*Sprite::active).coords.begin();
			}
			else
			{
				(*Sprite::active).coef *= -1;
				Sprite::nextFrame(0);
			}
		}
		delayMarker=0;
	}
	return;
}
void Engine::Sprite::resetFrame(){
	frame=active->coords.begin();
}
/*---------------------
Function name: addCoords
Purpose: Draws the sprite, differs from the inherited version of the function becuase this only displays part of an image
Paramaters:	
	SDL_Surface *screen
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::draw(sf::RenderWindow* const screen)
{
	const sf::IntRect tmpRect(
		(*Sprite::frame).x,
		(*Sprite::frame).y,
		(*Sprite::frame).w,
		(*Sprite::frame).h
	);
	face.setTextureRect(tmpRect);

	screen->draw(face);
	return;
}

/*---------------------
Function name: getCoord
Purpose: Sets a SpriteCoord object based off of the other paramaters given. Used for automatically generating coords in uniformly rectangular sprites
Paramaters:	
	SpriteCoords &coords, 
	int width, 
	int height, 
	int imgWidth, 
	int imgHeight, 
	int initialOffset, 
	int tileNum
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::getCoord(SpriteCoords &coords, int width, int height, int imgWidth, int imgHeight, int initialOffset, int tileNum)
{
	int xGridPos=(tileNum+initialOffset) % (imgWidth/width);
	int yGridPos=(int)floor((double)(tileNum+initialOffset)/(imgWidth/width));
	coords.w=width;
	coords.h=height;
	coords.x=xGridPos*width;
	coords.y=yGridPos*height;
	return;
}

/*---------------------
Function name: genSequence
Purpose: Generates a sprite, used for automatically generating large amounts of uniformly rectangular sprites.
Paramaters:	
	SDL_Surface *screen
Returns: none
Version: 1.3
Level: Core 
---------------------*/
void Engine::Sprite::genSequence(string sequenceID, int width, int height, int imgWidth, int imgHeight, int initialOffset, int tileStart, int tileCount, float delay, bool loop)
{
	SpriteCoords tmpCoords;
	Sprite::addSequence(sequenceID, delay,loop);
	for(int i=(tileStart); i<(tileStart+tileCount); i++)
	{
		getCoord(tmpCoords,width,height,imgWidth,imgHeight,initialOffset,i);
		Sprite::addCoords(sequenceID,tmpCoords);
	}
	Sprite::width=width;
	Sprite::height=height;
	return;
}


void Engine::Sprite::loadImg(string path)
{
	if(Engine::doesFileExist(path))
	{
		img.loadFromFile(path);
		face.setTexture(img);
		
		sf::Vector2u tmpSize;

		tmpSize = img.getSize();

		drawStartX = 0;
		drawStartY = 0;
		return;
	}
}

void Engine::Sprite::loadImg(string path,int r,int g,int b)
{
	if(Engine::doesFileExist(path))
	{
		sf::Image tmp;
		tmp.loadFromFile(path);
		tmp.createMaskFromColor(sf::Color(r,g,b));
		img.loadFromImage(tmp);
		face.setTexture(img);

		sf::Vector2u tmpSize;
		tmpSize = img.getSize();

		drawStartX = 0;
		drawStartY = 0;
		return;
	}
}
void Engine::DrawingOrder::addTop(ObjectProperties *spr, string id){
	list.push_back(make_pair(spr,id));
}
void Engine::DrawingOrder::addBottom(ObjectProperties *spr, string id){
	list.insert(list.begin(),make_pair(spr,id));
}



void Engine::DrawingOrder::moveOver(string a, string b)
{
	//Holders for the two items
	vector<pair<ObjectProperties*,string>>::iterator ita;
	pair<ObjectProperties*,string> tmp;
	int count=0;

	//Find the two items
	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
		if(i->second==a)
		{
			ita=i;
			count++;
			tmp=make_pair(i->first,i->second);
			i=list.erase(i);
			break;
		}
	}
	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
		if(i->second==b && count > 0)
		{
			list.insert(++i,tmp);
			break;
		}
	}
}

void Engine::DrawingOrder::moveUnder(string a, string b)
{
	//Holders for the two items
	vector<pair<ObjectProperties*,string>>::iterator ita;
	pair<ObjectProperties*,string> tmp;
	int count=0;

	//Find the two items
	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
		if(i->second==a)
		{
			ita=i;
			count++;
			tmp=make_pair(i->first,i->second);
			i=list.erase(i);
			break;
		}
	}
	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
		if(i->second==b && count > 0)
		{
			list.insert(i,tmp);
			break;
		}
	}
}

void Engine::DrawingOrder::moveToTop(string id)
{
	if(list.end()->second==id)
		return;

	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
		if(i->second==id){
			list.push_back(make_pair(i->first,i->second));
			list.erase(i);
		}
	}
}

void Engine::DrawingOrder::moveToBottom(string id){
	if(list.begin()->second==id)
		return;

	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
		if(i->second==id){
			list.insert(list.begin(),make_pair(i->first,i->second));
			i=list.erase(i);
		}
	}
}

void Engine::DrawingOrder::draw(sf::RenderWindow *screen){
	
	for(vector<pair<ObjectProperties*,string>>::iterator i=list.begin();i!=list.end();++i)
	{
			i->first->draw(screen);
	}
}