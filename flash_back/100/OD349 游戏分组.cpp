#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  // 存储10名选手的评分
  vector<int> scores(10);

  // 读取10个评分
  for (int i = 0; i < 10; i++) {
    cin >> scores[i];
  }

  // 最小实力差
  int min_diff = INT_MAX;

  // 枚举所有可能的组合
  // 使用二进制方式枚举选择5个人的所有方案
  for (int state = 0; state < (1 << 10); state++) {
    // 确保选择了5个人
    if (__builtin_popcount(state) != 5)
      continue;

    // 计算两组的总分
    int group1_sum = 0, group2_sum = 0;

    // 遍历所有选手
    for (int i = 0; i < 10; i++) {
      // 使用位运算判断选手归属
      if (state & (1 << i)) {
        group1_sum += scores[i];
      } else {
        group2_sum += scores[i];
      }
    }

    // 更新最小实力差
    min_diff = min(min_diff, abs(group1_sum - group2_sum));
  }

  // 输出结果
  cout << min_diff << endl;

  return 0;
}