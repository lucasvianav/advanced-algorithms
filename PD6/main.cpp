#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

#define ffor(i, o, n) for (int i = (int)(o); i < (int)(n); i++)
#define fforr(i, o, n) for (int i = (int)(n)-1; i >= o; i--) // reverse

// short hand for usual tokens
#define pb push_back
#define fi first
#define se second

// to be used with algorithms that processes a container Eg: find(all(c),42)
#define all(x) (x).begin(), (x).end()  // Forward traversal
#define rall(x) (x).rbegin, (x).rend() // reverse traversal

// traversal function to avoid long template definition. Now with C++11 auto
// alleviates the pain.
#define tr(c, i)                                                               \
  for (__typeof__((c)).begin() i = (c).begin(); i != (c).end(); i++)

// find if a given value is present in a container. Container version. Runs in
// log(n) for set and map
#define present(c, x) ((c).find(x) != (c).end())

// find version works for all containers. This is present in std namespace.
#define cpresent(c, x) (find(all(c), x) != (c).end())

using namespace std;

// Shorthand for commonly used types
typedef unordered_map<int, int> umi;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef double ld;

////////////////////////////////////////////////////////////////////////////////

class Solution {
private:
  int min(int i, int j, int k) { return std::min(i, std::min(j, k)); }
  string word1, word2;
  int len1, len2;

public:
  Solution(string word1, string word2) {
    this->word1 = word1;
    this->word2 = word2;
    this->len1 = word1.length();
    this->len2 = word2.length();
  }

  int solve() {
    vvi cache(2);

    ffor(i, 0, cache.size()) { cache[i].resize(len1 + 1, 0); }
    ffor(i, 0, len1 + 1) { cache[0][i] = i; }

    ffor(i, 1, len2 + 1) {
      ffor(j, 0, len1 + 1) {
        if (j == 0) {
          cache[i % 2][j] = i;
        } else if (word1[j - 1] == word2[i - 1]) {
          cache[i % 2][j] = cache[(i - 1) % 2][j - 1];
        } else {
          cache[i % 2][j] = 1 + min(cache[(i - 1) % 2][j], cache[i % 2][j - 1],
                                    cache[(i - 1) % 2][j - 1]);
        }
      }
    }

    return cache[len2 % 2][len1];
  }
};

int main() {
  int n_cases;
  string word1, word2;

  cin >> n_cases;
  ffor(i, 0, n_cases) {
    cin >> word1 >> word2;
    cout << Solution(word1, word2).solve() << endl;
  }

  return 0;
}
