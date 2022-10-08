#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <iostream>
#include <vector>
#include <unordered_map>

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

class Solution {
private:
  vi days;
  int n_mountains;
  unordered_map<int, int> cache;
public:
  Solution(vi *data) {
    this->days = *data;
    this->n_mountains = data->size();
  }

  int solve(int curr) {
    if (curr == n_mountains - 1) {
      return 0;
    }

    if (!present(cache, curr)) {
      cache[curr] = INT_MAX;
      ffor(i, 1, 3) {
        if (curr + i < n_mountains) {
          cache[curr] = min(cache[curr], solve(curr + i) + abs(days[curr] - days[curr + i]));
        }
      }
    }

    return cache[curr];
  }

  int solve() {
    this->cache[n_mountains - 1] = 0;
    this->cache[n_mountains] = 0;

    fforr(i, 0, n_mountains - 1) {
      cache[i] = INT_MAX;
      ffor(j, 1, 3) {
        if (i + j < n_mountains) {
          cache[i] = min(cache[i], cache[i + j] + abs(days[i] - days[i + j]));
        }
      }
    }

    return cache[0];
  }
};

int main() {
  int n_mountains, tmp;
  vi data;

  cin >> n_mountains;
  ffor(j, 0, n_mountains) {
    cin >> tmp;
    data.pb(tmp);
  }

  cout << Solution(&data).solve() << endl;

  return 0;
}
