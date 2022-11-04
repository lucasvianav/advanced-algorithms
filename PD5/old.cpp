#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/** Priciest Common Subsequence. */
int PCS(string str1, string str2, unordered_map<char, int> prices) {
  int N = str1.length(), M = str2.length();
  int **cache = (int **)malloc((N + 1) * sizeof(int *));
  char ch;

  for (int i = 0; i <= N; i++) {
    cache[i] = (int *)malloc((M + 1) * sizeof(int));

    for (int j = 0; j <= M; j++) {
      if (i == 0 || j == 0) {
        cache[i][j] = 0;
      } else {
        cache[i][j] = (ch = str1[i - 1]) == str2[j - 1]
                          ? cache[i - 1][j - 1] + prices[ch]
                          : max(cache[i - 1][j], cache[i][j - 1]);
      }
    }
  }

  int result = cache[N][M];

  for (int i = 0; i <= N; i++) {
    free(cache[i]);
  }
  free(cache);

  return result;
}

int main() {
  int N, M;
  string str1, str2;
  unordered_map<char, int> prices;

  cin >> N >> M;
  for (char i = 'a'; i <= 'z'; i++) {
    cin >> prices[i];
  }
  cin >> str1 >> str2;

  cout << PCS(str1, str2, prices) << endl;

  return 0;
}
