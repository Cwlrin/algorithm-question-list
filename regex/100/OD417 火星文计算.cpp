#include <bits/stdc++.h>

using namespace std;

// 计算 x # y 的函数
unsigned long long CalculateHash(unsigned long long x, unsigned long long y) {
  return 4 * x + 3 * y + 2;
}

// 计算 x $ y 的函数
unsigned long long CalculateDollar(unsigned long long x, unsigned long long y) {
  return 2 * x + y + 3;
}

int main() {
  string expression;
  cin >> expression; // 输入火星人的字符串表达式

  vector<unsigned long long> numbers; // 用于存储数字
  vector<char> operations; // 用于存储运算符

  // 解析表达式
  for (size_t i = 0; i < expression.size(); ) {
    size_t j = i;
    while (j < expression.size() && isdigit(expression[j])) {
      j++; // 找到数字的范围
    }
    // 提取数字并存入 numbers 中
    unsigned long long number = stoull(expression.substr(i, j - i));
    numbers.push_back(number);

    if (j < expression.size()) {
      operations.push_back(expression[j]); // 提取操作符
      j++; // 移动到下一个字符
    }
    i = j; // 更新 i
  }

  // 优先处理 #
  size_t pos = 0;

  while (pos < operations.size()) {
    if (operations[pos] == '#') {
      unsigned long long result = CalculateHash(numbers[pos], numbers[pos + 1]);
      // 更新 numbers 和 operations
      numbers[pos] = result; // 更新数字
      numbers.erase(numbers.begin() + pos + 1); // 删除下一个数字
      operations.erase(operations.begin() + pos); // 删除运算符
      // 从当前位置重新开始处理
      pos = 0;
    } else {
      pos++; // 移动到下一个操作符
    }
  }

  // 处理所有 $
  unsigned long long final_result = numbers[0];
  for (size_t i = 0; i < operations.size(); ++i) {
    if (operations[i] == '$') {
      final_result = CalculateDollar(final_result, numbers[i + 1]);
    }
  }

  // 输出最终结果
  cout << final_result << endl;

  return 0;
}