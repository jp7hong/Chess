///
/// @file		ChessBoard.cpp
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		Chessboard class (singleton pattern)
/// @remark		Tab size: 4
///

#include <iostream>		// std::cout
#include <string>		// std::getline
#include <algorithm>	// std::for_each
#include <cctype>		// toupper, isalpha, isdigit
#include <cassert>		// assert

#include "ChessBoard.h"
#include "ChessPieceKing.h"
#include "ChessPieceRook.h"
#include "ChessPieceBish.h"
#include "ChessPiecePawn.h"

/// @brief		constructor
/// @param		N/A
/// @return		N/A
CChessBoard::CChessBoard()
{
	// m_nPieces = 13 (King 1, Rook 2, Bishop 2, and Pawn 8)
	m_vWhite.reserve(m_nPieces);
	m_vBlack.reserve(m_nPieces);

	// allocate memory and initialize color and position of each pieces
	Init();
}

/// @brief		destructor
/// @param		N/A
/// @return		N/A
CChessBoard::~CChessBoard()
{
	// deallocate memory for all pieces
	Quit();
}

/// @brief		initialize color and position of each pieces
/// @param		N/A
/// @return		void
void
CChessBoard::Init()
{
	// CChessPieceXXXX arguments:
	// argument 1: 'W'(white) or 'B'(black)
	// argument 2: 'K'(king), 'R'(rook), 'B'(bishop), or 'P'(pawn)
	// argument 3: column index ['A'..'H'] (it's a character, not a int)
	// argument 4: row index ['1'..'8'] (it's a character, not a int)

	// make instances for white pieces
	m_vWhite.push_back(new CChessPieceKing('W', 'K', 'E', '1'));
	m_vWhite.push_back(new CChessPieceRook('W', 'R', 'A', '1'));
	m_vWhite.push_back(new CChessPieceRook('W', 'R', 'H', '1'));
	m_vWhite.push_back(new CChessPieceBish('W', 'B', 'C', '1'));
	m_vWhite.push_back(new CChessPieceBish('W', 'B', 'F', '1'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'A', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'B', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'C', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'D', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'E', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'F', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'G', '2'));
	m_vWhite.push_back(new CChessPiecePawn('W', 'P', 'H', '2'));

	// make instances for black pieces
	m_vBlack.push_back(new CChessPieceKing('B', 'K', 'E', '8'));
	m_vBlack.push_back(new CChessPieceRook('B', 'R', 'A', '8'));
	m_vBlack.push_back(new CChessPieceRook('B', 'R', 'H', '8'));
	m_vBlack.push_back(new CChessPieceBish('B', 'B', 'C', '8'));
	m_vBlack.push_back(new CChessPieceBish('B', 'B', 'F', '8'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'A', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'B', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'C', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'D', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'E', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'F', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'G', '7'));
	m_vBlack.push_back(new CChessPiecePawn('B', 'P', 'H', '7'));

	// update the board status to show
	Update();
}

/// @brief		deallocate memory for all pieces
/// @param		N/A
/// @return		void
void
CChessBoard::Quit()
{
	// deallocate memory for white/black pieces
	for (int i = 0; i < m_nPieces; i++)
	{
		delete m_vWhite[i];
		delete m_vBlack[i];
	}

	m_vWhite.clear();
	m_vBlack.clear();
}

/// @brief		main interface function for main.cpp
/// @param		N/A
/// @return		void
void CChessBoard::Run()
{
	// show board at the beginning
	ShowOutput();

	while (1)
	{
		// get user's input
		GetInput();

		// change turn if user's command is valid
		if (CheckMoveRule() == true)
		{
			// update position of a piece and remove a enemy if it captured
			PostProcess();

			// change turn
			m_cTurnColor = (m_cTurnColor == 'W') ? 'B' : 'W';
		}

		// show board or decision result (return false if the game is terminated)
		if (ShowOutput() == false)
			break;
	}
}

