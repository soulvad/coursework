#include "Game.h"

Game::Game() {
	board.resize(8, vector<Piece*>(8, nullptr));
	// White pieces
	board[0][0] = new Rook(true);
	board[0][1] = new Knight(true);
	board[0][2] = new Bishop(true);
	board[0][3] = new Queen(true);
	board[0][4] = new King(true);
	board[0][5] = new Bishop(true);
	board[0][6] = new Knight(true);
	board[0][7] = new Rook(true);

	for (int j = 0; j < 8; j++) {
		board[1][j] = new Pawn(true);
	}

	// Black pieces
	board[7][0] = new Rook(false);
	board[7][1] = new Knight(false);
	board[7][2] = new Bishop(false);
	board[7][3] = new Queen(false);
	board[7][4] = new King(false);
	board[7][5] = new Bishop(false);
	board[7][6] = new Knight(false);
	board[7][7] = new Rook(false);

	for (int j = 0; j < 8; j++) {
		board[6][j] = new Pawn(false);
	}

	isGameOver = false;
}

Game::Game(const Game& other) {
	board = other.board;
	last_move = other.last_move;
	isGameOver = other.isGameOver;
}

const vector<vector<Piece*>>& Game::getBoard() {
	return board;
}


bool Game::getIsGameOver() {
	return isGameOver;
}

void Game::atomicKaboom(int row_from, int col_from, int row_to, int col_to) {
	bool wouldGameOver = false;
	int r[9] = { 0, 1, 1, 0, -1, -1, -1, 0, 1 };
	int c[9] = { 0, 0, 1, 1, 1, 0, -1, -1, -1 };
	for (int k = 0; k < 9; k++) {
		if (row_to + r[k] > 7 || row_to + r[k] < 0)
			continue;
		if (col_to + c[k] > 7 || col_to + c[k] < 0)
			continue;
		if (King* king = dynamic_cast<King*>(board[row_to + r[k]][col_to + c[k]])) {
			wouldGameOver = true;
			break;
		}
	}
	string winner;
	if (wouldGameOver) {
		if (board[row_from][col_from]->getIsWhite()) {
			winner = "white";
		}
		else {
			winner = "black";
		}
	}
	for (int k = 1; k < 9; k++) {
		if (row_to + r[k] >= 0 && col_to + c[k] >= 0 && row_to + r[k] <= 7 && col_to + c[k] <= 7) {
			if (board[row_to + r[k]][col_to + c[k]] == nullptr) {
				continue;
			}
			else if (Pawn* pawn = dynamic_cast<Pawn*>(board[row_to + r[k]][col_to + c[k]])) {
				continue;
			}
			else
				board[row_to + r[k]][col_to + c[k]] = nullptr;
		}
	}
	board[row_to][col_to] = nullptr;
	board[row_from][col_from] = nullptr;
	if (wouldGameOver) {
		isGameOver = true;
	}
}

