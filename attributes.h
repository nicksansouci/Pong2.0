#pragma once
#include <string>

struct Ball
{
	float x, y;
	float speed_x, speed_y;
	float radius;

	void Draw()
	{
		DrawCircle(int(x), int(y), int(radius), WHITE);
	}

};

struct Paddle
{
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRectangle()
		//Returns rectangle with parameters
	{
		return Rectangle{ x - (width / 2), y - (height / 2), width, height};
	}
	
	void Draw()
	{
		//Draw rectangle based on GetRectangle function
		DrawRectangleRec(GetRectangle(), WHITE);
	}
};

struct PowerUpBox
{
	float x, y;
	float width, height;

	void Draw()
	{
		DrawRectangle(x, y, width, height, MAGENTA);
	}

	Rectangle GetPowerBox()
		//Returns rectangle with parameters
	{
		return Rectangle{ x, y, width, height };
	}

};