/// @brief		get positions of given colored troops (w/o including 'pairPosIgnore')
/// @param		color [in] CChessBoard::WHITE or CChessBoard::BLACK
/// @param		pairPosIgnore [in] position which is not to be included
/// @return		position vector of given colored troops (w/o including 'pairPosIgnore')
/// @remark		don't use 'pairPosIgnore' if you don't need to ignore specific position
std::vector<std::pair<int, int>>
CChessBoard::GetTroopsPos(const int color, \
const std::pair<int, int>& pairPosIgnore)
{
	std::vector<std::pair<int, int>> vRet;
	std::vector<CChessPiece*> *p = 0;

	assert(color == CChessBoard::WHITE || color == CChessBoard::BLACK);

	// set a vector pointer to a proper colored troops
	p = (color == WHITE) ? &m_vWhite : &m_vBlack;

	std::vector<CChessPiece*>::iterator it;
	for (it = p->begin(); it != p->end(); ++it)
	{
		// if it is a live piece
		if ((*it)->IsExist())
		{
			int x = (*it)->GetPos().first;
			int y = (*it)->GetPos().second;

			// add only if it is not same position
			if (std::make_pair(x, y) != pairPosIgnore)
				vRet.push_back(std::make_pair(x, y));
		}
	}

	return vRet;
}

/// @brief		get a user's input
/// @param		N/A
/// @return		true if inputted col/row index range is valid, otherwise false
bool
CChessBoard::GetInput()
{
	std::string s;

	std::cout << std::endl;
	std::cout << "==== BEGIN GAME INPUT ====" << std::endl;
	std::getline(std::cin, s);
	std::cout << "====  END GAME INPUT  ====" << std::endl << std::endl;

	// get a character from inputted string
	char col_curr = s[0];
	char row_curr = s[1];
	char col_next = s[3];
	char row_next = s[4];

	// check alphabet, number, and comma (eg. "C3,D4")
	if (!isalpha(int(s[0])) ||	// 'C'
		!isdigit(int(s[1])) ||	// '3'
		!isalpha(int(s[3])) ||	// 'D'
		!isdigit(int(s[4])) ||	// '4'
		s[2] != ',')			// ','
		return false;

	// convert to upper case (eg. "C3,D4")
	col_curr = char(toupper(s[0]));		// 'C'
	col_next = char(toupper(s[3]));		// 'D'

	// column range check (available range: ['A'..'H'])
	if (col_curr < 'A' || col_curr > 'H' || col_next < 'A' || col_next > 'H')
		return false;

	// row range check (available range: ['1'..'8'])
	if (row_curr < '1' || row_curr > '8' || row_next < '1' || row_next > '8')
		return false;

	// check piece color, existence of the given current position
	int x = col_curr - 'A';
	int y = row_curr - '1';
	if (m_arrSquare[y][x].cColor != m_cTurnColor)
		return false;

	// set current/desired positions
	m_pairSrcIdx = std::make_pair(col_curr, row_curr);
	m_pairDstIdx = std::make_pair(col_next, row_next);

	return true;
}

/// @brief		check whether a user entered the move rule
/// @param		N/A
/// @return		true if the move rule is satisfied, otherwise false
bool
CChessBoard::CheckMoveRule()
{
	// pointer of chess piece of user's source index
	CChessPiece* pChessPiece = \
		m_arrSquare[GetSrcPos().second][GetSrcPos().first].pChessPiece;

	// if there's no piece at the source position of user's input
	if (!pChessPiece)
		return false;

	// check whether piece color is matched
	if (m_cTurnColor != pChessPiece->GetColor())
		return false;

	// get possible positions of user's source piece position
	std::vector<std::pair<int, int>> vPairPossiblePos;
	vPairPossiblePos = pChessPiece->GetPossiblePos();
	std::vector<std::pair<int, int>>::iterator it;
	for (it = vPairPossiblePos.begin(); it != vPairPossiblePos.end(); ++it)
	{
		// if a user's desired position is matched according to the move rule
		if (GetDstPos() == (*it))
		{
			return true;
		}
	}

	return false;
}

