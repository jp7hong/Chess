///
/// @file		ChessPieceKing.cpp
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		King piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#include "ChessPieceKing.h"
#include "ChessBoard.h"		// CChessBoard

/// @brief		get possible positions of this piece
/// @param		N/A
/// @return		position vector which contains possible positions
std::vector<std::pair<int, int>>
CChessPieceKing::GetPossiblePos()
{
	std::vector<std::pair<int, int>> vRet;

	// my position
	int nSrcX = GetPos().first;
	int nSrcY = GetPos().second;

	// check whether it's within normal range
	assert(IS_POS_WITHIN_RANGE(nSrcX, nSrcY));

	// (a) The king moves exactly one square horizontally, vertically, or diagonally.
	// (b) The king cannot move where the square is already occupied by a friendly piece.
	// (c) The king captures an enemy piece by moving onto its square.
	// (d) The king cannot move where it would place itself in check.
	// (e) The king cannot capture the opposing king.
	// *** In this program, it doesn't consider the rule (d), (e), and other exceptional rules.

	// rule (a): can move exactly one square horizontally, vertically, or diagonally.
	std::vector<std::pair<int, int>> vPairRelPos =
	{
		std::make_pair( 0, +1),	// (1)	//   +1  (8) | (1) | (2)
		std::make_pair(+1, +1),	// (2)	//      -----+-----+-----
		std::make_pair(+1,  0),	// (3)	// y  0  (7) | [K] | (3)
		std::make_pair(+1, -1),	// (4)	//      -----+-----+-----
		std::make_pair( 0, -1),	// (5)	//   -1  (6) | (5) | (4)
		std::make_pair(-1, -1),	// (6)	//
		std::make_pair(-1,  0),	// (7)	//       -1     0    +1
		std::make_pair(-1, +1),	// (8)	//              x
	};

	// check move rules for the king
	std::vector<std::pair<int, int>>::iterator it;
	for (it = vPairRelPos.begin(); it != vPairRelPos.end(); ++it)
	{
		// candidate position
		int nCndX = nSrcX + it->first;
		int nCndY = nSrcY + it->second;

		// if candidate position is out of range, just skip
		if (!IS_POS_WITHIN_RANGE(nCndX, nCndY))
			continue;

		// get a color at the candidate position
		char cCndColor = CChessBoard::GetInstance()->GetPosColor(nCndX, nCndY);

		// if candidate square is vacant or an enemy, then can move (rule (b) and (c))
		if (cCndColor != GetColor())
		{
			// add to possible position
			vRet.push_back(std::make_pair(nCndX, nCndY));
		}
	}

	return vRet;
}
