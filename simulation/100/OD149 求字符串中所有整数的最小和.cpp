#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  long long sum = 0;  // 使用long long避免溢出
  int len = s.length();
  int i = 0;

  while (i < len) {
    // 跳过非数字且非负号的字符
    if (!isdigit(s[i]) && s[i] != '-') {
      i++;
      continue;
    }

    // 处理负数
    if (s[i] == '-') {
      i++;  // 移到负号后面
      string num;
      // 收集负号后的所有数字
      while (i < len && isdigit(s[i])) {
        num += s[i];
        i++;
      }
      // 如果负号后有数字
      if (!num.empty()) {
        // 去除前导零
        while (num.length() > 1 && num[0] == '0') {
          num = num.substr(1);
        }
        sum -= stoll(num);
      }
    }
    // 处理正数
    else if (isdigit(s[i])) {
      // 对于正数，逐位相加
      while (i < len && isdigit(s[i])) {
        sum += (s[i] - '0');
        i++;
      }
    }
  }

  cout << sum << endl;
  return 0;
}