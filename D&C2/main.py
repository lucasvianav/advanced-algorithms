class Solution:
    def __init__(self, songs: list[tuple[int, int]],):
        self.endings: list[int] = []

        now = 0
        for n_repetitions, duration in songs:
            now += n_repetitions * duration
            self.endings.append(now)

    def solve(self, moment: int) -> int:
        return self.binary_search(moment, 0, len(self.endings) - 1)

    def binary_search(self, moment: int, left: int, right: int) -> int:
        middle = (left + right) // 2

        if left > right:
            return -1
        elif (middle == 0 or self.endings[middle - 1] < moment) and moment <= self.endings[middle]:
            return middle + 1
        elif self.endings[middle] < moment:
            return self.binary_search(moment, middle + 1, right)
        else:
            return self.binary_search(moment, left, middle - 1)


if __name__ == "__main__":
    n_songs, n_moments = (int(e) for e in input().strip().split())
    songs = [tuple(int(e) for e in input().strip().split()) for _ in range(n_songs)]  # n_repetitions, duration
    moments = [int(e) for e in input().strip().split()]
    solver = Solution(songs)

    for moment in moments:
        print(solver.solve(moment))
