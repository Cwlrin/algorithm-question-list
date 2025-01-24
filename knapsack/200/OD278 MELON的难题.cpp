#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> m(n);
  int total_weight = 0;
  for (int i = 0; i < n; ++i) {
    cin >> m[i];
    total_weight += m[i];
  }

  // 如果总重量是奇数，无法均分
  if (total_weight % 2 != 0) {
    cout << -1 << endl;
    return 0;
  }

  int target = total_weight / 2;

  // 初始化 dp 数组和 min_count 数组
  vector<bool> dp(target + 1, false);
  vector<int> min_count(target + 1, INT_MAX);
  dp[0] = true;
  min_count[0] = 0;

  // 动态规划求解
  for (int i = 0; i < n; ++i) {
    for (int j = target; j >= m[i]; --j) {
      if (dp[j - m[i]]) {
        dp[j] = true;
        min_count[j] = min(min_count[j], min_count[j - m[i]] + 1);
      }
    }
  }

  // 如果无法达到 target，输出 -1
  if (!dp[target]) {
    cout << -1 << endl;
    return 0;
  }

  // 输出最小子集大小
  cout << min_count[target] << endl;

  return 0;
}