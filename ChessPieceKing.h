///
/// @file		ChessPieceKing.h
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		King piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#ifndef _CHESS_PIECE_KING_H_
#define _CHESS_PIECE_KING_H_

#include "ChessPiece.h"

/// @brief		King piece class (derived from CChessPiece class)
class CChessPieceKing : public CChessPiece
{
public:
	explicit CChessPieceKing(const char color, const char name, \
		const char col, const char row)
		: CChessPiece(color, name, col, row) {}
	virtual ~CChessPieceKing() {}

	virtual std::vector<std::pair<int, int>> GetPossiblePos();

private:
	/// non construction-copyable
	CChessPieceKing(const CChessPieceKing&);

	/// non copyable
	const CChessPieceKing& operator=(const CChessPieceKing&);
};

#endif // _CHESS_PIECE_KING_H_
