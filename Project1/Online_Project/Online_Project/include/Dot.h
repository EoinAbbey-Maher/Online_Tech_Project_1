#pragma once
#include "LTexture.h"
#include "GameClient.h"
#include <string>
#include <vector>
#include <sstream>


using namespace std;

struct not_Digit
{
	bool operator()(const char c)
	{
		return c != ' ' && !isdigit(c);
	}
};

class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 5;

	Dot() {};
	//Initializes the variables
	Dot(bool chaser, GameClient* t_client = nullptr);
	~Dot();

	void Init(SDL_Renderer *gRenderer, std::string t_texture);
	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	void updateServerPositionOut();
	void updateServerPosGet();

	//Moves the dot
	void move(int SCREEN_HEIGHT, int SCREEN_WIDTH);

	//Shows the dot on the screen
	void render(SDL_Renderer *gRenderer);

	std::string GetPosAsString();

	bool Checkcollision(int centerX, int centerY);

	bool GetLocal() { return isLocalplayer; };

	int GetCenterX();
	int GetCenterY();

	void SetPosition(int x, int y);

private:

	not_Digit isNotADigit;

	bool isLocalplayer;
	bool isChaser;

	GameClient* m_client = nullptr;

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	int width, height;

	int mCenterX, mCenterY;
	//The velocity of the dot
	int mVelX, mVelY;

	LTexture gDotTexture;

	std::string m_recievedServerMsg;
	
};