#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // 读取输入
  string line;
  getline(cin, line);

  // 解析输入
  vector<long long> stack;
  stringstream ss(line);
  long long num;

  // 依次处理每个数字
  while (ss >> num) {
    stack.push_back(num);

    // 检查是否满足出栈条件
    while (stack.size() >= 2) {
      bool found = false;

      // 尝试查找从栈顶开始的所有可能子序列
      for (int i = 2; i <= min(static_cast<int>(stack.size()), 1000); i++) {
        // 计算最后 i 个元素的和
        long long sum = 0;
        for (int j = stack.size() - i; j < stack.size() - 1; j++) {
          sum += stack[j];
        }

        // 检查是否满足条件
        if (stack.back() == sum) {
          // 出栈 i 个元素
          long long last = stack.back();
          for (int k = 0; k < i; k++) {
            stack.pop_back();
          }

          // 入栈新元素
          stack.push_back(2 * last);

          found = true;
          break;
        }
      }

      // 如果没有找到满足条件的子序列，退出循环
      if (!found)
        break;
    }
  }

  // 输出结果
  if (stack.empty()) {
    cout << "No" << endl;
  } else {
    // 反向输出栈中元素
    for (int i = stack.size() - 1; i >= 0; i--) {
      cout << stack[i];
      if (i > 0)
        cout << " ";
    }
    cout << endl;
  }

  return 0;
}