#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string s1, s2;
  int k;

  // 读取输入数据
  cin >> s1 >> s2 >> k;

  int n1 = s1.size(), n2 = s2.size();
  if (n1 + k > n2) return cout << -1 << endl, 0; // 如果 s2 的长度不足

  // 统计 s1 中每个字符的频率
  vector<int> char_count(26, 0);
  for (char c : s1) {
    char_count[c - 'a']++;
  }

  // 所需匹配的字符数量
  int required_chars = n1;
  int left = 0, right = 0;

  // 统计当前窗口的字符频率
  vector<int> window_count(26, 0);

  // 初始化窗口
  while (right < n1 + k && right < n2) {
    char c = s2[right++];
    window_count[c - 'a']++;
    if (char_count[c - 'a'] > 0 && window_count[c - 'a'] <= char_count[c - 'a']) {
      required_chars--;
    }
  }

  // 检查初始窗口是否满足条件
  if (required_chars == 0) {
    cout << 0 << endl; // 返回起始索引0
    return 0;
  }

  // 开始滑动窗口
  while (right < n2) {
    // 移除左侧字符
    char remove_char = s2[left++];
    if (char_count[remove_char - 'a'] > 0) {
      if (window_count[remove_char - 'a'] <= char_count[remove_char - 'a']) {
        required_chars++;
      }
      window_count[remove_char - 'a']--;
    }

    // 添加右侧新字符
    char add_char = s2[right++];
    window_count[add_char - 'a']++;
    if (char_count[add_char - 'a'] > 0 && window_count[add_char - 'a'] <= char_count[add_char - 'a']) {
      required_chars--;
    }

    // 检查当前窗口
    if (required_chars == 0) {
      cout << left << endl; // 返回窗口的起始索引
      return 0;
    }
  }

  cout << -1 << endl; // 如果没有找到合适的子串，返回-1
  return 0;
}