#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, d;
  cin >> n >> d;

  vector<int> strength(n);
  for (int i = 0; i < n; i++) {
    cin >> strength[i];
  }

  // 排序
  sort(strength.begin(), strength.end());

  // 动态规划数组
  // dp[i].first 表示前 i 个队伍的最大匹配数
  // dp[i].second 表示对应的最小实力差值总和
  vector<pair<int, int> > dp(n + 1, {0, 0});

  for (int i = 1; i <= n; i++) {
    dp[i] = dp[i - 1]; // 不匹配第 i 个队伍
    for (int j = 1; j < i; j++) {
      if (strength[i - 1] - strength[j - 1] <= d) {
        int new_match = dp[j - 1].first + 1;
        int new_diff = dp[j - 1].second + (strength[i - 1] - strength[j - 1]);
        if (new_match > dp[i].first || (
              new_match == dp[i].first && new_diff < dp[i].second)) {
          dp[i] = {new_match, new_diff};
        }
      }
    }
  }

  if (dp[n].first == 0) {
    cout << -1 << endl;
  } else {
    cout << dp[n].second << endl;
  }

  return 0;
}