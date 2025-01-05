#include <bits/stdc++.h>

using namespace std;

void convert(string& s) {
  int lower_count = 0;
  int upper_count = 0;

  for (const auto& c : s) {
    if (islower(c)) lower_count++;
    else if (isupper(c)) upper_count++;
  }

  if (lower_count > upper_count) {
    ranges::transform(s, s.begin(), ::tolower);
  } else if (lower_count < upper_count) {
    ranges::transform(s, s.begin(), ::toupper);
  }
}

int main() {
  int k;
  string s;
  cin >> k;
  cin >> s;
  // 存储最终结果
  string result;
  // 第一步：按 '-' 分割字符串
  stringstream ss(s);
  string token, new_str;
  // 处理第一个子串的标志
  bool first = true;
  // 分割并处理子串
  while (getline(ss, token, '-')) {
    if (first) {
      // 第一个子串直接保留
      result += token;
      first = false;
    } else {
      // 合并后续子串
      new_str += token;
    }
  }
  // 处理后续子串
  for (size_t i = 0; i < new_str.size(); i += k) {
    // 获取 K 个字符的子串
    string group = new_str.substr(i, k);
    // 转换大小写  
    convert(group);
    // 添加分隔符和处理后的子串  
    result += "-" + group;
  }
  cout << result << endl;
  return 0;
}