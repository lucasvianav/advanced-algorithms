#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

vector<pair<int, int>> stable_match(vector<vector<int>> pref_m,
                                    vector<vector<int>> pref_f) {
  vector<int> single_men(pref_m.size());
  iota(begin(single_men), end(single_men), 0);

  unordered_map<int, int> pairs_m;
  unordered_map<int, int> pairs_f;
  unordered_map<int, set<int>> proposed;

  while (!single_men.empty()) {
    int curr = single_men.front();
    vector<int> pref = pref_m[curr];

    single_men.erase(single_men.begin());

    for (int woman : pref) {
      // if the current proposer already proposed
      // to the current woman, skip her
      if (proposed[curr].count(woman)) {
        continue;
      }

      proposed[curr].insert(woman);

      if (pairs_f.find(woman) != pairs_f.end()) {
        auto pref_married =
            find(pref_f[woman].begin(), pref_f[woman].end(), pairs_f[woman]);
        auto pref_proposer =
            find(pref_f[woman].begin(), pref_f[woman].end(), curr);

        // if the woman's husband comes before the current proposer in
        // her preference list, she won't leave him for the proposer
        if (distance(pref_married, pref_proposer) > 0) {
          continue;
        }

        // otherwise undo the marriage and make the ex-husband single again
        pairs_m.erase(pairs_f[woman]);
        single_men.push_back(pairs_f[woman]);
        pairs_f.erase(woman);
      }

      // marry the current proposer to the current woman
      pairs_m[curr] = woman;
      pairs_f[woman] = curr;
      break;
    }
  };

  vector<pair<int, int>> output(pairs_m.begin(), pairs_m.end());
  sort(output.begin(), output.end());

  return output;
}

void read_preferences(vector<vector<int>> *pref, int n_marriages) {
  int pref_id;

  for (int i = 0; i < n_marriages; i++) {
    vector<int> tmp;

    cin >> pref_id;
    for (int k = 0; k < n_marriages; k++) {
      cin >> pref_id;
      tmp.push_back(pref_id - 1);
    }

    pref->push_back(tmp);
  }
}

int main() {
  int n_cases, n_marriages;
  vector<vector<int>> pref_f, pref_m;

  cin >> n_cases;
  for (int i = 0; i < n_cases; i++) {
    cin >> n_marriages;
    read_preferences(&pref_f, n_marriages);
    read_preferences(&pref_m, n_marriages);

    for (pair<int, int> match : stable_match(pref_m, pref_f)) {
      cout << match.first + 1 << ' ' << match.second + 1 << endl;
    }

    pref_f.clear();
    pref_m.clear();
  }

  return 0;
}
