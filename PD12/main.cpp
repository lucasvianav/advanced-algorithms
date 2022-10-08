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

#define N_PASSES 3
int PASSES[N_PASSES] = {1, 7, 30};

class Solution {
private:
  int n_days;
  vi days, prices;
  unordered_map<int, unordered_map<int, int>> cache;

public:
  Solution(vi *data, vi *prices) {
    this->days = *data;
    this->n_days = data->size();
    this->prices = *prices;
  }
  int solve() { return solve(0, 0); }

  int solve(int curr, int days_bought) {
    if (curr == n_days) {
      return 0;
    } else if (!present(cache[days_bought], curr)) {
      cache[days_bought][curr] = INT_MAX;
      int spent_days = curr + 1 < n_days ? days[curr + 1] - days[curr] : 1;

      if (days_bought <= 0) {
        ffor(i, 0, N_PASSES) {
          cache[days_bought][curr] =
              min(cache[days_bought][curr],
                  solve(curr + 1, PASSES[i] - spent_days) + prices[i]);
        }
      } else {
        cache[days_bought][curr] =
            min(cache[days_bought][curr],
                solve(curr + 1, days_bought - spent_days));
      }
    }

    return cache[days_bought][curr];
  }
};

int main() {
  int n_days, tmp;
  vi data, prices;

  cin >> n_days;
  ffor(_, 0, N_PASSES) {
    cin >> tmp;
    prices.pb(tmp);
  }
  ffor(_, 0, n_days) {
    cin >> tmp;
    data.pb(tmp);
  }

  cout << Solution(&data, &prices).solve() << endl;

  return 0;
}
