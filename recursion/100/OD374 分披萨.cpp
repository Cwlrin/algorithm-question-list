#include <bits/stdc++.h>
using namespace std;

constexpr int MAXN = 510;
int n;
int pizza[MAXN];

// 记忆化数组
long long memo[MAXN][MAXN];

// 环形数组边界处理
inline int bound(int x) {
  return (x + n) % n;
}

// 递归求解最大披萨分配
long long solve(int left, int right) {
  // 馋嘴选择最大块
  if (pizza[left] > pizza[right]) {
    left = bound(left - 1);
  } else {
    right = bound(right + 1);
  }

  // 缓存优化
  if (memo[left][right] > 0) {
    return memo[left][right];
  }

  if (left == right) {
    // 只剩一块披萨
    memo[left][right] = pizza[left];
  } else {
    // 吃货选择最优解
    memo[left][right] = max(
        solve(bound(left - 1), right) + pizza[left],
        solve(left, bound(right + 1)) + pizza[right]
        );
  }

  return memo[left][right];
}

int main() {
  // 输入披萨数量
  cin >> n;

  // 输入披萨大小
  for (int i = 0; i < n; i++) {
    cin >> pizza[i];
  }

  // 最大披萨值初始化
  long long max_pizza = 0;

  // 单一循环，尝试每个起点
  for (int i = 0; i < n; i++) {
    // 重置记忆数组
    memset(memo, 0, sizeof(memo));

    // 计算从该起点开始的最大披萨值
    max_pizza = max(max_pizza,
                    solve(bound(i - 1), bound(i + 1)) + pizza[i]
        );
  }

  // 输出最终结果
  cout << max_pizza << endl;

  return 0;
}