#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cmath>
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
  int bin_to_dec(string n) {
    int dec = 0, acc = pow(2, n.length());

    for (auto bit : n) {
      if (bit == '1') {
        dec += acc;
      }
      acc /= 2;
    }

    return dec;
  }

public:
  bool solve(string bin, int prime) { return !(bin_to_dec(bin) % prime); }
};

int main() {
  string bin, tmp;

  while (cin >> bin) {
    tmp = bin;

    while (tmp.back() != '#') {
      cin >> tmp;
      bin += tmp;
    }

    bin.pop_back();
    cout << (Solution().solve(bin, 131071) ? "YES" : "NO") << endl;
  }

  return 0;
}
