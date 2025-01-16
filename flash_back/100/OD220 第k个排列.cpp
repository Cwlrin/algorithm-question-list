#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  // 读取输入
  int n, k;
  cin >> n >> k;

  // 阶乘预处理
  vector<int> factorial(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    factorial[i] = factorial[i - 1] * i;
  }

  // 记录数字是否被使用
  vector<bool> used(n + 1, false);

  // 结果字符串
  string result;

  // k从1开始，需要减1调整
  k--;

  // 逐位确定
  for (int i = 1; i <= n; i++) {
    // 当前位的分组大小
    int group = factorial[n - i];

    // 计算当前位应该填入的数字
    for (int j = 1; j <= n; j++) {
      if (used[j])
        continue;

      // 如果当前数字组可以容纳k
      if (k >= group) {
        k -= group;
      } else {
        // 找到了当前位的数字
        result += to_string(j);
        used[j] = true;
        break;
      }
    }
  }

  // 输出结果
  cout << result << endl;

  return 0;
}