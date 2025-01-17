#pragma once
#include "Libraries.h"
using namespace std;

class Piece {
protected:
	bool isWhite;
public:
	Piece();

	Piece(bool isWhite);
	
	bool getIsWhite();

	virtual char getLetter() = 0;

	virtual vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j) = 0;
};

class Pawn : public Piece {
public:
	Pawn(bool isWhite);

	char getLetter();

	vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j);
};

class Knight : public Piece {
public:
	Knight(bool isWhite);

	char getLetter();

	vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j);
};

class Bishop : public Piece {
public:
	Bishop(bool isWhite);

	char getLetter();

	vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j);
};

class Rook : public Piece {
private:
	bool isMoved;

public:
	Rook(bool isWhite);

	bool getIsMoved();

	void setIsMoved();

	char getLetter();

	vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j);
};

class Queen : public Piece {
public:
	Queen(bool isWhite);

	char getLetter();

	vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j);
};

class King : public Piece {
private:
	bool isMoved;

public:
	King(bool isWhite);

	bool getIsMoved();

	void setIsMoved();

	char getLetter();

	vector<vector<int>> obtainLegalMoves(vector<vector<Piece*>> board, int i, int j);
};