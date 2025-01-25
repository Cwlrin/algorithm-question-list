#include <bits/stdc++.h>

using namespace std;

int dp[32][2][2][2]; // 状态表
vector<int> digits;  // 存储二进制位

int dfs(int pos, int prev1, int prev2, int tight) {
  // 如果已经处理完所有位，返回 1（表示找到一个有效数）
  if (pos == digits.size()) {
    return 1;
  }

  // 如果状态已经计算过，直接返回结果
  if (dp[pos][prev1][prev2][tight] != -1) {
    return dp[pos][prev1][prev2][tight];
  }

  int limit = tight ? digits[pos] : 1; // 当前位的上限
  int count = 0;

  for (int i = 0; i <= limit; ++i) {
    // 检查是否出现 101
    if (prev2 == 1 && prev1 == 0 && i == 1) {
      continue; // 跳过无效情况
    }

    // 递归处理下一位
    count += dfs(pos + 1, i, prev1, tight && (i == limit));
  }

  // 记录状态并返回结果
  return dp[pos][prev1][prev2][tight] = count;
}

int main() {
  int l, r;
  cin >> l >> r;

  // 计算 [1, r] 的满足条件的数的个数
  digits.clear();
  int temp = r;
  while (temp > 0) {
    digits.push_back(temp % 2);
    temp /= 2;
  }
  reverse(digits.begin(), digits.end());

  memset(dp, -1, sizeof(dp));
  int total = dfs(0, 0, 0, 1);

  // 计算 [1, l - 1] 的满足条件的数的个数
  digits.clear();
  temp = l - 1;
  while (temp > 0) {
    digits.push_back(temp % 2);
    temp /= 2;
  }
  reverse(digits.begin(), digits.end());

  memset(dp, -1, sizeof(dp));
  int exclude = dfs(0, 0, 0, 1);

  // 输出结果
  cout << total - exclude << endl;

  return 0;
}