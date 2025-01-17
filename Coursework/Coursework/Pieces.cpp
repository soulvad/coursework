#include "Pieces.h"

Piece::Piece() {}

Piece::Piece(bool isWhite) {
	this->isWhite = isWhite;
}

bool Piece::getIsWhite() {
	return isWhite;
}

// pawn

Pawn::Pawn(bool isWhite) {
	this->isWhite = isWhite;
}

char Pawn::getLetter() {
	return 'p';
}

vector<vector<int>> Pawn::obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) {
	vector<vector<int>> legal_moves;
	if (board[i][j]->getIsWhite()) {
		if (i == 1 && board[i + 2][j] == nullptr && board[i + 1][j] == nullptr)
			legal_moves.push_back({ i + 2, j });
		if (i != 7 && board[i + 1][j] == nullptr)
			legal_moves.push_back({ i + 1, j });
		if (j != 0 && board[i + 1][j - 1] != nullptr && !board[i + 1][j - 1]->getIsWhite())
			legal_moves.push_back({ i + 1, j - 1 });
		if (j != 7 && board[i + 1][j + 1] != nullptr && !board[i + 1][j + 1]->getIsWhite())
			legal_moves.push_back({ i + 1, j + 1 });
	}
	else {
		if (i == 6 && board[i - 2][j] == nullptr && board[i - 1][j] == nullptr)
			legal_moves.push_back({ i - 2, j });
		if (i != 0 && board[i - 1][j] == nullptr)
			legal_moves.push_back({ i - 1, j });
		if (j != 0 && board[i - 1][j - 1] != nullptr && board[i - 1][j - 1]->getIsWhite())
			legal_moves.push_back({ i - 1, j - 1 });
		if (j != 7 && board[i - 1][j + 1] != nullptr && board[i - 1][j + 1]->getIsWhite())
			legal_moves.push_back({ i - 1, j + 1 });
	}
	return legal_moves;
}

// knight

Knight::Knight(bool isWhite) {
	this->isWhite = isWhite;
}

char Knight::getLetter() {
	return 'n';
}

vector<vector<int>> Knight::obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) {
	vector<vector<int>> legal_moves;
	int r[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
	int c[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };
	for (int k = 0; k < 8; k++) {
		if (i + r[k] > 7 || i + r[k] < 0)
			continue;
		if (j + c[k] > 7 || j + c[k] < 0)
			continue;
		if (board[i + r[k]][j + c[k]] != nullptr && board[i + r[k]][j + c[k]]->getIsWhite() == board[i][j]->getIsWhite())
			continue;
		legal_moves.push_back({ i + r[k], j + c[k] });
	}
	return legal_moves;
}

// bishop

Bishop::Bishop(bool isWhite) {
	this->isWhite = isWhite;
}

char Bishop::getLetter() {
	return 'b';
}

vector<vector<int>> Bishop::obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) {
	vector<vector<int>> legal_moves;
	int r = i + 1, c = j + 1;
	while (r <= 7 && c <= 7) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r++;
		c++;
	}
	r = i - 1, c = j - 1;
	while (r >= 0 && c >= 0) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r--;
		c--;
	}
	r = i + 1, c = j - 1;
	while (r <= 7 && c >= 0) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r++;
		c--;
	}
	r = i - 1, c = j + 1;
	while (r >= 0 && c <= 7) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r--;
		c++;
	}
	return legal_moves;
}

// rook

Rook::Rook(bool isWhite) {
	this->isWhite = isWhite;
	this->isMoved = false;
}

bool Rook::getIsMoved() {
	return isMoved;
}

void Rook::setIsMoved() {
	isMoved = true;
}

char Rook::getLetter() {
	return 'r';
}

