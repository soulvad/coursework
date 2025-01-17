#pragma once
#include "Libraries.h"
#include "Pieces.h"
using namespace std;

class Game {
private:
	vector<vector<Piece*>> board;
	string last_move;
	bool isGameOver;

public:
	Game();

	Game(const Game& other);

	const vector<vector<Piece*>>& getBoard();

	bool getIsGameOver();

	void atomicKaboom(int row_from, int col_from, int row_to, int col_to);

	bool isAtomicLegal(int row_from, int col_from, int row_to, int col_to);

	void makeMove(int row_from, int col_from, int row_to, int col_to);

	vector<vector<int>> checkLegalMovesForPiece(int row, int col);

	vector<vector<int>> getAllLegalMoves(bool isWhiteTurn);

	bool isDraw();
};