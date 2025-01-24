#include <bits/stdc++.h>

using namespace std;

int main() {
  int T, n;
  cin >> T >> n;

  vector<int> t(n + 1), w(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> t[i] >> w[i];
  }

  // 初始化 dp 数组
  vector<int> dp(T + 1, 0);

  // 动态规划求解
  for (int i = 1; i <= n; ++i) {
    for (int j = T; j >= t[i]; --j) {
      dp[j] = max(dp[j], dp[j - t[i]] + w[i]);
    }
  }

  // 输出结果
  cout << dp[T] << endl;

  return 0;
}