#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, k;
  cin >> n;

  vector<int> score(n);
  for (int i = 0; i < n; ++i) {
    cin >> score[i];
  }

  cin >> k;

  // 动态规划数组
  vector<int> dp(n, 0);
  dp[0] = score[0];

  // 双端队列维护滑动窗口
  deque<int> dq;
  dq.push_back(0);

  for (int i = 1; i < n; ++i) {
    // 移除不在窗口内的索引
    while (!dq.empty() && dq.front() < i - k) {
      dq.pop_front();
    }

    // 当前 dp[i] 为窗口内最大值 + score[i]
    dp[i] = dp[dq.front()] + score[i];

    // 维护递减队列
    while (!dq.empty() && dp[i] >= dp[dq.back()]) {
      dq.pop_back();
    }

    dq.push_back(i);
  }

  // 输出结果
  cout << dp[n - 1] << endl;

  return 0;
}