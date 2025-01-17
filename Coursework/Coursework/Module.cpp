#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Game.h"
#include "Pieces.h"
#include "ChessBot.h"

namespace py = pybind11;

PYBIND11_MODULE(chess_module, m) {
    py::class_<Game>(m, "Game")
        .def(py::init<>())
        .def(py::init<const Game&>())
        .def("get_board", &Game::getBoard, py::return_value_policy::reference_internal)
        .def("get_is_game_over", &Game::getIsGameOver)
        .def("atomic_kaboom", &Game::atomicKaboom)
        .def("is_atomic_legal", &Game::isAtomicLegal)
        .def("make_move", &Game::makeMove)
        .def("check_legal_moves_for_piece", &Game::checkLegalMovesForPiece)
        .def("get_all_legal_moves", &Game::getAllLegalMoves)
        .def("is_draw", &Game::isDraw);

    py::class_<Piece>(m, "Piece")
        .def("get_is_white", &Piece::getIsWhite)
        .def("get_letter", &Piece::getLetter);

    py::class_<Pawn, Piece>(m, "Pawn")
        .def(py::init<bool>())
        .def("obtain_legal_moves", &Pawn::obtainLegalMoves);

    py::class_<Knight, Piece>(m, "Knight")
        .def(py::init<bool>())
        .def("obtain_legal_moves", &Knight::obtainLegalMoves);

    py::class_<Bishop, Piece>(m, "Bishop")
        .def(py::init<bool>())
        .def("obtain_legal_moves", &Bishop::obtainLegalMoves);

    py::class_<Rook, Piece>(m, "Rook")
        .def(py::init<bool>())
        .def("get_is_moved", &Rook::getIsMoved)
        .def("set_is_moved", &Rook::setIsMoved)
        .def("obtain_legal_moves", &Rook::obtainLegalMoves);

    py::class_<Queen, Piece>(m, "Queen")
        .def(py::init<bool>())
        .def("obtain_legal_moves", &Queen::obtainLegalMoves);

    py::class_<King, Piece>(m, "King")
        .def(py::init<bool>())
        .def("get_is_moved", &King::getIsMoved)
        .def("set_is_moved", &King::setIsMoved)
        .def("obtain_legal_moves", &King::obtainLegalMoves);

    py::class_<ChessBot>(m, "ChessBot")
        .def(py::init<>())
        .def("find_best_move", &ChessBot::findBestMove)
        .def("update_tree_after_player_move", &ChessBot::updateTreeAfterPlayerMove);

    py::class_<MoveNode>(m, "MoveNode")
        .def(py::init<int, int, int, int, double>());

    m.def("create_move_node", [](int fr, int fc, int tr, int tc, double eval) {
        return std::make_unique<MoveNode>(fr, fc, tr, tc, eval);
        });
}

int main() {
    return 0;
}