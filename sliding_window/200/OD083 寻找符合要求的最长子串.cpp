#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
  char forbidden_char;
  string s;

  // 读取输入
  cin >> forbidden_char;
  cin >> s;

  unordered_map<char, int> char_count;
  int max_length = 0; // 记录满足条件的最长子串长度
  int start = 0;     // 滑动窗口的起始位置

  for (int end = 0; end < s.size(); end++) {
    char current_char = s[end];

    // 跳过限制字符
    if (current_char == forbidden_char) {
      start = end + 1;   // 移动窗口开始位置
      char_count.clear(); // 清空字符计数
      continue;
    }

    // 记录当前字符
    char_count[current_char]++;

    // 如果当前字符次数超过 2，则移动左指针
    while (char_count[current_char] > 2) {
      char_count[s[start]]--;
      start++;
    }

    // 更新最长子串长度
    max_length = max(max_length, end - start + 1);
  }

  cout << max_length << endl; // 输出结果
  return 0;
}
