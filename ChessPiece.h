///
/// @file		ChessPiece.h
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		abstract class for chess piece types (strategy pattern)
/// @remark		Tab size: 4
///

#ifndef _CHESS_PIECE_H_
#define _CHESS_PIECE_H_

#include <utility>		// std::pair
#include <vector>		// std::vector (used at derived class)
#include <cassert>		// assert (used at derived class)
#include <cstddef>		// size_t (used at derived class)

/// length of column and row
#ifndef BOARD_LEN
#define BOARD_LEN	(8)
#endif

/// check if a given position is valid
#define IS_POS_WITHIN_RANGE(x,y) \
	((x) >= 0 && (x) <= BOARD_LEN - 1 && (y) >= 0 && (y) <= BOARD_LEN - 1)

/// @brief		abstract class for chess piece types (strategy pattern)
class CChessPiece
{
public:
	explicit CChessPiece(const int cColor, const char cName, \
		const char col, const char row)
	: m_cColor(cColor)
	, m_cName(cName)
	, m_bExist(true)
	, m_pairPos(std::make_pair(col - 'A', row - '1')) {}
	virtual ~CChessPiece() {}

	char GetColor() { return m_cColor; }
	char GetName() { return m_cName; }
	bool IsExist() { return m_bExist; }
	void Remove() { m_bExist = false; }
	std::pair<int, int> GetPos() { return m_pairPos; }
	void SetPos(const int x, const int y) { m_pairPos = std::make_pair(x, y); }

	virtual std::vector<std::pair<int, int>> GetPossiblePos() = 0;

private:
	/// non construction-copyable
	CChessPiece(const CChessPiece&);

	/// non copyable
	const CChessPiece& operator=(const CChessPiece&);

protected:
	char m_cColor;					///< 'W' or 'B'
	char m_cName;					///< 'K', 'R', 'B', or 'P'
	bool m_bExist;					///< true or false
	std::pair<int, int> m_pairPos;	///< x(col), y(row) (integer!)

};

#endif // _CHESS_PIECE_H_
