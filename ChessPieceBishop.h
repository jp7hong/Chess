// ChessPieceBishop.h

#ifndef _CHESS_PIECE_BISHOP_H_
#define _CHESS_PIECE_BISHOP_H_

#include "ChessPiece.h"

class CChessPieceBishop : public CChessPiece
{
public:
	explicit CChessPieceBishop() {}
	virtual ~CChessPieceBishop() {}

	virtual std::vector<SPos> CChessPieceBishop() {}

private:
	/// non construction-copyable
	CChessPieceBishop(const CChessPieceBishop&);

	/// non copyable
	const CChessPieceBishop& operator=(const CChessPieceBishop&);

};

#endif // _CHESS_PIECE_BISHOP_H_
