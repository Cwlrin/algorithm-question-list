#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<string> logs(n);
  for (int i = 0; i < n; i++) {
    cin >> logs[i];
  }

  stable_sort(logs.begin(), logs.end(), [](const auto& a, const auto& b) {
    int h1, h2, m1, m2, s1, s2, n1, n2;
    sscanf(a.c_str(), "%d:%d:%d.%d", &h1, &m1, &s1, &n1);
    sscanf(b.c_str(), "%d:%d:%d.%d", &h2, &m2, &s2, &n2);

    // 直接分别比较时分秒毫秒，避免计算后数据过大
    if (h1 != h2) return h1 < h2;
    if (m1 != m2) return m1 < m2;
    if (s1 != s2) return s1 < s2;
    return n1 < n2;
  });

  for (const auto& log : logs) {
    cout << log << endl;
  }

  return 0;
}