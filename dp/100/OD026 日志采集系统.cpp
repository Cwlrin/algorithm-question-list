#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> logs;
  int log;

  // 读取所有日志
  while (cin >> log) {
    logs.push_back(log);
  }

  int n = logs.size();
  int max_score = 0;

  // 遍历所有可能的上报时机
  for (int i = 0; i < n; ++i) {
    int total_logs = 0;
    int score = 0;

    // 遍历计算每个时刻的日志
    for (int j = 0; j <= i; ++j) {
      total_logs += logs[j];

      // 如果总日志数超过 100，只计算 100 个日志的积分
      if (total_logs > 100) {
        int exceed = total_logs - 100;
        score += logs[j] - exceed;
        score -= (i - j) * logs[j];
        break;
      }

      // 每条日志增加 1 分
      score += logs[j];
      // 每条日志扣除延迟的分数
      score -= (i - j) * logs[j];
    }

    max_score = max(max_score, score);
  }

  cout << max_score << endl;
  return 0;
}