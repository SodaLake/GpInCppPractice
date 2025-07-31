// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <vector>

class BoardState
{
public:
	enum SquareState { Empty, Red, Yellow };
	BoardState();
	std::vector<BoardState*> GetPossibleMoves(SquareState player) const;
	bool IsTerminal() const;
	float GetScore() const;

	SquareState mBoard[6][7];
protected:
	bool IsFull() const;
	int GetFourInARow() const;
	float CalculateHeuristic() const;
};

struct GTNode
{
	// Children nodes
	std::vector<GTNode*> mChildren;
	// State of game
	BoardState* mState;
	GTNode(BoardState* mState)
		:mState(mState)
	{

	}
	~GTNode()
	{
		for (auto i : mChildren)
		{
			delete i;
		}
	}
};

// Try to place the player's piece
bool TryPlayerMove(class BoardState* state, int column);

// Make the next CPU move
void CPUMove(class BoardState* state);

float AlphaBetaMin(GTNode* node, int depth, float alpha, float beta);
float AlphaBetaMax(GTNode* node, int depth, float alpha, float beta);
GTNode* AlphaBetaDecide(GTNode* root, int maxDepth);