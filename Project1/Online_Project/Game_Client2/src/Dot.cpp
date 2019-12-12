#include "Dot.h"

Dot::Dot(bool local, GameClient* t_client) :
	m_client(t_client)
{
	isLocalplayer = local;
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	if (isChaser)
	{
		gDotTexture.setColor(244, 66, 66);
	}
	else
	{
		gDotTexture.setColor(66, 69, 244);
	}

	width = 10;
	height = 10;
}

Dot::~Dot()
{
	gDotTexture.free();
}

void Dot::SetPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;

	mCenterX = mPosX + (width / 2);
	mCenterY = mPosY + (height / 2);
}

//"dot.bmp"
void Dot::Init(SDL_Renderer* gRenderer, std::string t_texture)
{
	if (isLocalplayer)
	{
		if (!gDotTexture.loadFromFile("Resources/BlueDot.bmp", gRenderer))
		{
			printf("Failed to load dot texture!\n");
		}
	}
	else
	{
		if (!gDotTexture.loadFromFile("Resources/RedDot.bmp", gRenderer))
		{
			printf("Failed to load dot texture!\n");
		}
	}

	updateServerPositionOut();
	updateServerPosGet();
}

void Dot::handleEvent(SDL_Event& e)
{

	if (isLocalplayer)
	{
		//If a key was pressed
		if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY = -DOT_VEL;
				mPosY += mVelY;
				SetPosition(mPosX, mPosY);
				updateServerPositionOut();
				break;

			case SDLK_s: mVelY = DOT_VEL;
						mPosY += mVelY;
						SetPosition(mPosX, mPosY);
				updateServerPositionOut();
				break;

			case SDLK_a: mVelX = -DOT_VEL;
				mPosX += mVelX;
				SetPosition(mPosX, mPosY);
				updateServerPositionOut();
				break;

			case SDLK_d: mVelX = DOT_VEL;
				mPosX += mVelX;
				SetPosition(mPosX, mPosY);
				updateServerPositionOut();
				break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: mVelY = 0; break;
			case SDLK_s: mVelY = 0; break;
			case SDLK_a: mVelX = 0; break;
			case SDLK_d: mVelX = 0; break;
			}
		}
	}

}

void Dot::updateServerPositionOut()
{
	m_client->SendString(std::to_string(isChaser) + "is Chaser" + GetPosAsString());
}

void Dot::updateServerPosGet()
{
	m_recievedServerMsg = m_client->m_recievedMessage;
	if (m_recievedServerMsg != "")
	{
		std::cout << m_client->m_recievedMessage << std::endl;
		string::iterator end = std::remove_if(m_recievedServerMsg.begin(), m_recievedServerMsg.end(), isNotADigit);

		std::string allNumbers(m_recievedServerMsg.begin(), end);

		std::stringstream ss(allNumbers);
		vector<int> NumVec;

		int i;
		for (; ss >> i;)
		{
			NumVec.push_back(i);
		}

		if (!isLocalplayer)
		{
			SetPosition(NumVec[1], NumVec[2]);
		}

		m_recievedServerMsg = "";
	}
}

void Dot::move(int SCREEN_HEIGHT, int SCREEN_WIDTH)
{
	updateServerPosGet();

}

void Dot::render(SDL_Renderer* gRenderer)
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY, gRenderer);
}

string Dot::GetPosAsString()
{
	return string("X: " + std::to_string(mPosX) + ", " + "Y: " + std::to_string(mPosY));
}

int Dot::GetCenterX()
{
	return mCenterX;
}

int Dot::GetCenterY()
{
	return mCenterY;
}

bool Dot::Checkcollision(int centerX, int centerY)
{
	double distance = sqrt(((mCenterX - centerX) * (mCenterX - centerX)) + ((mCenterY - centerY) * (mCenterY - centerY)));

	if (distance <= width)
	{
		return true;
	}
	else
	{
		return false;
	}
}