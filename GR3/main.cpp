#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cstring>
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

#define MAX_NODES 100

class Solution {
private:
  int M[MAX_NODES][MAX_NODES], R[MAX_NODES][MAX_NODES], n;

  vi find_path(int root, int target) {
    queue<vi> backlog;
    vector<bool> history(n, false);

    backlog.push({root});
    history[root] = true;

    while (!backlog.empty()) {
      vi path = backlog.front();
      int curr = path.back();

      backlog.pop();

      ffor(neighbor, 0, n) {
        if (R[curr][neighbor] > 0 && !history[neighbor]) {
          vi new_path(path);

          new_path.push_back(neighbor);
          backlog.push(new_path);

          if (neighbor == target) {
            return new_path;
          }

          history[neighbor] = true;
        }
      }
    }

    return {};
  }

public:
  Solution(int M[MAX_NODES][MAX_NODES], int n) {
    this->n = n;

    ffor(i, 0, n) {
      ffor(j, 0, n) {
        this->M[i][j] = M[i][j];
        this->R[i][j] = M[i][j];
      }
    }
  };

  int solve(int root, int target) {
    int max_flow = 0;
    vi path;

    while (!(path = find_path(root, target)).empty()) {
      int bottleneck = INT_MAX;

      for (auto i = path.begin(); i != path.end() - 1; i++) {
        bottleneck = min(bottleneck, R[*i][*(i + 1)]);
      }

      for (auto i = path.begin(); i != path.end(); i++) {
        R[*i][*(i + 1)] -= bottleneck;
      }

      max_flow += bottleneck;
    }

    return max_flow;
  };
};

int main() {
  int n_nodes, n_edges, u, v, w, root, target, M[MAX_NODES][MAX_NODES], i = 0;

  while (++i) {
    cin >> n_nodes;

    if (!n_nodes) {
      break;
    }

    cin >> root >> target >> n_edges;
    memset(M, 0, sizeof(M));

    ffor(i, 0, n_edges) {
      cin >> u >> v >> w;
      M[u - 1][v - 1] += w;
      M[v - 1][u - 1] += w;
    }

    cout << (i > 1 ? "\n" : "") << "Network " << i << endl;
    cout << "The bandwidth is "
         << Solution(M, n_nodes).solve(root - 1, target - 1) << "." << endl;
  }

  return 0;
}
