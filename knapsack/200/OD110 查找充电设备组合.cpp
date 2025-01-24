#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> power(n);
  for (int i = 0; i < n; ++i) {
    cin >> power[i];
  }

  int p_max;
  cin >> p_max;

  // 使用 bitset 优化 dp 数组
  bitset<1000001> dp;
  dp[0] = true; // 初始状态：空集的总和为 0

  // 动态规划求解（位运算优化）
  for (int i = 0; i < n; ++i) {
    dp |= (dp << power[i]); // 位运算更新 dp
  }

  // 寻找最优元素
  int optimal = 0;
  for (int j = p_max; j >= 0; --j) {
    if (dp[j]) {
      optimal = j;
      break;
    }
  }

  // 输出结果
  cout << optimal << endl;

  return 0;
}