/// @brief		remove a enemy if it's captured and move player's piece
/// @param		N/A
/// @return		void
/// @remark		this function must be called when user's move command is valid
void
CChessBoard::PostProcess()
{
	int srcPosX = GetSrcPos().first;
	int srcPosY = GetSrcPos().second;
	int dstPosX = GetDstPos().first;
	int dstPosY = GetDstPos().second;
	char cEnemyColor = (m_cTurnColor == 'W') ? 'B' : 'W';

	// if there's a enemy at the desired position, remove it
	if (m_arrSquare[dstPosY][dstPosX].cColor == cEnemyColor)
		m_arrSquare[dstPosY][dstPosX].pChessPiece->Remove();

	// move a piece to the user's desired position
	m_arrSquare[srcPosY][srcPosX].pChessPiece->SetPos(dstPosX, dstPosY);
}

/// @brief		show game output (display board or result)
/// @param		N/A
/// @return		false if the game is terminated, otherwise true
bool
CChessBoard::ShowOutput()
{
	bool bRet = false;

	std::cout << "==== BEGIN GAME OUTPUT ====" << std::endl;

	switch (MakeDecision())
	{
	case WIN_W:
		std::cout << "Winner: W" << std::endl;
		break;

	case WIN_B:
		std::cout << "Winner: B" << std::endl;
		break;

	case DRAW:
		std::cout << "Winner: D" << std::endl;
		break;

	case CONTINUE:
	default:
		ShowBoard();
		bRet = true;	// the game should be continued
	}

	std::cout << "====  END GAME OUTPUT  ====" << std::endl;

	return bRet;
}

/// @brief		make a decision
/// @param		N/A
/// @return		NONE (no dicision), WIN_W (white win), WIN_B (black win), or DRAW
int
CChessBoard::MakeDecision()
{
	// check whether two kings are alive
	assert(m_vWhite[0]->GetName() == 'K');
	assert(m_vBlack[0]->GetName() == 'K');

	// (1) if the white king is not exist, then black wins.
	if (!m_vWhite[0]->IsExist())
		return WIN_B;

	// (2) if the black king is not exist, then white wins.
	if (!m_vBlack[0]->IsExist())
		return WIN_W;

	////////////////////////////////////////////////////////////////////////////
	// (3) check if the 'stalemate' has happened

	// set the troops pointers according to the turn
	std::vector<CChessPiece*> *pTroops[2] = { 0, 0 };
	pTroops[0] = (m_cTurnColor == WHITE) ? &m_vWhite : &m_vBlack;
	pTroops[1] = (m_cTurnColor == WHITE) ? &m_vBlack : &m_vWhite;

	// the pTroops[0] king's possible position
	std::vector<std::pair<int, int>> vPairPosKingPossiblePos = \
		pTroops[0]->at(0)->GetPossiblePos();

	// possible positions of all pTroops[1] pieces
	std::vector<std::pair<int, int>> vPairPosEnemiesPossiblePos;
	for (size_t i = 0; i < pTroops[1]->size(); i++)
	{
		if (!pTroops[1]->at(i)->IsExist())
			continue;

		// possible positions of a pTroops[1] piece
		std::vector<std::pair<int, int>> vPairPosEnemyPossiblePos = \
			pTroops[1]->at(i)->GetPossiblePos();

		// possible positions of all pTroops[1] pieces
		vPairPosEnemiesPossiblePos.insert(vPairPosEnemiesPossiblePos.end(), \
			vPairPosEnemyPossiblePos.begin(), vPairPosEnemyPossiblePos.end());
	}

	// check if the king can avoid
	bool bKingCanMove = true;
	for (size_t i = 0; i < vPairPosKingPossiblePos.size(); i++)
	{
		// compare with each enemy's possible positions
		for (size_t j = 0; j < vPairPosEnemiesPossiblePos.size(); j++)
		{
			// if this square is a dangerous square
			if (vPairPosKingPossiblePos[i] == vPairPosEnemiesPossiblePos[j])
			{
				bKingCanMove = false;
				break;
			}
		}

		if (bKingCanMove)
			return CONTINUE;
	}

	// if pTroop[0] king cannot move, then check if other pieces can move
	if (!bKingCanMove)
	{
		for (size_t i = 1; i < pTroops[0]->size(); i++)
		{
			std::vector<std::pair<int, int>> vPairPos = \
				pTroops[0]->at(i)->GetPossiblePos();

			// if it is possible to move at least one piece, it's not 'statemate'
			if (vPairPos.size() > 0)
				return CONTINUE;
		}
	}

	////////////////////////////////////////////////////////////////////////////

	return DRAW;
}

