///
/// @file		ChessPiecePawn.cpp
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		Pawn piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#include "ChessPiecePawn.h"
#include "ChessBoard.h"		// CChessBoard

/// @brief		get possible positions of this piece
/// @param		N/A
/// @return		position vector which contains possible positions
std::vector<std::pair<int, int>>
CChessPiecePawn::GetPossiblePos()
{
	std::vector<std::pair<int, int>> vRet;

	// my position
	int nSrcX = GetPos().first;
	int nSrcY = GetPos().second;

	// check whether it's within normal range
	assert(IS_POS_WITHIN_RANGE(nSrcX, nSrcY));

	// (a) A pawn moves straight forward one square where there's no piece.
	// (b) A pawn cannot move backward or lateral side.
	// (c) A pawn can capture an opponent's piece on a square diagonally.
	// (d) On first move, a pawn can advance two square along the same file,
	//     provided both square are unoccupied.
	// *** In this program, it doesn't consider the rule (d) and other exceptional rules.

	// rule (a): can move straight forward one square where there's no piece.
	// rule (b): cannot move backward or lateral side.
	std::vector<std::pair<int, int>> vPairRelPosWhite =
	{									//  +1  (2) | (1) | (3)
		std::make_pair(0, +1),	// (1)	//     -----+-----+-----
		std::make_pair(-1, +1),	// (2)	// y 0   -  | [P] |  -
		std::make_pair(+1, +1),	// (3)	//     -----+-----+-----
	};									//   x: -1     0    +1
	
	std::vector<std::pair<int, int>> vPairRelPosBlack =
	{									//     -----+-----+-----
		std::make_pair(0, -1),	// (1)	// y 0   -  | [P] |  -
		std::make_pair(-1, -1),	// (2)	//     -----+-----+-----
		std::make_pair(+1, -1),	// (3)	//  -1  (2) | (1) | (3)
	};									//   x: -1     0    +1

	// set pointer according to the current turn color
	std::vector<std::pair<int, int>> *pVecPairRelPos = \
		(CChessBoard::GetInstance()->GetTurnColor() == \
		CChessBoard::EPieceColor::WHITE) ? \
		&vPairRelPosWhite : &vPairRelPosBlack;

	// check move rules for a pawn
	for (size_t i = 0; i < pVecPairRelPos->size(); i++)
	{
		// candidate position
		int nCndX = nSrcX + pVecPairRelPos->at(i).first;
		int nCndY = nSrcY + pVecPairRelPos->at(i).second;

		// if candidate position is out of range, just skip
		if (!IS_POS_WITHIN_RANGE(nCndX, nCndY))
			continue;

		// get a color at the candidate position
		char cCndColor = CChessBoard::GetInstance()->GetPosColor(nCndX, nCndY);

		// straight forward direction:
		// can move only when there's no piece. (rule (a) and (b))
		if (i == 0)
		{
			// if candidate position is not occupied, then add to possible position
			if (cCndColor == CChessBoard::EPieceColor::NO_COLOR)
				vRet.push_back(std::make_pair(nCndX, nCndY));
		}
		// diagonal direction: can move only when there's a enemy (rule (c))
		else if (
			(cCndColor == CChessBoard::EPieceColor::WHITE &&
			GetColor() == CChessBoard::EPieceColor::BLACK) ||
			(cCndColor == CChessBoard::EPieceColor::BLACK &&
			GetColor() == CChessBoard::EPieceColor::WHITE))
		{
			// add to possible position
			vRet.push_back(std::make_pair(nCndX, nCndY));
		}
	}

	return vRet;
}
