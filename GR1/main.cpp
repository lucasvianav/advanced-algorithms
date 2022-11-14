#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <queue>
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

#define MAX_N_CITIES 500

class Graph {
private:
  ll n, cache[MAX_N_CITIES][MAX_N_CITIES];
  unordered_map<ll, set<pair<ll, ll>>> neighbors;

public:
  Graph(unordered_map<ll, set<pair<ll, ll>>> neighbors, int n) {
    this->neighbors = neighbors;
    this->n = n;

    fill_n(cache[0], MAX_N_CITIES * MAX_N_CITIES, LLONG_MAX);
  }

  bool validate_distance(ll distance) {
    return distance != LLONG_MAX && distance >= 0;
  }

  ll dijkstra(ll root, ll target) {
    if (root == target) {
      return 0;
    } else if (cache[root][target] != LLONG_MAX) {
      return cache[root][target];
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>>
        backlog;
    vector<ll> dist(n);

    ffor(i, 0, n) {
      dist[i] = cache[root][i] != -1 ? cache[root][i] : LLONG_MAX;
    }

    backlog.push(make_pair(0, root));
    dist[root] = 0;

    while (!backlog.empty()) {
      auto top = backlog.top();
      ll cost = top.first, curr = top.second;

      backlog.pop();

      if (curr == target && cost <= cache[root][target]) {
        cache[root][target] = cost;
        break;
      } else if ((validate_distance(cache[curr][target]) &&
                  cost + cache[curr][target] >= cache[root][target])) {
        continue;
      } else if (validate_distance(cache[curr][target]) &&
                 cost + cache[curr][target] < cache[root][target]) {
        cache[root][target] = cost + cache[curr][target];
      }

      for (auto adj : neighbors[curr]) {
        ll neighbor = adj.second, next_cost = cost + adj.first;

        if ((next_cost <= dist[neighbor] && next_cost < cache[root][target])) {
          dist[neighbor] = next_cost;
          backlog.push(make_pair(next_cost, neighbor));
        }
      }
    }

    if (cache[root][target] == LLONG_MAX) {
      cache[root][target] = -1;
    }
    cache[target][root] = cache[root][target];

    return cache[root][target];
  }
};

int main() {
  ll n_cities, n_roads, n_queries, tmp1, tmp2, tmp3;
  unordered_map<ll, set<pair<ll, ll>>> adjacency_lists;

  cin >> n_cities >> n_roads >> n_queries;

  ffor(i, 0, n_roads) {
    cin >> tmp1 >> tmp2 >> tmp3;
    adjacency_lists[tmp1 - 1].insert(make_pair(tmp3, tmp2 - 1));
    adjacency_lists[tmp2 - 1].insert(make_pair(tmp3, tmp1 - 1));
  }

  Graph g(adjacency_lists, n_cities);

  ffor(i, 0, n_queries) {
    cin >> tmp1 >> tmp2;
    cout << g.dijkstra(tmp1 - 1, tmp2 - 1) << endl;
  }

  return 0;
}
