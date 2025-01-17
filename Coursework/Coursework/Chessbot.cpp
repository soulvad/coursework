#include "Chessbot.h"

ChessBot::ChessBot() {
    root = make_unique<MoveNode>(-1, -1, -1, -1, 0.0);
    current_node = root.get();
}

double ChessBot::getMaterialBalance(Game& game) {
    vector<vector<Piece*>> board = game.getBoard();
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                int pieceValue = piece_values.at(board[i][j]->getLetter());
                score += board[i][j]->getIsWhite() ? pieceValue : -pieceValue;
            }
        }
    }
    return score;
}

double ChessBot::evaluateExplosion(Game& game, vector<int>& move) {
    Game simulatedGame = game;
    simulatedGame.makeMove(move[0], move[1], move[2], move[3]);
    double position_before = getMaterialBalance(game);
    double position_after = getMaterialBalance(simulatedGame);
    return (position_before - position_after) * 2.0;
}

double ChessBot::evaluatePosition(Game& game, vector<int>& move) {
    double material_balance = getMaterialBalance(game);
    double explosion_value = evaluateExplosion(game, move);
    return material_balance + explosion_value;
}

double ChessBot::alphaBeta(Game& game, MoveNode* node, int depth, double alpha, double beta, bool maximizingPlayer) {
    if (depth == 0 || game.getIsGameOver()) {
        return getMaterialBalance(game);
    }

    vector<vector<int>> moves = game.getAllLegalMoves(maximizingPlayer ? false : true);

    if (maximizingPlayer) {
        double maxEval = -numeric_limits<double>::infinity();
        for (auto& move : moves) {
            Game newGame = game;
            newGame.makeMove(move[0], move[1], move[2], move[3]);

            vector<int> move_key = { move[0], move[1], move[2], move[3] };
            if (node->children.find(move_key) == node->children.end()) {
                node->children[move_key] = make_unique<MoveNode>(move[0], move[1], move[2], move[3], 0.0);
            }

            double eval = alphaBeta(newGame, node->children[move_key].get(), depth - 1, alpha, beta, false);
            eval += evaluatePosition(game, move);
            node->children[move_key]->evaluation = eval;

            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    }
    else {
        double minEval = numeric_limits<double>::infinity();
        for (auto& move : moves) {
            Game newGame = game;
            newGame.makeMove(move[0], move[1], move[2], move[3]);

            vector<int> move_key = { move[0], move[1], move[2], move[3] };
            if (node->children.find(move_key) == node->children.end()) {
                node->children[move_key] = make_unique<MoveNode>(move[0], move[1], move[2], move[3], 0.0);
            }

            double eval = alphaBeta(newGame, node->children[move_key].get(), depth - 1, alpha, beta, true);
            eval += evaluatePosition(game, move);
            node->children[move_key]->evaluation = eval;

            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}

vector<int> ChessBot::findBestMove(Game& game, MoveNode* current_node, int depth, bool isWhite) {
    alphaBeta(game, current_node, depth, -numeric_limits<double>::infinity(), numeric_limits<double>::infinity(), isWhite);

    vector<int> best_move;
    double best_eval = (isWhite) ? -numeric_limits<double>::infinity() : numeric_limits<double>::infinity();

    for (const auto& child_pair : current_node->children) {
        const vector<int>& move = child_pair.first;
        const MoveNode* child = child_pair.second.get();

        if ((isWhite && child->evaluation > best_eval) || (!isWhite && child->evaluation < best_eval)) {
            best_eval = child->evaluation;
            best_move = move;
        }
    }

    return best_move;
}


void ChessBot::updateTreeAfterPlayerMove(vector<int> player_move) {
    if (current_node->children.find(player_move) != current_node->children.end()) {
        current_node = current_node->children[player_move].get();
    }
    else {
        current_node = root.get();
    }
}