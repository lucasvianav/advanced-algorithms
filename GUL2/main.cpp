#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

float imbalance(vector<vector<int>> chambers, float avg_mass) {
  return accumulate(chambers.begin(), chambers.end(), 0.,
                    [avg_mass](float acc, vector<int> cur) -> float {
                      return acc + abs(accumulate(cur.begin(), cur.end(), 0.) -
                                       avg_mass);
                    });
}

vector<vector<int>> arrange_chambers(vector<int> masses, int n_chambers) {
  vector<vector<int>> chambers(n_chambers);
  int n_masses = masses.size();
  int right_allocated_index;

  sort(masses.begin(), masses.end());

  for (int i = 0; i < n_chambers; i++) {
    if (i == right_allocated_index) {
      break;
    }

    if (masses[i]) {
      chambers[i].push_back(masses[i]);
    }
    if (masses[n_masses - 1 - i]) {
      right_allocated_index = n_masses - 1 - i;
      chambers[i].push_back(masses[right_allocated_index]);
    }
  }

  return chambers;
}

int main() {
  int n_chambers, n_specimens, n_set = 0;
  vector<vector<int>> chambers;

  while (cin >> n_chambers >> n_specimens) {
    vector<int> masses(2 * n_chambers);
    for (int i = 0; i < n_specimens; i++) {
      cin >> masses[i];
    }

    chambers = arrange_chambers(masses, n_chambers);

    cout << "Set #" << ++n_set << endl;
    for (int i = 0; i < n_chambers; i++) {
      cout << " " << i << ": ";
      for (auto mass : chambers[i]) {
        cout << mass << " ";
      }
      cout << endl;
    }
    printf("IMBALANCE = %.5f\n\n",
           imbalance(chambers, accumulate(masses.begin(), masses.end(), 0.) /
                                   n_chambers));
  }

  return 0;
}
