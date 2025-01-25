#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入
  string input;
  getline(cin, input);
  stringstream ss(input);

  vector<int> groups;
  int value;
  while (ss >> value) {
    groups.push_back(value);
    if (ss.peek() == ',') {
      ss.ignore();
    }
  }

  int capacity;
  cin >> capacity;

  // 动态规划表
  vector<int> dp(capacity + 1, 0);
  dp[0] = 1; // 容量为 0 时有一种方案

  // 更新动态规划表
  for (int group : groups) {
    for (int i = capacity; i >= group; --i) {
      dp[i] += dp[i - group];
    }
  }

  // 输出结果
  cout << dp[capacity] << endl;

  return 0;
}