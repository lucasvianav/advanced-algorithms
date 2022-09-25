def get_neighbors(i, j, matrix):
    neighbors = []

    rows = len(matrix)
    cols = len(matrix[0])

    if i < rows - 1:
        neighbors.append((i + 1, j))
    if i > 0:
        neighbors.append((i - 1, j))
    if j < cols - 1:
        neighbors.append((i, j + 1))
    if j > 0:
        neighbors.append((i, j - 1))

    return neighbors


def exist(board: list[list[str]], word: str) -> bool:
    backlog = [(0, 0, set([(0, 0)]))]
    length = len(word)
    started = set([(0, 0)])

    while backlog:
        x, y, history = backlog.pop()
        pos = len(history) - 1
        curr = board[x][y]

        if curr == word[pos] and pos + 1 == length:
            return True

        target = word[pos + 1] if pos + 1 < length else None
        neighbors = get_neighbors(x, y, board)

        for i, j in neighbors:
            char = board[i][j]

            if char == target and board[x][y] == word[pos]:
                if (i, j) not in history:
                    backlog.append((i, j, history.union([(i, j)])))
            elif (i, j) not in started:
                backlog.append((i, j, set([(i, j)])))
                started.add((i, j))

    return False


if __name__ == "__main__":
    n, _ = (int(e) for e in input().split())
    board = [list(input()) for _ in range(n)]
    input()
    word = input()

    print("Yes" if exist(board, word) else "No")
