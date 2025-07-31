// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AIState.h"
#include "AIComponent.h"
#include <SDL/SDL_log.h>
#include"Actor.h"
#include"Game.h"
#include"Enemy.h"
#include"Tower.h"
#include"Bullet.h"
void AIPatrol::Update(float deltaTime)
{
	SDL_Log("Updating %s state", GetName());

	Tower* owner = (Tower*)mOwner->GetOwner();
	
	//탱크를 조금씩 돌린다.
	float rot = owner->GetRotation();
	rot += 1 * deltaTime;
	owner->SetRotation(rot);

	
	if (owner->deathTimer <= 0.f)
	{
		mOwner->ChangeState("Death");
	}

	
	//적을 발견할경우 공격모드로 돌입한다.
	Enemy* e = owner->GetGame()->GetNearestEnemy(owner->GetPosition());
	if (e != nullptr)
	{
		// Vector from me to enemy
		Vector2 dir = e->GetPosition() - owner->GetPosition();
		float dist = dir.Length();
		if (dist < owner->AttackRange)
		{
			mOwner->ChangeState("Attack");
		}
	}

	

}

void AIPatrol::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIPatrol::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

void AIDeath::Update(float deltaTime)
{
	Tower* owner = (Tower*)mOwner->GetOwner();
	float scale = owner->GetScale();
	scale -= 0.5 * deltaTime;
	
	owner->SetScale(scale);

	if (scale <= 0)
		owner->SetState(Actor::State::EDead);
}

void AIDeath::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIDeath::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}

void AIAttack::Update(float deltaTime)
{

	Tower* owner = (Tower*)mOwner->GetOwner();
	if (owner->mNextAttack <= 0.0f)
	{
		Enemy* e = owner->GetGame()->GetNearestEnemy(owner->GetPosition());
		if (e != nullptr)
		{
			// Vector from me to enemy
			Vector2 dir = e->GetPosition() - owner->GetPosition();
			float dist = dir.Length();
			if (dist < owner->AttackRange)
			{
				// Rotate to face enemy
				owner->SetRotation(Math::Atan2(-dir.y, dir.x));
				// Spawn bullet at tower position facing enemy
				Bullet* b = new Bullet(owner->GetGame());
				b->SetPosition(owner->GetPosition());
				b->SetRotation(owner->GetRotation());
			}
			else
			{
				mOwner->ChangeState("Patrol");

			}
		}
		owner->mNextAttack = owner->AttackTime;
	}

	if (owner->deathTimer <= 0.f)
	{
		mOwner->ChangeState("Death");
	}
}

void AIAttack::OnEnter()
{
	SDL_Log("Entering %s state", GetName());
}

void AIAttack::OnExit()
{
	SDL_Log("Exiting %s state", GetName());
}
