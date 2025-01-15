#include <bits/stdc++.h>

using namespace std;

int main() {
  string input;
  getline(cin, input);
  string result;
  // 逐个字符处理输入
  for (int i = 0; i < input.size();) {
    // 处理数字部分
    if (isdigit(input[i])) {
      // 解析数字
      int count = 0;
      bool has_leading_zero = (input[i] == 0);
      while (i < input.size() && isdigit(input[i])) {
        // 检查前导 0
        if (count == 0 && input[i] == '0') {
          has_leading_zero = true;
        }
        count = count * 10 + (input[i] - '0');
        i++;
      }
      if ((count > 0 && count < 3) || i >= input.size() || !islower(input[i]) ||
          has_leading_zero) {
        cout << "!error" << endl;
        return 0;
      }
      // 重复字母
      result.append(count, input[i]);
      i++;
    }
    // 处理普通字母
    else if (islower(input[i])) {
      result += input[i];
      i++;
    }
    // 非法字符
    else {
      cout << "!error" << endl;
      return 0;
    }
  }
  // 如果解压成功，检查重新压缩后是否与输入一致
  string recompressed;
  int count = 1;
  for (int i = 1; i <= result.size(); ++i) {
    // 如果是连续字符，计数器增加
    if (i < result.size() && result[i] == result[i - 1]) {
      count++;
    }
    // 遇到不同字符或者到达末尾
    else {
      // 只有连续三个以上才压缩
      if (count >= 3) {
        recompressed += to_string(count) + result[i - 1];
      }
      // 少于三个则正常输出
      else {
        recompressed.append(count, result[i - 1]);
      }
      // 重置计数器
      count = 1;
    }
  }
  // 检查解压后再次压缩的结果是否与原始输入一致
  if (recompressed == input) {
    cout << result << endl;
  } else {
    cout << "!error" << endl;
  }
  return 0;
}