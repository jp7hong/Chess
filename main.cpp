///
/// @file		main.cpp
/// @author		Junpyo Hong (jp7.hong@gmail.com)
/// @date		Nov. 14, 2017
/// @version	1.0
/// @brief		entry point function of the program
/// @remark		Tab size: 4
///

#include "ChessBoard.h"

/// @brief		entry point function of the program
/// @param		argc [in] the number of arguments being passed into this program
/// @param		argv [in] character array of arguments
/// @return		0 on success
int main(int argc, char *argv[])
{
	CChessBoard::GetInstance()->Run();

	return 0;
}
