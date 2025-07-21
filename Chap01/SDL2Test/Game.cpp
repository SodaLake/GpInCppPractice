#include "Game.h"
#include<stdlib.h>
#include<time.h>
const int thickness = 15;
const float paddleH = 100.0f;
Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true),
	mPaddlePos{ 0,0 },
	mTicksCount(0),
	mPaddleDir{ 0,0 }

{

	mPaddlePos[0].x = 10.0f;
	mPaddlePos[0].y = 768.0f / 2.0f;


	mPaddlePos[1].x = 1014.0f - thickness;
	mPaddlePos[1].y = 768.0f / 2.0f;

}


bool Game::Initialize()
{
	balls.resize(5);
	srand(time(NULL));
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("GPinCPPChap1", 100, 100, 1024, 768, 0);


	if (!mWindow)
	{
		SDL_Log("Failed to create Window : %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, 01, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		return false;
	}


	for (int i = 0; i < balls.size(); i++)
	{
		balls[i].pos = { 1024.0f / 2.0f, 768 / 2 };
		balls[i].vel = { -150.f + rand() % 100, 185.f + rand() % 100 };

	}
	return true;


}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}

	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleDir[0] = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir[0] -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir[0] += 1;
	}

	mPaddleDir[1] = 0;
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir[1] -= 1;
	}
	if (state[SDL_SCANCODE_K])
	{
		mPaddleDir[1] += 1;
	}


}

void Game::UpdateGame()
{

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}


	mTicksCount = SDL_GetTicks();


	for (int i = 0; i < 2; i++)
	{
		if (mPaddleDir[i])
		{
			mPaddlePos[i].y += mPaddleDir[i] * 300 * deltaTime;

			if (mPaddlePos[i].y < (paddleH / 2 + thickness))
			{
				mPaddlePos[i].y = paddleH / 2 + thickness;
			}
			else if (mPaddlePos[i].y > (768.f - paddleH / 2.f - thickness))
			{
				mPaddlePos[i].y = (768.f - paddleH / 2.f - thickness);
			}
		}
	}

	for (int i = 0; i < balls.size(); i++)
	{
		balls[i].pos.x += balls[i].vel.x * deltaTime;
		balls[i].pos.y += balls[i].vel.y * deltaTime;

		// Bounce if needed
		// Did we intersect with the paddle?


		float diff = mPaddlePos[0].y - balls[i].pos.y;
		// Take absolute value of difference
		diff = (diff > 0.0f) ? diff : -diff;
		if (
			// Our y-difference is small enough
			diff <= paddleH / 2.0f &&
			// We are in the correct x-position
			balls[i].pos.x <= 25.0f && balls[i].pos.x >= 20.0f &&
			// The ball is moving to the left
			balls[i].vel.x < 0.0f)
		{
			balls[i].vel.x *= -1.0f;
		}

		diff = mPaddlePos[1].y - balls[i].pos.y;
		// Take absolute value of difference
		diff = (diff > 0.0f) ? diff : -diff;
		if (
			// Our y-difference is small enough
			diff <= paddleH / 2.0f &&
			// We are in the correct x-position
			balls[i].pos.x <= 1005.0f && balls[i].pos.x >= 1000.0f &&
			// The ball is moving to the right
			balls[i].vel.x > 0.0f)
		{
			balls[i].vel.x *= -1.0f;
		}





		// Did the ball go off the screen? (if so, end game)
		if (balls[i].pos.x <= 0.0f || balls[i].pos.x >= 1024.f)
		{
			// = false;
		}

		// Did the ball collide with the top wall?
		if (balls[i].pos.y <= thickness && balls[i].vel.y < 0.0f)
		{
			balls[i].vel.y *= -1;
		}
		// Did the ball collide with the bottom wall?
		else if (balls[i].pos.y >= (768 - thickness) &&
			balls[i].vel.y > 0.0f)
		{
			balls[i].vel.y *= -1;
		}

	}

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	SDL_RenderClear(mRenderer);

	//

	SDL_SetRenderDrawColor(mRenderer, 255, 0, 255, 255);
	SDL_Rect wall{ 0,0,1024,thickness };
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);




	// Draw paddle1
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos[0].x),
		static_cast<int>(mPaddlePos[0].y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	paddle.x = static_cast<int>(mPaddlePos[1].x);
	paddle.y = static_cast<int>(mPaddlePos[1].y - paddleH / 2);

	SDL_RenderFillRect(mRenderer, &paddle);

	// Draw ball
	SDL_Rect ball{
		static_cast<int>(balls[0].pos.x - thickness / 2),
		static_cast<int>(balls[0].pos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	for (int i = 1; i < balls.size(); i++)
	{
		ball.x = balls[i].pos.x - thickness / 2;
		ball.y = balls[i].pos.y - thickness / 2;
		SDL_RenderFillRect(mRenderer, &ball);
	}





	SDL_RenderPresent(mRenderer);
}
