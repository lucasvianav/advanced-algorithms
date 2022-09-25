class Solution:
    def __init__(self):
        self.cols_taken = []
        self.bot_diags_taken = set()
        self.top_diags_taken = set()
        self.solutions: set[int] = set()

    def backtracking(self, board: list[list[int]], row=0):
        n = len(board)

        if row == n:
            self.solutions.add(sum([board[i][self.cols_taken[i]] for i in range(n)]))
            return

        available_cols = [
            j for j in range(n) if j not in self.cols_taken
            and (row - j) not in self.bot_diags_taken
            and (row + j) not in self.top_diags_taken
        ]

        for col in available_cols:
            self.cols_taken.append(col)
            self.bot_diags_taken.add(row - col)
            self.top_diags_taken.add(row + col)

            self.backtracking(board, row + 1)

            self.cols_taken.pop()
            self.bot_diags_taken.remove(row - col)
            self.top_diags_taken.remove(row + col)

    def solve(self, board: list[list[int]]) -> list:
        self.backtracking(board)
        return list(self.solutions)


if __name__ == "__main__":
    n_cases = int(input())
    scores: list[int] = []

    for _ in range(n_cases):
        data = [[int(n) for n in input().split()] for _ in range(8)]
        scores.append(max(Solution().solve(data)))

    length = len(str(max(scores)))

    for score in scores:
        print(" ", str(score).rjust(length))
