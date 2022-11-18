#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <utility>
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
  vii prime_factors(ll n) {
    vii factors;
    int i = 0;

    if (n) {
      for (i = 0; !(n % 2); n /= 2, i++) {
      }
      if (i) {
        factors.push_back(make_pair(2, i));
      }

      for (int j = 3; j <= sqrt(n); j += 2) {
        for (i = 0; !(n % j); n /= j, i++) {
        }
        if (i) {
          factors.push_back(make_pair(j, i));
        }
      }
    }

    if (n > 2) {
      factors.push_back(make_pair(n, 1));
    }

    return factors;
  }

public:
  bool solve(ll n, ll d) {
    if (d == 1) {
      return true;
    }

    vii factors = prime_factors(d);

    if (d == 0 || factors.back().first > n) {
      return false;
    }

    // https://medium.com/@krmayank/prime-numbers-and-factorials-e610da4b2441
    for (auto f : factors) {
      int qnt = 0, power = 0;

      while (n >= pow(f.first, ++power)) {
        qnt += (int)(n / pow(f.first, power));
      }

      if (qnt < f.second) {
        return false;
      }
    }

    return true;
  }
};

int main() {
  ll n, d;

  while (cin >> n >> d) {
    cout << d << " " << (Solution().solve(n, d) ? "divides" : "does not divide")
         << " " << n << "!" << endl;
  }

  return 0;
}
