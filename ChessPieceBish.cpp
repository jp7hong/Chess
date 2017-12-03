///
/// @file		ChessPieceBish.cpp
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		Bishop piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#include "ChessPieceBish.h"
#include "ChessBoard.h"		// CChessBoard

/// @brief		get possible positions of this piece
/// @param		N/A
/// @return		position vector which contains possible positions
std::vector<std::pair<int, int>>
CChessPieceBish::GetPossiblePos()
{
	std::vector<std::pair<int, int>> vRet;

	// my position
	int nSrcX = GetPos().first;
	int nSrcY = GetPos().second;

	// check whether it's within normal range
	assert(IS_POS_WITHIN_RANGE(nSrcX, nSrcY));

	// (a) A bishop moves any number of vacant squares in any diagonal direction.
	// (b) A bishop cannot move where the square is already occupied by a friendly piece.
	// (c) A bishop can capture an enemy piece by moving onto its square.
	// (d) A bishop cannot leap over other pieces.

	// comparing step
	std::vector<std::pair<int, int>> vDeltaXY = \
		{ { -1, -1 }, { -1, +1 }, { +1, -1 }, { +1, +1 } };

	// check move rules for a bishop
	for (size_t i = 0; i < vDeltaXY.size(); i++)
	{
		for (size_t j = 1; j < BOARD_LEN; j++)	// [1..7]
		{
			// rule (a): can move any squares in any diagonal direction
			int nCndX = nSrcX + (vDeltaXY[i].first * j);
			int nCndY = nSrcY + (vDeltaXY[i].second * j);

			// if it is out of range, do not check this direction anymore
			if (!IS_POS_WITHIN_RANGE(nCndX, nCndY))
				break;

			// get a color at the candidate position
			char cCndColor = CChessBoard::GetInstance()->GetPosColor(nCndX, nCndY);

			// rule (a): can move any squares in horiz/vert direction.
			if (cCndColor == CChessBoard::EPieceColor::NO_COLOR)
			{
				// add (nCndX, nCndY) to possible positions
				vRet.push_back(std::make_pair(nCndX, nCndY));
			}
			// rule (b): cannot move to the position of our troops.
			else if (cCndColor == GetColor())	// friendly troops
			{
				// rule (d): cannot leap over other pieces.
				break;
			}
			// rule (c): can capture an enemy piece by moving onto its square.
			else	// enemy
			{
				// add (nCndX, nCndY) to possible positions and break
				vRet.push_back(std::make_pair(nCndX, nCndY));

				// rule (d): cannot leap over other pieces.
				break;
			}
		}
	}

	return vRet;
}
