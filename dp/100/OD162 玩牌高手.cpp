#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);

  // 解析输入
  vector<int> nums;
  stringstream ss(input);
  string token;
  while (getline(ss, token, ',')) {
    nums.push_back(stoi(token));
  }

  int n = nums.size();

  // 动态规划数组
  vector<int> dp(n + 1, 0);

  // 初始条件
  dp[0] = 0;

  // 计算 dp[i]
  for (int i = 1; i <= n; ++i) {
    // 选择获取当前轮的牌面分数
    int take = dp[i - 1] + nums[i - 1];

    // 选择跳过当前轮
    int skip = (i >= 3) ? dp[i - 3] : 0;

    // 取最大值
    dp[i] = max(take, skip);
  }

  // 输出结果
  cout << dp[n] << endl;

  return 0;
}