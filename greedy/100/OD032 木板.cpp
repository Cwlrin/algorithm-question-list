#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int left = *min_element(a.begin(), a.end());
  int right = left + m;

  while (left < right) {
    int mid = left + (right - left + 1) / 2;
    long long need = 0;
    for (int length : a) {
      if (length < mid) {
        need += (mid - length);
      }
    }
    if (need <= m) {
      left = mid;
    } else {
      right = mid - 1;
    }
  }

  cout << left << endl;

  return 0;
}