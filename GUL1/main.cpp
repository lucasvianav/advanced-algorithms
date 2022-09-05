#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

typedef struct SprinklerCircle {
  int center;
  int radius;
} SprinklerCircle;

typedef struct Lawn {
  int length;
  int height;
} Lawn;

typedef struct SprinklerRectangle {
  double left_end;
  double right_end;

  friend bool operator<(SprinklerRectangle &a, SprinklerRectangle &b) {
    return a.left_end < b.left_end ||
           (a.left_end == b.left_end && a.right_end > b.right_end);
  };
} SprinklerRectangle;

int min_sprinklers(Lawn lawn, vector<SprinklerCircle> sprinklers) {
  vector<SprinklerRectangle> rectangles;
  double farthest_right_end = 0;

  for (auto sprinkler : sprinklers) {
    if (2 * sprinkler.radius > lawn.height) {
      double rect_half_length =
          sqrt(pow(sprinkler.radius, 2) - pow(lawn.height, 2) / 4);

      rectangles.push_back({sprinkler.center - rect_half_length,
                            sprinkler.center + rect_half_length});
      farthest_right_end = max(farthest_right_end, rectangles.back().right_end);
    }
  }

  sort(rectangles.begin(), rectangles.end());

  if (!rectangles.size() || rectangles.front().left_end > 0 ||
      farthest_right_end < lawn.length) {
    return -1;
  }

  int min_n_sprinklers = 0, n_sprinklers = rectangles.size(), i = 0;
  double curr_pos = 0, prev_pos;

  while (curr_pos < lawn.length) {
    prev_pos = curr_pos;

    for (int j = i; j < n_sprinklers && rectangles[j].left_end <= prev_pos;
         j++, i++) {
      if (curr_pos < rectangles[j].right_end) {
        curr_pos = rectangles[j].right_end;
      }
    }

    if (curr_pos == prev_pos) {
      break;
    }

    min_n_sprinklers++;
  }

  return curr_pos >= lawn.length ? min_n_sprinklers : -1;
}

int main() {
  int n_sprinklers;
  vector<SprinklerCircle> sprinklers;
  Lawn lawn;
  SprinklerCircle sprinkler;

  while (cin >> n_sprinklers >> lawn.length >> lawn.height) {
    for (int i = 0; i < n_sprinklers; i++) {
      cin >> sprinkler.center >> sprinkler.radius;
      sprinklers.push_back(sprinkler);
    }

    cout << min_sprinklers(lawn, sprinklers) << endl;

    sprinklers.clear();
  }

  return 0;
}
