#include <bits/stdc++.h>

using namespace std;

int main() {
  vector<int> img;
  int pixel;
  while (cin >> pixel) {
    img.push_back(pixel);
  }

  int n = img.size();
  int best_k = 0;
  double min_diff = INT_MAX;

  // 遍历所有可能的k
  for (int k = -255; k <= 255; k++) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
      int new_pixel = img[i] + k;
      new_pixel = max(0, min(new_pixel, 255)); // 截取到[0, 255]
      sum += new_pixel;
    }
    double avg = sum / n;
    double diff = abs(avg - 128);

    if (diff < min_diff || (diff == min_diff && k < best_k)) {
      min_diff = diff;
      best_k = k;
    }
  }

  cout << best_k << endl;

  return 0;
}