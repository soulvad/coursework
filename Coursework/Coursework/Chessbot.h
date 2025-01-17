#include "Libraries.h"
#include <map>
#include <memory>
#include <limits>
#include "Game.h"

using namespace std;

struct MoveNode {
    int from_row, from_col, to_row, to_col;
    double evaluation;
    map<vector<int>, unique_ptr<MoveNode>> children;

    MoveNode(int fr, int fc, int tr, int tc, double eval)
        : from_row(fr), from_col(fc), to_row(tr), to_col(tc), evaluation(eval) {}
};

class ChessBot {
private:
    unique_ptr<MoveNode> root;
    MoveNode* current_node;

    const map<char, double> piece_values = {
        {'p', 0.5},
        {'n', 3.0},
        {'b', 3.0},
        {'r', 5.0},
        {'q', 10.0},
        {'k', 1000.0}
    };

    double getMaterialBalance(Game& game);

    double evaluateExplosion(Game& game, vector<int>& move);

    double evaluatePosition(Game& game, vector<int>& move);

    double alphaBeta(Game& game, MoveNode* node, int depth, double alpha, double beta, bool maximizingPlayer);

public:
    ChessBot();

    vector<int> findBestMove(Game& game, MoveNode* current_node, int depth, bool isWhite);

    void updateTreeAfterPlayerMove(vector<int> player_move);
};