bool Game::isAtomicLegal(int row_from, int col_from, int row_to, int col_to) {
	int r[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int c[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	for (int k = 0; k < 8; k++) {
		if (row_to + r[k] > 7 || row_to + r[k] < 0)
			continue;
		if (col_to + c[k] > 7 || col_to + c[k] < 0)
			continue;
		if (King* king = dynamic_cast<King*>(board[row_to + r[k]][col_to + c[k]])) {
			if (king->getIsWhite() == board[row_from][col_from]->getIsWhite()) {
				return false;
			}
		}
	}
	return true;
}

void Game::makeMove(int row_from, int col_from, int row_to, int col_to) {
	last_move = board[row_from][col_from]->getLetter() + to_string(row_from) + to_string(col_from) +
		to_string(row_to) + to_string(col_to);
	if (board[row_to][col_to] == nullptr) {
		if (dynamic_cast<Pawn*>(board[row_from][col_from])) {
			if (abs(row_from - row_to) == 1 && abs(col_from - col_to) == 1) {
				board[row_from][col_to] = nullptr;
				atomicKaboom(row_from, col_from, row_to, col_to);
			}
			else if ((board[row_from][col_from]->getIsWhite() && row_to == 7) ||
				(!board[row_from][col_from]->getIsWhite() && row_to == 0)) {
				board[row_to][col_to] = new Queen(board[row_from][col_from]->getIsWhite());
				board[row_from][col_from] = nullptr;
			}
			else {
				board[row_to][col_to] = board[row_from][col_from];
				board[row_from][col_from] = nullptr;
			}
		}
		else if (King* king = dynamic_cast<King*>(board[row_from][col_from])) {
			if (col_to - col_from == 2) {
				board[row_to][col_to] = board[row_from][col_from];
				board[row_from][col_from] = nullptr;
				board[row_to][5] = board[row_from][7];
				board[row_from][7] = nullptr;
			}
			else if (col_from - col_to == 3) {
				board[row_to][col_to] = board[row_from][col_from];
				board[row_from][col_from] = nullptr;
				board[row_to][2] = board[row_from][0];
				board[row_from][0] = nullptr;
			}
			else {
				board[row_to][col_to] = board[row_from][col_from];
				board[row_from][col_from] = nullptr;
			}
			king->setIsMoved();
		}
		else {
			board[row_to][col_to] = board[row_from][col_from];
			board[row_from][col_from] = nullptr;
		}
	}
	else
		atomicKaboom(row_from, col_from, row_to, col_to);
}

vector<vector<int>> Game::checkLegalMovesForPiece(int row, int col) {
	vector<vector<int>> legal_moves;
	legal_moves = board[row][col]->obtainLegalMoves(board, row, col);
	// En passant
	if (Pawn* pawn = dynamic_cast<Pawn*>(board[row][col])) {
		if (last_move[0] == 'p' && (last_move[2] - '0' == col - 1 || last_move[2] - '0' == col + 1)) {
			if (pawn->getIsWhite()) {
				if (row == 4) {
					if (last_move[1] - '0' == 6 && last_move[3] - '0' == 4) {
						if (last_move[2] - '0' == col - 1)
							legal_moves.push_back({ row + 1, col - 1 });
						else
							legal_moves.push_back({ row + 1, col + 1 });
					}
				}
			}
			else {
				if (row == 3) {
					if (last_move[1] - '0' == 1 && last_move[3] - '0' == 3) {
						if (last_move[2] - '0' == col - 1)
							legal_moves.push_back({ row - 1, col - 1 });
						else
							legal_moves.push_back({ row - 1, col + 1 });
					}
				}
			}
		}
	}
	// Castle
	else if (King* king = dynamic_cast<King*>(board[row][col])) {
		if (king->getIsMoved() == false) {
			if (Rook* rook = dynamic_cast<Rook*>(board[row][0])) {
				if (rook->getIsMoved() == false) {
					if (board[row][1] == nullptr && board[row][2] == nullptr && board[row][3] == nullptr) {
						legal_moves.push_back({ row, 1 });
					}
				}
			}
			if (Rook* rook = dynamic_cast<Rook*>(board[row][7])) {
				if (rook->getIsMoved() == false) {
					if (board[row][5] == nullptr && board[row][6] == nullptr) {
						legal_moves.push_back({ row, 6 });
					}
				}
			}
		}
	}

	for (auto move = legal_moves.begin(); move != legal_moves.end();) {
		if (board[(*move)[0]][(*move)[1]] != nullptr && !isAtomicLegal(row, col, (*move)[0], (*move)[1])) {
			move = legal_moves.erase(move);
		}
		else {
			move++;
		}
	}

	return legal_moves;
}

vector<vector<int>> Game::getAllLegalMoves(bool isWhiteTurn) {
	vector<vector<int>> allLegalMoves;

	for (int row_from = 0; row_from < 8; row_from++) {
		for (int col_from = 0; col_from < 8; col_from++) {
			if (board[row_from][col_from] == nullptr) {
				continue;
			}

			if (board[row_from][col_from]->getIsWhite() != isWhiteTurn) {
				continue;
			}

			vector<vector<int>> legalMoves = checkLegalMovesForPiece(row_from, col_from);

			for (const auto& move : legalMoves) {
				allLegalMoves.push_back({ row_from, col_from, move[0], move[1] });
			}
		}
	}

	return allLegalMoves;
}

bool Game::isDraw() {
	int whitePieces = 0, blackPieces = 0;
	int whiteKingRow = -1, whiteKingCol = -1;
	int blackKingRow = -1, blackKingCol = -1;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece* piece = board[i][j];
			if (piece != nullptr) {
				if (King* king = dynamic_cast<King*>(piece)) {
					if (king->getIsWhite()) {
						whiteKingRow = i;
						whiteKingCol = j;
					}
					else {
						blackKingRow = i;
						blackKingCol = j;
					}
				}
				else {
					piece->getIsWhite() ? whitePieces++ : blackPieces++;
				}
			}
		}
	}

	if (whitePieces == 0 && blackPieces == 0) {
		return true;
	}

	if (abs(whiteKingRow - blackKingRow) <= 1 && abs(whiteKingCol - blackKingCol) <= 1) {
		if ((whitePieces == 0 && blackPieces == 0) ||
			(whitePieces == 0 && abs(whiteKingRow - blackKingRow) <= 1 && abs(whiteKingCol - blackKingCol) <= 1)) {
			return true;
		}
	}

	return false;
}