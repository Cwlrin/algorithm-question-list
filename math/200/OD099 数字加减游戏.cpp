#include <bits/stdc++.h>
using namespace std;

int main() {
  int s, t, a, b;
  cin >> s >> t >> a >> b;

  int target = t - s; // 目标差值

  // 如果 s > t，我们需要从 t 加到 s，因此用加法
  // 例如 s = 100, t = 69，我们应该计算从 100 减到 69
  // 但为了统一处理，直接使用差值即可

  int min_x = INT_MAX; // 最小使用次数

  // 从 x = 0 开始尝试，逐步增加 |x|
  for (int x = 0; ; ++x) {
    // 检查 x 和 -x 是否满足条件
    int remainder1 = target - a * x;    // a * x + b * y = target
    int remainder2 = target - a * (-x); // a * (-x) + b * y = target

    // 检查 remainder1 % b == 0
    // 并且 remainder1 / b 的结果可以是正数或负数
    if (remainder1 % b == 0) {
      min_x = x;
      break;
    }

    // 检查 remainder2 % b == 0
    // 并且 remainder2 / b 的结果可以是正数或负数
    if (remainder2 % b == 0) {
      min_x = x;
      break;
    }
  }

  cout << min_x << endl;
  return 0;
}