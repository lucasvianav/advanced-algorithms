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
typedef unordered_map<int, umi> umumi;
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
  vi data;
  int n;

public:
  Solution(vi *data) {
    this->data = *data;
    this->n = data->size();
  }
  int solve() {
    vi lengths(n, 1);

    ffor(i, 0, n) {
      fforr(j, 0, i) {
        if (data[i] > data[j]) {
          lengths[i] = max(lengths[i], lengths[j] + 1);
        }
      }
    }

    return *max_element(all(lengths));
  }
};

int main() {
  int n_nums, tmp;
  vi data;

  cin >> n_nums;
  ffor(j, 0, n_nums) {
    cin >> tmp;
    data.pb(tmp);
  }

  cout << Solution(&data).solve() << endl;

  return 0;
}
