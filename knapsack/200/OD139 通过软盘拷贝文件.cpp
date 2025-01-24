#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> size(n);
  for (int i = 0; i < n; ++i) {
    cin >> size[i];
  }

  // 计算每个文件占用的块数
  vector<int> blocks(n);
  for (int i = 0; i < n; ++i) {
    blocks[i] = (size[i] + 511) / 512;  // ceil(Si / 512)
  }

  // 软盘的总块数
  int total_blocks = 2880;

  // 初始化 dp 数组
  vector<int> dp(total_blocks + 1, 0);

  // 动态规划求解
  for (int i = 0; i < n; ++i) {
    for (int j = total_blocks; j >= blocks[i]; --j) {
      dp[j] = max(dp[j], dp[j - blocks[i]] + size[i]);
    }
  }

  // 输出结果
  cout << dp[total_blocks] << endl;

  return 0;
}