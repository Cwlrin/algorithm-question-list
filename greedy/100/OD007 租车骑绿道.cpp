#include <bits/stdc++.h>

using namespace std;

int main() {
  int m, n;
  cin >> m >> n;

  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
  }

  // 排序
  sort(weights.begin(), weights.end());

  int left = 0, right = n - 1;
  int bikes = 0;

  // 双指针法
  while (left <= right) {
    if (weights[left] + weights[right] <= m) {
      left++;
    }
    right--;
    bikes++;
  }

  cout << bikes << endl;

  return 0;
}