#include <bits/stdc++.h>

using namespace std;

int main() {
  int M;
  cin >> M;

  vector<int> P;
  int p;
  while (cin >> p) {
    P.push_back(p);
  }

  // 初始化 dp 数组
  vector<int> dp(M + 1, 0);

  // 动态规划求解
  for (int i = 1; i <= P.size(); ++i) {
    for (int j = i; j <= M; ++j) {
      dp[j] = max(dp[j], dp[j - i] + P[i - 1]);
    }
  }

  // 输出结果
  cout << dp[M] << endl;

  return 0;
}