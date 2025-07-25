// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
:Component(owner, updateOrder),
netForce(0, 0),
mass(30)
{
	
}

void MoveComponent::Update(float deltaTime)
{
	Vector2 pos = mOwner->GetPosition();

	Vector2 acc = Vector2(netForce.x / mass, netForce.y / mass) ;
	velocity += acc; 
	
	float rot = Math::Atan2(velocity.y, velocity.x); 
	mOwner->SetRotation(rot); 
	netForce = Vector2(0, 0); 

	// (Screen wrapping code only for asteroids)
	if (pos.x < 0.0f) { pos.x = 1022.0f; }
	else if (pos.x > 1024.0f) { pos.x = 2.0f; }

	if (pos.y < 0.0f) { pos.y = 766.0f; }
	else if (pos.y > 768.0f) { pos.y = 2.0f; }

	mOwner->SetPosition(pos + velocity);
}
