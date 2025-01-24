#include <bits/stdc++.h>
using namespace std;

int main() {
  // 动态读取输入  
  string line;
  vector<int> costs(4);
  vector<int> days;

  // 读取售票价格数组  
  getline(cin, line);
  stringstream ss(line);
  for (int i = 0; i < 4; ++i) {
    ss >> costs[i];
  }

  // 读取游玩日期数组  
  getline(cin, line);
  stringstream ss2(line);
  int day;
  while (ss2 >> day) {
    days.push_back(day);
  }

  // 使用动态规划计算最低消费  
  unordered_set<int> travel_days(days.begin(), days.end());
  vector<int> dp(366, 0);

  for (int i = 1; i <= 365; ++i) {
    if (travel_days.find(i) == travel_days.end()) {
      dp[i] = dp[i - 1];
    } else {
      dp[i] = dp[i - 1] + costs[0];
      dp[i] = min(dp[i], dp[max(i - 3, 0)] + costs[1]);
      dp[i] = min(dp[i], dp[max(i - 7, 0)] + costs[2]);
      dp[i] = min(dp[i], dp[max(i - 30, 0)] + costs[3]);
    }
  }

  // 输出结果  
  cout << dp[365] << endl;

  return 0;
}