#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  // 排序
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  int score = 0;
  int i = 0, j = 0, k = n - 1, l = n - 1;

  // 田忌赛马策略
  while (i <= k) {
    if (a[k] > b[l]) {
      score += 1;
      k--;
      l--;
    } else if (a[i] > b[j]) {
      score += 1;
      i++;
      j++;
    } else {
      if (a[i] < b[l]) {
        score -= 1;
      }
      i++;
      l--;
    }
  }

  cout << score << endl;

  return 0;
}