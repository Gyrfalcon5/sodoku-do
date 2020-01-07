"""This program will handle the main game logic, and eventually also the
   terminal UI"""
import square, board


def print_board(board):
    """Prints board when given the board as a 2d array/nested list"""
    board_string = ""

    for row_iter in range(len(board)):
        for col_iter in range(len(board)):
            if (board[row_iter][col_iter].value):
                board_string += " {} ".format(board[row_iter][col_iter].value)
            else:
                board_string += "   "

            if (((col_iter + 1) % 3) == 0 and col_iter != 8):
                board_string += "| "

        if (((row_iter + 1) % 3) == 0 and row_iter != 8):
            board_string += "\n-------------------------------\n"
        else:
            board_string += "\n"

    print(board_string)

def main():
    test = board.Board()
    test.initialize_from_file("easy")
        
    try:
        test.initialize_from_file("broken")
    except RuntimeError:
        print("This board is the wrong size!")

    try:
        test.initialize_from_file("hard")
    except FileNotFoundError:
        print("This board doesn't exist!")

main()
