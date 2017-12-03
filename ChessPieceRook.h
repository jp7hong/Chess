///
/// @file		ChessPieceRook.h
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		Rook piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#ifndef _CHESS_PIECE_ROOK_H_
#define _CHESS_PIECE_ROOK_H_

#include "ChessPiece.h"

/// @brief		Rook piece class (derived from CChessPiece class)
class CChessPieceRook : public CChessPiece
{
public:
	explicit CChessPieceRook(const char color, const char name, \
		const char col, const char row)
		: CChessPiece(color, name, col, row) {}
	virtual ~CChessPieceRook() {}

	virtual std::vector<std::pair<int, int>> GetPossiblePos();

private:
	/// non construction-copyable
	CChessPieceRook(const CChessPieceRook&);

	/// non copyable
	const CChessPieceRook& operator=(const CChessPieceRook&);
};

#endif // _CHESS_PIECE_ROOK_H_