/// @brief		update chessboard state and show the board
/// @param		N/A
/// @return		void
void
CChessBoard::ShowBoard()
{
	// update the board status to show
	Update();

	std::cout << "  -----------------------" << std::endl;

	for (int y = BOARD_LEN - 1; y >= 0; y--)
	{
		std::cout << y + 1 << "|";

		for (int x = 0; x < BOARD_LEN; x++)
		{
			std::cout << m_arrSquare[y][x].cColor << m_arrSquare[y][x].cName;

			// don't print rightmost space
			if (x != 7)
				std::cout << " ";
		}

		std::cout << "|" << std::endl;
	}

	std::cout << "  -----------------------" << std::endl;
	std::cout << "  A  B  C  D  E  F  G  H" << std::endl;
	std::cout << "In check: " << (IsInCheck() ? "Y" : "N") << std::endl;
	std::cout << "Next move: " << m_cTurnColor << std::endl;	// add "Next" not to confuse
}

/// @brief		update the chessboard status to show
/// @param		N/A
/// @return		void
void
CChessBoard::Update()
{
	// clear board array to get new position information of pieces
	for (int y = 0; y < BOARD_LEN; y++)
	{
		for (int x = 0; x < BOARD_LEN; x++)
		{
			m_arrSquare[y][x].cColor = '.';
			m_arrSquare[y][x].cName = '.';
			m_arrSquare[y][x].pChessPiece = 0;
		}
	}

	// search live white/black pieces and update chessboard state
	for (size_t i = 0; i < 2; i++)
	{
		std::vector<CChessPiece*> *pTroops = \
			(i == 0) ? &m_vWhite : &m_vBlack;

		std::vector<CChessPiece*>::iterator it;
		for (it = pTroops->begin(); it != pTroops->end(); ++it)
		{
			if ((*it)->IsExist())
			{
				int x = (*it)->GetPos().first;
				int y = (*it)->GetPos().second;

				// set color and name
				m_arrSquare[y][x].cColor = (*it)->GetColor();
				m_arrSquare[y][x].cName = (*it)->GetName();
				m_arrSquare[y][x].pChessPiece = *it;
			}
		}
	}
}

/// @brief		check whether 'In check' state has happened
/// @param		N/A
/// @return		true if 'In check' has happened, otherwise false
bool
CChessBoard::IsInCheck()
{
	// check whether the two kings are alive.
	assert(m_vWhite[0]->GetName() == 'K');
	assert(m_vBlack[0]->GetName() == 'K');

	// Because I don't consider following rules
	// "The king cannot move where it would place itself in check." and
	// "The king cannot capture the opposing king.",
	// so it needs to check 'In check' state for both sides.

	for (size_t i = 0; i < 2; i++)
	{
		// set pointer of friendly/enemy troops
		std::vector<CChessPiece*> *pFriendlyTroops = 0;
		std::vector<CChessPiece*> *pEnemyTroops = 0;
		pFriendlyTroops = (i == 0) ? &m_vWhite : &m_vBlack;
		pEnemyTroops = (i == 0) ? &m_vBlack : &m_vWhite;

		// the king's position to check
		//std::pair<int, int> pairKingPos = pFriendlyTroops[0].at(0)->GetPos();
		std::pair<int, int> pairKingPos = pFriendlyTroops->at(0)->GetPos();

		// check 'In check' possibility
		std::vector<CChessPiece*>::iterator itEnemy = pEnemyTroops->begin();
		for (; itEnemy < pEnemyTroops->end(); ++itEnemy)
		{
			if ((*itEnemy)->IsExist())
			{
				// possible positions where a enemy can move
				std::vector<std::pair<int, int>> vPairEnemyAttackablePos = \
					(*itEnemy)->GetPossiblePos();

				// check whether the king can be caught
				// for each possible position by the enemy
				std::vector<std::pair<int, int>>::iterator it;
				it = vPairEnemyAttackablePos.begin();
				for (; it != vPairEnemyAttackablePos.end(); ++it)
				{
					// if the king's current position is overlapped
					// with a possible position
					if (pairKingPos == *it)
						return true;
				}
			}
		}
	}

	return false;
}
