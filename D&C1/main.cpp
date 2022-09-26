#include <bits/stdc++.h>
#include <iostream>
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

class Solution {
private:
  vector<pair<ull, ull>> wires;
  ull divide_and_conquer(ull left, ull right) {
    if (left >= right) {
      return 0;
    }

    ull middle = (right + left) / 2;

    ull n_left = this->divide_and_conquer(left, middle);
    ull n_right = this->divide_and_conquer(middle + 1, right);
    ull n_merged = this->merge(left, middle, right);

    return n_left + n_right + n_merged;
  }
  ull merge(ull left, ull middle, ull right) {
    vector<pair<ull, ull>> tmp;
    ull i = left, j = middle + 1, count = 0;

    while (i <= middle && j <= right) {
      if (this->wires[i].fi < this->wires[j].fi and
          this->wires[i].se < this->wires[j].se) {
        tmp.pb(this->wires[i++]);
      } else {
        tmp.pb(this->wires[j++]);
        count += middle - i + 1;
      }
    }

    while (i <= middle) {
      tmp.pb(this->wires[i++]);
    }

    while (j <= right) {
      tmp.pb(this->wires[j++]);
    }

    for (ull i = left, k = 0; i <= right; i++, k++) {
      this->wires[i] = tmp[k];
    }

    return count;
  }

public:
  ull solve(vector<ull> *a) {
    for (ull i = 1; i <= a->size(); i++) {
      this->wires.pb({i, (*a)[i - 1]});
    };
    return this->divide_and_conquer(0, this->wires.size() - 1);
  }
};

int main() {
  int n_cases, n_inputs;
  ull tmp;
  vector<ull> data;

  cin >> n_cases;
  ffor(i, 0, n_cases) {
    cin >> n_inputs;

    ffor(j, 0, n_inputs) {
      cin >> tmp;
      data.push_back(tmp);
    }

    cout << Solution().solve(&data) << endl;
    data.clear();
  }

  return 0;
}
