#include <bits/stdc++.h>

using namespace std;

int main() {
  // 读取输入字符串
  string s;
  cin >> s;

  // 统计 'o' 的数量
  int o_count = 0;
  for (char c : s) {
    if (c == 'o') {
      o_count++;
    }
  }

  // 根据 'o' 数量的奇偶性返回结果
  cout << (o_count % 2 == 0 ? s.length() : s.length() - 1) << endl;

  return 0;
}