vector<vector<int>> Rook::obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) {
	vector<vector<int>> legal_moves;
	int r = i - 1;
	while (r >= 0) {
		if (board[r][j] == nullptr)
			legal_moves.push_back({ r, j });
		else if (board[r][j]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, j });
			break;
		}
		r--;
	}
	r = i + 1;
	while (r <= 7) {
		if (board[r][j] == nullptr)
			legal_moves.push_back({ r, j });
		else if (board[r][j]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else if (board[r][j]->getIsWhite() != board[i][j]->getIsWhite()) {
			legal_moves.push_back({ r, j });
			break;
		}
		r++;
	}
	int c = j - 1;
	while (c >= 0) {
		if (board[i][c] == nullptr)
			legal_moves.push_back({ i, c });
		else if (board[i][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else if (board[i][c]->getIsWhite() != board[i][j]->getIsWhite()) {
			legal_moves.push_back({ i, c });
			break;
		}
		c--;
	}
	c = j + 1;
	while (c <= 7) {
		if (board[i][c] == nullptr)
			legal_moves.push_back({ i, c });
		else if (board[i][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else if (board[i][c]->getIsWhite() != board[i][j]->getIsWhite()) {
			legal_moves.push_back({ i, c });
			break;
		}
		c++;
	}
	return legal_moves;
}

// queen

Queen::Queen(bool isWhite) {
	this->isWhite = isWhite;
}

char Queen::getLetter() {
	return 'q';
}

vector<vector<int>> Queen::obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) {
	vector<vector<int>> legal_moves;
	int r = i - 1;
	while (r >= 0) {
		if (board[r][j] == nullptr)
			legal_moves.push_back({ r, j });
		else if (board[r][j]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, j });
			break;
		}
		r--;
	}
	r = i + 1;
	while (r <= 7) {
		if (board[r][j] == nullptr)
			legal_moves.push_back({ r, j });
		else if (board[r][j]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else if (board[r][j]->getIsWhite() != board[i][j]->getIsWhite()) {
			legal_moves.push_back({ r, j });
			break;
		}
		r++;
	}
	int c = j - 1;
	while (c >= 0) {
		if (board[i][c] == nullptr)
			legal_moves.push_back({ i, c });
		else if (board[i][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else if (board[i][c]->getIsWhite() != board[i][j]->getIsWhite()) {
			legal_moves.push_back({ i, c });
			break;
		}
		c--;
	}
	c = j + 1;
	while (c <= 7) {
		if (board[i][c] == nullptr)
			legal_moves.push_back({ i, c });
		else if (board[i][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else if (board[i][c]->getIsWhite() != board[i][j]->getIsWhite()) {
			legal_moves.push_back({ i, c });
			break;
		}
		c++;
	}
	r = i + 1, c = j + 1;
	while (r <= 7 && c <= 7) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r++;
		c++;
	}
	r = i - 1, c = j - 1;
	while (r >= 0 && c >= 0) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r--;
		c--;
	}
	r = i + 1, c = j - 1;
	while (r <= 7 && c >= 0) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r++;
		c--;
	}
	r = i - 1, c = j + 1;
	while (r >= 0 && c <= 7) {
		if (board[r][c] == nullptr)
			legal_moves.push_back({ r, c });
		else if (board[r][c]->getIsWhite() == board[i][j]->getIsWhite())
			break;
		else {
			legal_moves.push_back({ r, c });
			break;
		}
		r--;
		c++;
	}
	return legal_moves;
}

// king

King::King(bool isWhite) {
	this->isWhite = isWhite;
	this->isMoved = false;
}

bool King::getIsMoved() {
	return isMoved;
}

void King::setIsMoved() {
	isMoved = true;
}

char King::getLetter() {
	return 'k';
}

vector<vector<int>> King::obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) {
	vector<vector<int>> legal_moves;
	int r[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
	int c[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	for (int k = 0; k < 8; k++) {
		if (i + r[k] > 7 || i + r[k] < 0)
			continue;
		if (j + c[k] > 7 || j + c[k] < 0)
			continue;
		if (board[i + r[k]][j + c[k]] != nullptr && board[i + r[k]][j + c[k]]->getIsWhite() == board[i][j]->getIsWhite())
			continue;
		legal_moves.push_back({ i + r[k], j + c[k] });
	}
	return legal_moves;
}