import warnings, square

class Board(object):
    """This class maintains the board state"""

    def __init__(self, squares=None, size=9):
        self.squares = squares
        self.size = size

    def initialize_from_file(self, file_name):

        if self.squares is not None:
            warnings.warn("Board being initialized without clearing!", RuntimeWarning)

        self.squares = [[square.Square()] * self.size for i in range(self.size)]

        with open("puzzles/{}.txt".format(file_name), "r") as f:

            nums = f.readline().strip()

        if len(nums) != (self.size ** 2):
            raise RuntimeError("File {} is too short for this size board!".format(file_name))

        for i in range(len(nums)):
            if nums[i] is "0":
                possible = self.size *[True]
                num = int(nums[i])
                self.squares[i // self.size][i % self.size] = square.Square(num, possible)
            else:
                possible = self.size *[False]
                num = int(nums[i])
                possible[num - 1] = True
                self.squares[i // self.size][i % self.size] = square.Square(num, possible)
