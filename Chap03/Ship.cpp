// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include"circleComponent.h"
#include "Game.h"
#include"Asteroid.h"
#include "Laser.h"

Ship::Ship(Game* game)
	:Actor(game)
	,mLaserCooldown(0.0f)
	,invisibleTimer(2, 2)
{
	// Create a sprite component
	sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));

	// Create an input component and set keys/speed
	ic = new InputComponent(this);
	ic->SetUpKey(SDL_SCANCODE_W);
	ic->SetDownKey(SDL_SCANCODE_S);
	ic->SetLeftKey(SDL_SCANCODE_A);
	ic->SetRightKey(SDL_SCANCODE_D);
	ic->SetMaxForce(3.0f);
	

	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(30.0f);

}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	invisibleTimer.first += deltaTime; 
	if (invisibleTimer.first >= invisibleTimer.second)
	{
		invisibleTimer.first = invisibleTimer.second;
		sc->SetVisible(true);
	}

	//for()

	if (!sc->IsVisible())
		return; 

	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			//우주선의 위치를 화면의 중심으로 초기화하고 회전값은 0으로 설정한다
			SetPosition(Vector2(1024 / 2, 768 / 2)); 
			SetRotation(0);
			ic->SetVelocity(Vector2(0, 0));
			invisibleTimer.first = 0;
			sc->SetVisible(false); 
			break;
		}
	}
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f)
	{
		// Create a laser and set its position/rotation to mine
		Laser* laser = new Laser(GetGame(), GetRotation());
		laser->SetPosition(GetPosition());
		
		// Reset laser cooldown (half second)
		mLaserCooldown = 0.5f;
	}
}
