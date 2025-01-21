#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
  string str1, str2;

  // 读取输入的两个字符串
  cin >> str1 >> str2;

  int len1 = str1.size(), len2 = str2.size();

  if (len1 > len2) {
    cout << -1 << endl; // 如果 str1 比 str2 长，直接返回 -1
    return 0;
  }

  // 频率统计
  vector<int> count1(26, 0), count2(26, 0);

  // 统计 str1 字符频率
  for (char c : str1) {
    count1[c - 'a']++;
  }

  // 初始化滑动窗口的字符频率
  for (int i = 0; i < len1; i++) {
    count2[str2[i] - 'a']++;
  }

  // 检查第一个滑动窗口
  if (count1 == count2) {
    cout << 0 << endl; // 如果第一个窗口匹配，返回 0
    return 0;
  }

  // 移动窗口
  for (int i = len1; i < len2; i++) {
    // 新增字符
    count2[str2[i] - 'a']++;
    // 移除旧字符
    count2[str2[i - len1] - 'a']--;

    // 检查窗口数据是否匹配
    if (count1 == count2) {
      cout << i - len1 + 1 << endl; // 返回匹配的起始位置
      return 0;
    }
  }

  cout << -1 << endl; // 如果没有找到匹配，输出 -1
  return 0;
}