class Solution:
    def __init__(self):
        pass

    def solve(self, data: list) -> int:
        return len(data)


if __name__ == "__main__":
    n_cases = int(input())

    for _ in range(n_cases):
        n_inputs = int(input())
        data = [int(input()) for _ in range(n_inputs)]
        print(Solution().solve(data))
