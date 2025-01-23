#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  cin >> input; // 读取输入信号字符串

  stack<char> st;              // 用于保存当前信号的字符
  string longest_signal = "-1"; // 初始化最长信号为-1
  int max_length = 0;           // 初始化最长信号的长度

  for (char c : input) {
    if (st.empty()) {
      // 如果栈为空，直接压入字符
      st.push(c);
    } else {
      char top = st.top();
      if (c == '0' && top == '0') {
        // 如果出现两个'0'，表示可能开始新的信号
        string current_signal;
        while (!st.empty()) {
          current_signal = st.top() + current_signal; // 组合形成信号
          st.pop();
        }

        // 使用正则表达式验证是否为完全交替信号
        regex pattern1("^0(10)+$"); // 模式1：0后面是一个或多个10
        regex pattern2("^(01)+0$"); // 模式2：0前面是一个或多个01

        // 如果满足任意一个正则，则找到一个交替信号
        if (regex_match(current_signal, pattern1) || regex_match(
                current_signal, pattern2)) {
          int current_length = current_signal.length();
          if (current_length > max_length) {
            max_length = current_length;
            longest_signal = current_signal; // 更新最长信号
          }
        }

        // 新信号的 '0' 入栈
        st.push(c);
      } else if (c == '0' || c == '1') {
        // 其他情况下直接压入栈
        st.push(c);
      }
    }
  }

  // 处理最后一个可能的信号（如果栈不为空时）
  if (!st.empty()) {
    string current_signal;
    while (!st.empty()) {
      current_signal = st.top() + current_signal; // 组合形成信号
      st.pop();
    }

    // 再次验证当前信号
    regex pattern1("^0(10)+$"); // 模式1：0后面是一个或多个10
    regex pattern2("^(01)+0$"); // 模式2：0前面是一个或多个01

    if (regex_match(current_signal, pattern1) || regex_match(
            current_signal, pattern2)) {
      int current_length = current_signal.length();
      if (current_length > max_length) {
        max_length = current_length;
        longest_signal = current_signal; // 更新最长信号
      }
    }
  }

  // 输出结果
  cout << longest_signal << endl;

  return 0;
}