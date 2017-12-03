///
/// @file		ChessPieceBish.h
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		Bishop piece class (derived from CChessPiece class)
/// @remark		Tab size: 4
///

#ifndef _CHESS_PIECE_BISH_H_
#define _CHESS_PIECE_BISH_H_

#include "ChessPiece.h"

/// @brief		Bishop piece class (derived from CChessPiece class)
class CChessPieceBish : public CChessPiece
{
public:
	explicit CChessPieceBish(const char color, const char name, \
		const char col, const char row)
		: CChessPiece(color, name, col, row) {}
	virtual ~CChessPieceBish() {}

	virtual std::vector<std::pair<int, int>> GetPossiblePos();

private:
	/// non construction-copyable
	CChessPieceBish(const CChessPieceBish&);

	/// non copyable
	const CChessPieceBish& operator=(const CChessPieceBish&);
};

#endif // _CHESS_PIECE_BISH_H_
