#include <iostream>
#include <vector>

using namespace std;

int fn(vector<int> vec) { return 0; }

int main() {
  int n_cases, n, tmp;
  vector<int> vec;

  cin >> n_cases;
  for (int i = 0; i < n_cases; i++) {
    cin >> n;

    for (int i = 0; i < n; i++) {
      cin >> tmp;
      vec.push_back(tmp);
    }

    cout << fn(vec) << endl;
    vec.clear();
  }

  return 0;
}
