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

	//��pair�� first�� ��������, second�� �������� �ǹ��Ѵ�.
	std::vector<std::pair<int, int>> ranges;
	//����������� pair. -1 �̸� ��ü�� ����Ѵ�.
	int currentPart;
	//��ȯ/���ȯ ����
	bool loop;



	// Current frame displayed
	float mCurrFrame;
	// Animation frame rate
	float mAnimFPS;
};
