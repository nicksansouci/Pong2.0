#include "raylib.h"
#include "attributes.h"
#include <iostream>
#include <cstdlib>

int main()
{
	InitWindow(800, 600, "Pong 2.0");
	//The game can use a dynamic resolution (1280x720 etc.) but I designed it
	// in 800x600 for the most ideal scale.
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = (GetScreenWidth() / 2.0f);
	ball.y = (GetScreenHeight() / 2.0f);
	ball.radius = 5;
	ball.speed_x = 250;
	ball.speed_y = 250;

	Paddle LP;
	LP.x = 35;
	LP.y = (GetScreenHeight() / 2);
	LP.width = 10;
	LP.height = 100;
	LP.speed = 500;

	Paddle RP;
	RP.x = (GetScreenWidth() - 35);
	RP.y = (GetScreenHeight() / 2);
	RP.width = 10;
	RP.height = 100;
	RP.speed = 500;

	PowerUpBox PowerBox;
	PowerBox.x = (275 + (rand() % 100) + (rand() % 100));
	PowerBox.y = (150 + (rand() % 100) + (rand() % 100));
	PowerBox.height = 30;
	PowerBox.width = 30;

	const char* winnerText = nullptr;
	const char* powerupText = nullptr;
	const char* playagainText = nullptr;
	int scoreLP = 0;
	int scoreRP = 0;
	

	while (!(WindowShouldClose()))
	{
		
		int count = 0;
		ball.x += ball.speed_x * GetFrameTime();
		ball.y += ball.speed_y * GetFrameTime();
		//Conditionals to keep the ball within the vertical bounds of the screen
		if (ball.y > GetScreenHeight())
		{
			ball.y = GetScreenHeight();
			ball.speed_y *= -1;
		}
		if (ball.y < 0)
		{
			ball.y = 0;
			ball.speed_y *= -1;
		}
		//Movement keys for paddles
		if (IsKeyDown(KEY_W))
		{
			LP.y -= LP.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_S))
		{
			LP.y += LP.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP))
		{
			RP.y -= RP.speed * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN))
		{
			RP.y += RP.speed * GetFrameTime();
		}
		//Conditionals to keep the paddles from moving off of the screen
		if (LP.y > GetScreenHeight())
		{
			LP.y = GetScreenHeight();
			
		}
		if (LP.y < 0)
		{
			LP.y = 0;
			
		}
		if (RP.y > GetScreenHeight())
		{
			RP.y = GetScreenHeight();

		}
		if (RP.y < 0)
		{
			RP.y = 0;

		}
		//Check for collision of ball and paddle for left paddle
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, LP.GetRectangle()))
		{
			if (ball.speed_x < 0)
			{
				ball.speed_x *= -1.2f;

				ball.speed_y = (ball.y - LP.y) / (LP.height / 2) * ball.speed_x;

			}
		}
		//Same collision check for right paddle
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, RP.GetRectangle()))
		{
			if (ball.speed_x > 0)
			{
				ball.speed_x *= -1.2f;
				//Physics for ball.speed_y when hit at a certain spot on the paddle
				//First take the y pos of the ball - y pos of the paddle, then divide by RP height/2
				// and finally reverse the ball speed, sending it in the opposite direction (x plane)
				ball.speed_y = (ball.y - RP.y) / (RP.height / 2) * -ball.speed_x;
			
			}
			
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, PowerBox.GetPowerBox()))
		{
			ball.speed_x *= 1.5f;
			PowerBox.x = (275 + (rand() % 100) + (rand() % 100));;
			PowerBox.y = (150 + (rand() % 100) + (rand() % 100));
			count = 1;
		}

		if (ball.x < 0)
		{
			winnerText = "Right Player Wins!";
			PowerBox.width = 0;
			PowerBox.height = 0;
			scoreRP += 1;
		}
		if (ball.x > GetScreenWidth())
		{
			winnerText = "Left Player Wins!";
			PowerBox.width = 0;
			PowerBox.height = 0;
			scoreLP += 1;
		}
		if (ball.x < 100)
		{
			powerupText = "Hit the power box for a speed boost!";
		}
		if (winnerText && IsKeyPressed(KEY_ENTER))
		{
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speed_x = 250;
			ball.speed_y = 250;
			winnerText = nullptr;
			powerupText = nullptr;
			PowerBox.width = 30;
			PowerBox.height = 30;


		}

		BeginDrawing();
		//Create background and display FPS function
			ClearBackground(BLACK);
			DrawFPS(675, 10);
			//Implement the ball and the paddles on the screen
			ball.Draw();
			LP.Draw();
			RP.Draw();
			PowerBox.Draw();
			if (powerupText)
			{
				DrawText(powerupText, 250, GetScreenHeight() / 10, 15, MAGENTA);

			}
			
			if (winnerText)
			{
				DrawText(winnerText, 170, GetScreenHeight() / 2.5, 55, YELLOW);
				powerupText = nullptr;
				playagainText = "Press Enter to Play Again.";
				DrawText(playagainText, 250, GetScreenHeight() / 1.5, 25, MAGENTA);
				
			}
			


		EndDrawing();


	}


	CloseWindow();

	return 0;
}