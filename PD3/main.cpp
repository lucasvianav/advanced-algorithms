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

#define MAX 1000000007
#define EMPTY '.'

class Solution {
private:
  vector<vector<char>> grid;
  unordered_map<int, unordered_map<int, int>> cache;
  int n_rows, n_cols;

public:
  Solution(vector<vector<char>> *data) {
    this->grid = *data;
    this->n_rows = data->size();
    this->n_cols = (*data)[0].size();
  }
  ll solve() { return solve(0, 0); }

  ll solve(int i, int j) {
    if (i == n_rows || j == n_cols || grid[i][j] != EMPTY) {
      return 0;
    } else if (i == n_rows - 1 && j == n_cols - 1) {
      return 1;
    } else if (!present(cache[i], j)) {
      cache[i][j] = (solve(i, j + 1) + solve(i + 1, j)) % MAX;
    }

    return cache[i][j];
  }
};

int main() {
  int n_rows, n_cols;
  char tmp;
  vector<char> tmp_v;
  vector<vector<char>> data;

  cin >> n_rows >> n_cols;

  ffor(i, 0, n_rows) {
    ffor(j, 0, n_cols) {
      cin >> tmp;
      tmp_v.pb(tmp);
    }
    data.pb(tmp_v);
    tmp_v.clear();
  }

  cout << Solution(&data).solve() << endl;

  return 0;
}
