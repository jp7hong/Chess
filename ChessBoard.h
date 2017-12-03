///
/// @file		ChessBoard.h
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 15, 2017
/// @version	1.0
/// @brief		Chessboard class (singleton pattern)
/// @remark		Tab size: 4
///

#ifndef _CHESS_BOARD_H_
#define _CHESS_BOARD_H_

#include <vector>		// std::vector
#include <utility>		// std::pair, std::make_pair

#include "Singleton.h"
#include "ChessPiece.h"

/// length of column and row
#ifndef BOARD_LEN
#define BOARD_LEN	(8)
#endif

/// @brief		Chessboard class (singleton pattern)
class CChessBoard : public TSingleton<CChessBoard>
{
public:
	enum EPieceColor { NO_COLOR = '.', WHITE = 'W', BLACK = 'B' };
	enum EDecision { CONTINUE = 0, WIN_W, WIN_B, DRAW };

public:
	explicit CChessBoard();
	virtual ~CChessBoard();

	void Run();

	char GetTurnColor() { return m_cTurnColor; }
	char GetPosColor(const int x, const int y) { return m_arrSquare[y][x].cColor; }
	std::pair<char, char> GetSrcIdx() { return m_pairSrcIdx; }
	std::pair<char, char> GetDstIdx() { return m_pairDstIdx; }
	std::pair<int, int> GetSrcPos()
	{
		return std::make_pair<int, int>( \
			int(m_pairSrcIdx.first - 'A'), int(m_pairSrcIdx.second - '1'));
	}
	std::pair<int, int> GetDstPos()
	{
		return std::make_pair<int, int>( \
			int(m_pairDstIdx.first - 'A'), int(m_pairDstIdx.second - '1'));
	}
	std::vector<std::pair<int, int>> GetTroopsPos( \
		const int color, \
		const std::pair<int, int>& pairPosIgnore = std::pair<int, int>(-1, -1));

private:
	void Init();
	void Quit();
	bool GetInput();
	bool CheckMoveRule();
	void PostProcess();
	bool ShowOutput();
	int  MakeDecision();
	void ShowBoard();
	void Update();
	bool IsInCheck();

private:
	/// non construction-copyable
	CChessBoard(const CChessBoard&);

	/// non copyable
	const CChessBoard& operator=(const CChessBoard&);

private:
	typedef struct _tagSBoardGrid
	{
		char cColor;						///< color of a piece ('W' or 'B')
		char cName;							///< name of a piece ('K', 'R', 'B', or 'P')
		CChessPiece *pChessPiece;			///< pointer to access a chess piece
	} SBoardGrid;

	const int m_nPieces = 13;				///< the number of pieces of a team
	char m_cTurnColor = WHITE;				///< current turn (WHITE('W') or BLACK('B'))
	std::vector<CChessPiece*> m_vWhite;		///< vector to hold white pieces
	std::vector<CChessPiece*> m_vBlack;		///< vector to hold black pieces
	SBoardGrid m_arrSquare[BOARD_LEN][BOARD_LEN];	///< matrix to show the chessboard
	std::pair<char, char> m_pairSrcIdx;		///< user's source index (eg. "A2")
	std::pair<char, char> m_pairDstIdx;		///< user's destination index (eg. "A3")
};

#endif // _CHESS_BOARD_H_
