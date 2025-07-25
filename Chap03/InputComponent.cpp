// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
:MoveComponent(owner)
,mUpKey(0)
,mDownKey(0)
,mLeftKey(0)
,mRightKey(0),
mMaxForce(300)
{
	
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	
	Vector2 f = Vector2(0, 0);
	bool x = false;
	bool y = false;
	if (keyState[mUpKey])
	{
		f.y -= mMaxForce;
		y = true;
	}
	if (keyState[mDownKey])
	{
		f.y += mMaxForce;
		y = true;
	}
	if (keyState[mLeftKey])
	{
		f.x -= mMaxForce;
		x = true;
	}
	if (keyState[mRightKey])
	{
		f.x += mMaxForce;
		x = true;
	}

	if (x && y)
	{
		f.x /= 1.414f;
		f.y /= 1.414f;
	}
	
	AddForce(f);

}
