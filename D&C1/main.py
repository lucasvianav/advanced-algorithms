class Solution:
    def __init__(self):
        self.wires: list[tuple[int, int]]

    def solve(self, a: list[int]) -> int:
        self.wires = [(i, a[i - 1]) for i in range(1, len(a) + 1)]
        return self.divide_and_conquer(0, len(self.wires) - 1)

    def divide_and_conquer(self, left: int, right: int) -> int:
        if left >= right:
            return 0

        middle = left + (right - left) // 2

        n_left = self.divide_and_conquer(left, middle)
        n_right = self.divide_and_conquer(middle + 1, right)
        n_merged = self.merge(left, middle, right)

        return n_merged + n_left + n_right

    def merge(self, left: int, middle: int, right: int) -> int:
        tmp: list[tuple[int, int]] = []
        i, j = left, middle + 1
        count = 0

        while i <= middle and j <= right:
            if self.wires[i][0] < self.wires[j][0] and self.wires[i][1] < self.wires[j][1]:
                tmp.append(self.wires[i])
                i += 1
            else:
                tmp.append(self.wires[j])
                count += middle - i + 1
                j += 1

        tmp.extend(self.wires[i:middle + 1])
        tmp.extend(self.wires[j:right + 1])

        for i in range(left, right + 1):
            self.wires[i] = tmp.pop(0)

        return count


if __name__ == "__main__":
    n_cases = int(input())

    for _ in range(n_cases):
        n_inputs = int(input())
        data = [int(n) for n in input().strip().split()]
        print(Solution().solve(data))
