///
/// @file		ChessPiecePawn.h
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		Pawn piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#ifndef _CHESS_PIECE_PAWN_H_
#define _CHESS_PIECE_PAWN_H_

#include "ChessPiece.h"

/// @brief		Pawn piece class (derived from CChessPiece class)
class CChessPiecePawn : public CChessPiece
{
public:
	explicit CChessPiecePawn(const char color, const char name, \
		const char col, const char row)
		: CChessPiece(color, name, col, row) {}
	virtual ~CChessPiecePawn() {}

	virtual std::vector<std::pair<int, int>> GetPossiblePos();

private:
	/// non construction-copyable
	CChessPiecePawn(const CChessPiecePawn&);

	/// non copyable
	const CChessPiecePawn& operator=(const CChessPiecePawn&);
};

#endif // _CHESS_PIECE_PAWN_H_

