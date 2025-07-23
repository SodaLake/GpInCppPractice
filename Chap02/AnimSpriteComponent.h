// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SpriteComponent.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// Update animation every frame (overridden from component)
	void Update(float deltaTime) override;
	// Set the textures used for animation
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// Set/get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

	void AddPart(int first, int second);
	void SetPart(int part) { currentPart = part; mCurrFrame = ranges[currentPart].first; }
	void SetLoop(bool loop) { this->loop = loop; }

private:
	// All textures in the animation
	std::vector<SDL_Texture*> mAnimTextures;

	//각pair의 first는 시작지점, second는 끝지점을 의미한다.
	std::vector<std::pair<int, int>> ranges;
	//현재재생중인 pair. -1 이면 전체를 재생한다.
	int currentPart;
	//순환/비순환 지원
	bool loop;



	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};
