#pragma once
#include<SDL.h>
#include<vector>



struct Vector2 {
	float x;
	float y;
};

struct Ball {
	Vector2 pos;
	Vector2 vel;
};
class Game

{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mTicksCount;


	int mPaddleDir[2];
	Vector2 mPaddlePos[2];



	std::vector<Ball> balls;
};

