#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入的位数和序号
  int digit_count, sequence_index;
  cin >> digit_count >> sequence_index;

  // 输入合法性检查
  if (digit_count < 3 || digit_count > 7) {
    cout << -1 << endl;
    return 0;
  }

  // 序号合法性检查
  if (sequence_index < 0) {
    cout << -1 << endl;
    return 0;
  }

  // 预计算最大可能值
  int upper_bound = pow(9, digit_count) * digit_count;

  // 存储水仙花数的容器
  vector<long long> narcissistic_numbers;

  // 计算 n 位数的起始和结束范围
  long long start = pow(10, digit_count - 1);
  long long end = min(static_cast<long long>(pow(10, digit_count) - 1),
                      static_cast<long long>(upper_bound));

  // 快速幂预处理
  vector<int> power_cache(10);
  for (int i = 0; i < 10; ++i) {
    power_cache[i] = pow(i, digit_count);
  }

  // 遍历范围查找水仙花数
  for (long long number = start; number <= end; number++) {
    // 快速剪枝：数字各位数字最大和限制
    long long temp = number;
    long long sum = 0;
    bool valid = true;

    while (temp > 0) {
      int digit = temp % 10;
      sum += power_cache[digit];

      // 提前剪枝：和已经超过原数
      if (sum > number) {
        valid = false;
        break;
      }

      temp /= 10;
    }

    // 判断是否为水仙花数并记录
    if (valid && sum == number) {
      narcissistic_numbers.push_back(number);
    }
  }

  // 处理查找结果
  if (narcissistic_numbers.empty()) {
    cout << -1 << endl;
  } else if (sequence_index < narcissistic_numbers.size()) {
    cout << narcissistic_numbers[sequence_index] << endl;
  } else {
    // 处理大索引情况
    long long last_narcissistic = narcissistic_numbers.back();
    // 使用 long long 避免溢出
    long long result =
        last_narcissistic * static_cast<long long>(sequence_index);
    cout << result << endl;
  }

  return 0;
}