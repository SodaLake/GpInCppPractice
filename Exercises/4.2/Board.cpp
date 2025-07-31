// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Board.h"
#include "Random.h"

BoardState::BoardState()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			mBoard[i][j] = Empty;
		}
	}
}

std::vector<BoardState*> BoardState::GetPossibleMoves(SquareState player) const
{
	std::vector<BoardState*> retVal;

	// For each column, find if a move is possible
	for (int col = 0; col < 7; col++)
	{
		for (int row = 5; row >= 0; row--)
		{
			if (mBoard[row][col] == BoardState::Empty)
			{
				retVal.emplace_back(new BoardState(*this));
				retVal.back()->mBoard[row][col] = player;
				break;
			}
		}
	}

	return retVal;
}

bool BoardState::IsTerminal() const
{
	// Is the board full?
	if (IsFull())
	{
		return true;
	}

	// Is there a four-in-a-row?
	int fourInRow = GetFourInARow();
	if (fourInRow != 0)
	{
		return true;
	}

	return false;
}

float BoardState::GetScore() const
{
	// If the board is full, the score is 0
	if (IsFull())
	{
		return 0.0f;
	}

	// Is there a four-in-a-row?
	int fourInRow = GetFourInARow();
	if (fourInRow != 0)
	{
		return static_cast<float>(fourInRow);
	}

	return CalculateHeuristic();
}

bool BoardState::IsFull() const
{
	bool isFull = true;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (mBoard[i][j] == Empty)
			{
				isFull = false;
			}
		}
	}

	return isFull;
}

int BoardState::GetFourInARow() const
{
	// Returns -1 if yellow wins, 1 if red wins, 0 otherwise

	// Check if there's a row with four in a row
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (mBoard[row][col] == mBoard[row][col + 1] &&
				mBoard[row][col] == mBoard[row][col + 2] &&
				mBoard[row][col] == mBoard[row][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	// Check if there's a column with four in a row
	for (int col = 0; col < 7; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (mBoard[row][col] == mBoard[row + 1][col] &&
				mBoard[row][col] == mBoard[row + 2][col] &&
				mBoard[row][col] == mBoard[row + 3][col])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	// Check if there's a right diagonal four in a row
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			if (mBoard[row][col] == mBoard[row + 1][col + 1] &&
				mBoard[row][col] == mBoard[row + 2][col + 2] &&
				mBoard[row][col] == mBoard[row + 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}

	// Check if there's a left diagonal for in a row
	for (int col = 0; col < 4; col++)
	{
		for (int row = 3; row < 6; row++)
		{
			if (mBoard[row][col] == mBoard[row - 1][col + 1] &&
				mBoard[row][col] == mBoard[row - 2][col + 2] &&
				mBoard[row][col] == mBoard[row - 3][col + 3])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					return -1;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

float BoardState::CalculateHeuristic() const
{
	// TODO: You could change this to calculate an actual heuristic
	float yellowScore = 0;
	float redScore = 0;


	//휴리스틱은 짜다 말았음.. 
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			if (mBoard[row][col] == mBoard[row][col + 1] &&
				mBoard[row][col] == mBoard[row][col + 2])
			{
				if (mBoard[row][col] == BoardState::Yellow)
				{
					//왼쪽이 열려있는지 조사
					if (col != 0 && mBoard[row][col - 1] == BoardState::Empty)
						yellowScore += 0.05;
					//오른쪽이 열려있는지 조사
					if (col != 4 && mBoard[row][col + 3] == BoardState::Empty)
						yellowScore += 0.05;
				}
				else if (mBoard[row][col] == BoardState::Red)
				{
					float redTemp = 0;
					//왼쪽이 열려있는지 조사
					if (col != 0 && mBoard[row][col - 1] == BoardState::Empty)
						redScore += 0.05;
					//오른쪽이 열려있는지 조사
					if (col != 4 && mBoard[row][col + 3] == BoardState::Empty)
						redScore += 0.05;
				}
			}
		}
	}
	


	return redScore - yellowScore;
}

bool TryPlayerMove(BoardState* state, int column)
{
	// Find the first row in that column that's available
	// (if any)
	for (int row = 5; row >= 0; row--)
	{
		if (state->mBoard[row][column] == BoardState::Empty)
		{
			state->mBoard[row][column] = BoardState::Yellow;
			return true;
		}
	}

	return false;
}

void CPUMove(BoardState* state)
{
	// For now, this just randomly picks one of the possible moves
	
	GTNode* root = new GTNode(state);
	

	GTNode* res = AlphaBetaDecide(root, 4);


	
	*state = *res->mState;

	delete root;
}

float AlphaBetaMax( GTNode* node, int depth, float alpha, float beta)
{
	// If this is a leaf, return score
	if (depth == 0 || node->mState->IsTerminal())
	{
		return node->mState->GetScore();
	}

	float maxValue = -std::numeric_limits<float>::infinity();

	//한 깊이 아래의 트리를 Real-Time 으로 생성한다.
	std::vector<BoardState*> moves = node->mState->GetPossibleMoves(BoardState::Red);

	for (int i = 0; i < moves.size(); i++)
	{
		GTNode* child = new GTNode(moves[i]);
		
		node->mChildren.push_back(child);
	}


	// Find the subtree with the maximum value
	for ( GTNode* child : node->mChildren)
	{
		maxValue = std::max(maxValue, AlphaBetaMin(child, depth - 1, alpha, beta));
		if (maxValue >= beta)
		{
			return maxValue; // Beta prune
		}
		alpha = std::max(maxValue, alpha);
	}
	return maxValue;
}

float AlphaBetaMin(GTNode* node, int depth, float alpha, float beta)
{
	// If this is a leaf, return score
	if (depth == 0 || node->mState->IsTerminal())
	{
		return node->mState->GetScore();
	}

	float minValue = std::numeric_limits<float>::infinity();

	//한 깊이 아래의 트리를 Real-Time 으로 생성한다.
	std::vector<BoardState*> moves = node->mState->GetPossibleMoves(BoardState::Yellow);

	for (int i = 0; i < moves.size(); i++)
	{
		GTNode* child = new GTNode(moves[i]);
		
		node->mChildren.push_back(child);
	}

	// Find the subtree with the minimum value
	for (GTNode* child : node->mChildren)
	{
		minValue = std::min(minValue, AlphaBetaMax(child,depth - 1, alpha, beta));
		if (minValue <= alpha)
		{
			return minValue; // Alpha prune
		}
		beta = std::min(minValue, beta);
	}
	return minValue;
}

GTNode* AlphaBetaDecide( GTNode* root, int maxDepth)
{
	// Find the subtree with the maximum value, and save the choice
	GTNode* choice = nullptr;
	float maxValue = -std::numeric_limits<float>::infinity();
	float beta = std::numeric_limits<float>::infinity();

	//한 깊이 아래의 트리를 Real-Time 으로 생성한다.
	std::vector<BoardState*> moves = root->mState->GetPossibleMoves(BoardState::Red);

	for (int i = 0; i < moves.size(); i++)
	{
		GTNode* child = new GTNode(moves[i]);

		root->mChildren.push_back(child);
	}

	for (GTNode* child : root->mChildren)
	{
		float v = AlphaBetaMin(child, maxDepth - 1,maxValue, beta);
		if (v > maxValue)
		{
			maxValue = v;
			choice = child;
		}
	}
	return choice;
}