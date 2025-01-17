import tkinter as tk
from tkinter import messagebox
import sys
sys.path.append(r"..\Coursework\build\Debug")
import chess_module

game = chess_module.Game()
bot = chess_module.ChessBot()
hint_bot = chess_module.ChessBot()

board_size = 800
cell_size = board_size // 8
depth = 2
selected_piece = None
legal_moves = []

piece_images = {
    "P": r"..\..\Images\Chess_plt60.png",
    "N": r"..\..\Images\Chess_nlt60.png",
    "B": r"..\..\Images\Chess_blt60.png",
    "R": r"..\..\Images\Chess_rlt60.png",
    "Q": r"..\..\Images\Chess_qlt60.png",
    "K": r"..\..\Images\Chess_klt60.png",
    "p": r"..\..\Images\Chess_pdt60.png",
    "n": r"..\..\Images\Chess_ndt60.png",
    "b": r"..\..\Images\Chess_bdt60.png",
    "r": r"..\..\Images\Chess_rdt60.png",
    "q": r"..\..\Images\Chess_qdt60.png",
    "k": r"..\..\Images\Chess_kdt60.png",
}

def choose_difficulty():
    def set_difficulty(level):
        global depth
        depth = level
        difficulty_window.destroy()

    difficulty_window = tk.Toplevel(root)
    difficulty_window.title("Choose Difficulty")
    tk.Button(difficulty_window, text="Easy", command=lambda: set_difficulty(2)).pack()
    tk.Button(difficulty_window, text="Medium", command=lambda: set_difficulty(3)).pack()
    tk.Button(difficulty_window, text="Hard", command=lambda: set_difficulty(4)).pack()

piece_images_loaded = {}

def draw_board():
    global piece_images_loaded
    canvas.delete("all")
    for row in range(8):
        for col in range(8):
            color = "#F0D9B5" if (row + col) % 2 == 0 else "#B58863"
            canvas.create_rectangle(col * cell_size, row * cell_size, (col + 1) * cell_size, (row + 1) * cell_size, fill=color)

            piece = game.get_board()[row][col]
            if piece:
                piece_letter = piece.get_letter()
                if piece.get_is_white():
                    piece_letter = piece_letter.upper()

                if piece_letter not in piece_images_loaded:
                    image_url = piece_images[piece_letter]
                    piece_images_loaded[piece_letter] = tk.PhotoImage(file=image_url)

                img = piece_images_loaded[piece_letter]
                canvas.create_image(col * cell_size + cell_size // 2, row * cell_size + cell_size // 2, image=img)



last_move = chess_module.create_move_node(0, 0, 0, 0, 0.0)

def on_click(event):
    global selected_piece, legal_moves
    
    col = event.x // cell_size
    row = event.y // cell_size
    board = game.get_board()

    if selected_piece:
        if [row, col] in legal_moves:
            game.make_move(selected_piece[0], selected_piece[1], row, col)
            selected_piece = None
            legal_moves = []
            draw_board()
            check_game_over()
            bot_move()
        else:
            selected_piece = None
            legal_moves = []
            draw_board()
    else:
        piece = board[row][col]
        if piece and piece.get_is_white():
            selected_piece = (row, col)
            legal_moves = game.check_legal_moves_for_piece(row, col)
            highlight_moves(legal_moves)


def bot_move():
    global last_move
    if last_move is None:
        last_move = chess_module.MoveNode(0, 0, 0, 0, 0.0)

    best_move = bot.find_best_move(game, last_move, depth, True)
    if (best_move):
        game.make_move(best_move[0], best_move[1], best_move[2], best_move[3])
        last_move = chess_module.create_move_node(best_move[0], best_move[1], best_move[2], best_move[3], 0.0)
        draw_board()
        check_game_over()

def highlight_moves(moves):
    for move in moves:
        canvas.create_rectangle(move[1] * cell_size, move[0] * cell_size, (move[1] + 1) * cell_size, (move[0] + 1) * cell_size, outline="green", width=3)

def check_game_over():
    if game.get_is_game_over():
        messagebox.showinfo("Game Over", "The game is over!")
        root.quit()
    elif game.is_draw():
        messagebox.showinfo("Draw", "It's a draw!")
        root.quit()

def get_hint():
    hint_move = hint_bot.find_best_move(game, chess_module.create_move_node(0, 0, 0, 0, 0.0), 4, False)
    hint_label.config(text=f"Hint: {hint_move}")

root = tk.Tk()
root.title("Atomic Chess")

canvas = tk.Canvas(root, width=board_size, height=board_size)
canvas.pack(side=tk.LEFT)

hint_button = tk.Button(root, text="Hint", command=get_hint)
hint_button.pack()

hint_label = tk.Label(root, text="")
hint_label.pack()

canvas.bind("<Button-1>", on_click)

choose_difficulty()

draw_board()

root.mainloop()