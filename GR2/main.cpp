#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <iostream>
#include <tuple>
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

class Graph {
private:
  ll n;
  vector<tuple<ll, ll, ll>> edges;

public:
  Graph(vector<tuple<ll, ll, ll>> edges, ll n) {
    this->edges = edges;
    this->n = n;
  }

  bool has_negative_cycle() {
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
        backlog;
    vector<ll> dist(n, LLONG_MAX);
    ll u, v, w;

    dist[0] = 0;

    ffor(i, 0, n) {
      for (auto edge : edges) {
        u = get<0>(edge), v = get<1>(edge), w = get<2>(edge);
        if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
        }
      }
    }

    for (auto edge : edges) {
      u = get<0>(edge), v = get<1>(edge), w = get<2>(edge);
      if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
        return true;
      }
    }

    return false;
  };
};

int main() {
  ll n_nodes, n_edges, u, v, w;
  vector<tuple<ll, ll, ll>> edges;

  cin >> n_nodes >> n_edges;
  ffor(i, 0, n_edges) {
    cin >> u >> v >> w;
    edges.push_back({u - 1, v - 1, w});
  }

  cout << (Graph(edges, n_nodes).has_negative_cycle() ? "YES" : "NO") << endl;

  return 0;
}
