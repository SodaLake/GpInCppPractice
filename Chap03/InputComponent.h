// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "MoveComponent.h"
#include <cstdint>

class InputComponent : public MoveComponent
{
public:
	// Lower update order to update first
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;
	
	// Getters/setters for private variables
	float GetMaxForce() const { return mMaxForce; }
	int GetUpKey() const { return mUpKey; }
	int GetDownKey() const { return mDownKey; }
	int GetLeftKey() const { return mLeftKey; }
	int GetRightKey() const { return mRightKey; }

	void SetMaxForce(float speed) { mMaxForce = speed; }
	
	void SetUpKey(int key) { mUpKey = key; }
	void SetDownKey(int key) { mDownKey = key; }
	void SetLeftKey(int key) { mLeftKey = key; }
	void SetRightKey(int key) { mRightKey = key; }
private:
	// The maximum forward/angular speeds
	float mMaxForce; 
	// Keys for forward/back movement
	int mUpKey;
	int mDownKey;
	// Keys for angular movement
	int mLeftKey;
	int mRightKey;
};
