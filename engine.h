#include <string>
#include <vector>
#include <SFML/System.hpp> 
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using std::vector;
using std::string;
using std::pair;

#ifndef __ENGINE_H
#define __ENGINE_H 1
namespace Engine
{

	struct SpriteCoords
	{
		int x,y,w,h;
	};

	struct SpriteSequence
	{
		string name;
		bool loop;
		int coef;
		float delay; //In seconds
		vector<SpriteCoords> coords;
	};

    /****************************
    Class ObjectProperties
    Description: Containes the essental parts of every object. To be directly implimented
				    in no higher level than game core
    Version: 1
    Added on initial build
    Level: Engine Core
    Notes:
    *****************************/
    class ObjectProperties
    {
	protected:
	    float xpos,ypos; 
		float xvel, yvel; 
	    int width,height;
    public:
		float x(),y(),w(),h();
	    float DistanceFrom(ObjectProperties);
	    void  
		    changeXRelitave(float x), 
		    changeYRelitave(float y), 
		    changePositionRelitave(float x,float y),
			changeVelocityRelative(float x, float y);

	    void  
		    changeXAbsolute(float x), 
		    changeYAbsolute(float y), 
		    changePostitionAbsolute(float x,float y),
			changeVelocityAbsolute(float x, float y);

	    void  
		    placeOnMap(float x,float y), 
		    redefine(int x, int y, int w, int h);

		void
			applyVelocity(float time);

	    void move(int dir);
		
	    sf::Texture img;
		sf::Sprite face;
	   virtual void draw(sf::RenderWindow* const screen);
		//drawAll(sf::RenderWindow screen); --- CURRENTLY NOT IMPLIMENTED ---

        sf::Vector2f toRect();

	    virtual void 
		    loadImg(string),
		    loadImg(string,int r,int g,int b);

	    int  drawW, drawH, drawStartX, drawStartY;


	    ObjectProperties();
    };

	/****************************
    Class Sprite
    Description: Contains commands to alter images in a sprite
    Version: 1.3
    Level: Engine Core
    Notes: 
    *****************************/
	class Sprite: public ObjectProperties
	{
		//The list of sequences
		vector<SpriteSequence> sequences;
		//The active sequence
		vector<SpriteSequence>::iterator active;
		//The frame in the active sequence
		vector<SpriteCoords>::iterator frame;

		sf::Color transparacy;

		void changeObject(SpriteCoords coords);
		void getSequence(string sequenceID, vector<SpriteSequence>::iterator &pIt);

		bool hasSequenceBeenSet, isForced;
		string afterForced;
		float delayMarker;
		bool isometricScaling;
		float isometricScale;
		int mapHeight; //For isometric scaling only.
	public:
		void setRGB(int R, int G, int B);

		void addSequence(string reference, float dealy, bool loop);
		void deleteSequence(string sequenceID);
		void addCoords(string sequenceID, SpriteCoords coords);
		void removeFromSequenceEnd(string sequenceID, SpriteSequence sequence), removeFromSequence(string sequenceID, int place, SpriteCoords sequence);
		void forceSequence(string sequenceID), forceSequence(string sequenceID, string after);
		void setActiveSequence(string sequenceID);
		void nextFrame(float time),resetFrame();
		void setIsomatricScale(float scale, int windowheight);
		void loadImg(string path), loadImg(string,int r,int g,int b);
		void applyVelocity(float time);

		//Sets the coords to a given place on the image given consistant sprite width and heights
		//Autowrap starting from top left.
		void getCoord(SpriteCoords &coords, int width, int height, int imgWidth, int imgHeight, int initialOffset, int tileNum);

		//Generate a sequence of tiles based off of the paramaters
		void genSequence(string sequenceID, int width, int height, int imgWidth, int imgHeight, int initialOffset, int tileStart, int tileEnd, float delay, bool loop);
		
	    void draw(sf::RenderWindow* const screen);

		Sprite():isForced(false),hasSequenceBeenSet(false),afterForced(""),delayMarker(0),isometricScaling(0),isometricScale(0),mapHeight(0){}
	}; 

	class DrawingOrder
	{
	private:
		vector<pair<ObjectProperties*,string>> list;
	public:
		void 
			addBottom(ObjectProperties *spr,string id), 
			addTop(ObjectProperties *spr, string id), 
			remove(string id), 
			moveUnder(string a, string b), 
			moveOver(string a, string b),
			moveToTop(string id),
			moveToBottom(string id);
		void draw(sf::RenderWindow *screen);
	};

    /****************************
    Class Window
    Description: A handler for a window
    Version: 1.1
    Level: Engine Core
    Notes:
    *****************************/
    class Window
    {
    public:
		sf::RenderWindow *screen;
	    ObjectProperties bg;
	    int w,h,bpp;
		std::string title;
	    Window(int w, int h, int bpp, string title);
		Window(const Window &other);
		~Window();
    };

	bool doesFileExist(std::string file);
}
#endif