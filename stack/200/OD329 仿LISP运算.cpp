#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input); // 读取整个输入行

  stack<string> stack; // 用于存储操作数和操作符
  string sb;      // 用于收集字符的临时字符串

  for (char c : input) {
    if (c != '(' && c != ')' && c != ' ') {
      // 收集操作符或参数的字符
      sb += c;
    } else if (c == ' ' || c == ')') {
      // 当收集完一个元素时，将其压入栈
      if (!sb.empty()) {
        stack.push(sb);
        sb.clear(); // 清空临时字符串
      }

      // 遇到闭合括号，进行计算
      if (c == ')') {
        // 从栈中取出 p2, p1 和 op
        int p2 = stoi(stack.top());
        stack.pop();
        int p1 = stoi(stack.top());
        stack.pop();
        string op = stack.top();
        stack.pop();

        // 执行计算
        int result = 0;
        if (op == "add")
          result = p1 + p2; // 加法
        else if (op == "sub")
          result = p1 - p2; // 减法
        else if (op == "mul")
          result = p1 * p2; // 乘法
        else if (op == "div") {
          // 处理除法，包括除零错误和向下取整
          if (p2 == 0) {
            cout << "error" << endl; // 输出错误信息
            return 0;                // 终止程序
          }
          // 向下取整操作，考虑负数
          result = p1 / p2;
          if (p1 % p2 != 0 && (p1 < 0) != (p2 < 0)) {
            result--; // 调整结果向下取整
          }
        }

        // 将计算结果重新压入栈
        stack.push(to_string(result));
      }
    }
  }

  // 输出最上面的结果，也就是最终计算结果
  cout << stack.top() << endl;

  return 0;
}